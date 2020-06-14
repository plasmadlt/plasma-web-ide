#pragma once

#include <ion/ion.hpp>
#include <ion/print.hpp>

#include "../core/contract.hpp"
#include "../core/rate.hpp"

class [[ion::contract]] simple_token : public plasma::contractBase
{
public:
    simple_token(ion::name receiver, ion::name code, ion::datastream<const char*> ds);
    virtual ~simple_token() {}

    [[ion::action]]
    void updaterate(ion::name owner, ion::symbol_code from, ion::symbol_code to, uint64_t value, uint8_t precision);

    [[ion::action]]
    void displayrates();

    [[ion::action]]
    void clearrates();

    [[ion::action]]
    void buytokens(ion::name user, ion::name owner, ion::asset amount);

    [[ion::action]]
    void version();

private:
    TABLE simplerate_ : public plasma::coinrate {};
    using TableSimpleRates_t = ion::multi_index<"simple.rates"_n, simplerate_>;
    TableSimpleRates_t simplerates_;
};
