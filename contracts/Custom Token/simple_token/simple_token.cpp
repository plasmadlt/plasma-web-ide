#include "simple_token.hpp"
#include <cmath>

#include "../core/asset.hpp"
#include "../core/token_utils.hpp"
#include "../core/token_types64.hpp"

//----------------------------------------------------------------------------------------------------------------------

simple_token::simple_token(ion::name receiver, ion::name code, ion::datastream<const char*> ds)
  : contractBase(receiver, code, ds)
  , simplerates_(receiver, code.value)
{
}

//----------------------------------------------------------------------------------------------------------------------

void simple_token::updaterate(ion::name owner, ion::symbol_code from, ion::symbol_code to, uint64_t value, uint8_t precision)
{
    ion::check(to == plasma::system_symbol, "[to] -> only PLASMA supported");
    ion::check(from != plasma::system_symbol, "[from] -> PLASMA not supported");

    ion::name issuer = plasma::tokenTypes::getIssuer_<plasma::tokenTypes::TableStats>(owner, from);
    require_auth(issuer);

    ion::name id(plasma::genRateID(from, to));
    auto it = simplerates_.find(id.value);
    if (it != simplerates_.end())
    {
        simplerates_.modify(it, get_self(), [&](auto& rec) {
            rec.value = value;
            rec.precision = precision;
        });
    }
    else {
        simplerates_.emplace(get_self(), [&](auto& rec) {
            rec.id        = id;
            rec.from      = from;
            rec.to        = to;
            rec.value     = value;
            rec.precision = precision;
        });
    }
}

//----------------------------------------------------------------------------------------------------------------------

void simple_token::displayrates()
{
    require_auth(get_self());
    for (const auto& item : simplerates_)
    {
        plasma::big_asset asset_print(item.value, ion::symbol(plasma::system_symbol, item.precision));
        ion::print("1.00 ", item.from, " = ", asset_print, "\n");
    }
}

//----------------------------------------------------------------------------------------------------------------------

void simple_token::clearrates()
{
    require_auth(get_self());
    auto it = simplerates_.begin();
    while (it != simplerates_.end())
    {
        it = simplerates_.erase(it);
    }
}

//----------------------------------------------------------------------------------------------------------------------

void simple_token::buytokens(ion::name user, ion::name owner, ion::asset amount)
{
    ion::name id(plasma::genRateID(amount.symbol.code() , plasma::system_symbol));
    auto it = simplerates_.find(id.value);

    ion::check(it != simplerates_.end(), "buytokens exchange rate not found");
    ion::check(it->from == amount.symbol.code(), "buytokens exchange rate invalid");

    //----------------------------------------------------------------------------------------------------------------------
    //  calculate and transfer PLASMA tokens user -> owner account

    ion::symbol sys_symbol = plasma::tokenTypes::getSymbolEx(plasma::system_symbol);
    ion::symbol from_symbol = plasma::tokenTypes::getSymbol_<plasma::tokenTypes::TableStats>(owner, it->from);

    plasma::big_asset quantity(
        amount.amount * it->value / std::pow(10, it->precision) * 
        std::pow(10, sys_symbol.precision() - from_symbol.precision()), sys_symbol);

    plasma::token::transfer(user, owner, quantity, std::string("buytokens PLASMA transfer"));
    // ion::print("quantity_test = ", quantity);

    //----------------------------------------------------------------------------------------------------------------------
    //  issue tokens to the owner account

    ion::name issuer = plasma::tokenTypes::getIssuer_<plasma::tokenTypes::TableStats>(owner, amount.symbol.code());
    ion::action(
            ion::permission_level{ issuer, ion::name("active") },
            owner,
            ion::name("issue"),
            std::make_tuple(owner, amount, std::string("buytokens issue"))
    ).send();

    //----------------------------------------------------------------------------------------------------------------------
    //  transfer tokens owner account -> user account

    require_auth(user);

    ion::action(
            ion::permission_level{ owner, ion::name("active") },
            ion::name(owner),
            ion::name("transfer"),
            std::make_tuple(owner, user, amount, std::string("buytokens transfer"))
    ).send();
}

//----------------------------------------------------------------------------------------------------------------------

void simple_token::version()
{
    printVersion("0.1");
}

//----------------------------------------------------------------------------------------------------------------------

ION_DISPATCH(simple_token, (updaterate)(displayrates)(clearrates)(buytokens)(version))
