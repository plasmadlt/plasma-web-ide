#include "simple_vote.hpp"

#include "../core/asset.hpp"
#include "../core/token_utils.hpp"
#include "../core/token_types64.hpp"

//----------------------------------------------------------------------------------------------------------------------

simple_vote::simple_vote(ion::name receiver, ion::name code, ion::datastream<const char*> ds)
  : contractBase(receiver, code, ds)
  , candidates(receiver, code.value)
  , delegates(receiver, code.value)
  , investments(receiver, code.value)
{
}

//--------------------------------------------------------------------------------

void simple_vote::registrate(ion::name account)
{
    require_auth(account);
    ion::check(ion::is_account(account), "account doesn't exist in blockchain");

    auto it = candidates.find(account.value);
    if (it == candidates.end()) {
        candidates.emplace(get_self(), [&](auto& new_data) { 
            new_data.account = account; 
        });
    }
    else {
        ion::print("Register candidate - user already exists in DB.\n");
    }
}

//--------------------------------------------------------------------------------

void simple_vote::display()
{
    require_auth(get_self());
    for (const auto& item : candidates) {
        ion::print(item.account, ", ");
    }
}

//--------------------------------------------------------------------------------

void simple_vote::remove()
{
    require_auth(get_self());

    auto it = candidates.begin();
    while (it != candidates.end()) {
        it = candidates.erase(it);
    }
}

//----------------------------------------------------------------------------------------------------------------------

void simple_vote::addvote(ion::name account, ion::name candidate)
{
    ion::check(ion::is_account(account), "account doesn't exist in blockchain");
    ion::check(ion::is_account(candidate), "account doesn't exist in blockchain");

    require_auth(account);
    ion::check(account != candidate, "voting for yourself forbidden");

    auto it = candidates.find(candidate.value);
    ion::check(it != candidates.end(), "account wasn't registered as candidate in DAO");

    auto pos = std::find(it->electors.begin(), it->electors.end(), account);
    ion::check(pos == it->electors.end(), "account has already voted per delegate");

    candidates.modify(it, get_self(), [&](auto& old_data) {
        old_data.electors.push_back(account);
    });

    auto total_votes = it->electors.size();
    ion::print("#", account, " voted for #", candidate, ", total votes = [", total_votes, "]");

    if (total_votes >= 3) {
        //  ToDo -> BPV review
        registrate_delegate(candidate);
    }
}

//----------------------------------------------------------------------------------------------------------------------

void simple_vote::registrate_delegate(ion::name delegate)
{
    auto it = delegates.find(delegate.value);
    if (it == delegates.end()) {
        delegates.emplace(get_self(), [&](auto& new_data) { 
            new_data.account = delegate; 
        });
        ion::print(", new DAO delegate registered, welcome #", delegate);
    }
    else {
        ion::print(", #", delegate, " already registered as DAO delegate");
    }
}

//----------------------------------------------------------------------------------------------------------------------

void simple_vote::support(ion::name project, ion::name delegate)
{
    require_auth(delegate);
    ion::check(ion::is_account(delegate), "account doesn't exist in blockchain");
    
    auto itd = delegates.find(delegate.value);
    ion::check(itd != delegates.end(), "account wasn't registered as delegate in DAO");

    auto itp = investments.find(project.value);
    ion::check(itp != investments.end(), "project wasn't registered in DAO");

    investments.modify(itp, get_self(), [&](auto& old_data) {
        old_data.voters.push_back(delegate);
    });

    auto total_votes = itp->voters.size();
    ion::print("delegate #", delegate, " voted for project #", project, "], total votes = [", total_votes, "]");

    if (total_votes == 2) {
        donate_project(project);
    }
}

//----------------------------------------------------------------------------------------------------------------------

void simple_vote::donate_project(ion::name project)
{
    ion::print(", #donate_investment call");
}

//----------------------------------------------------------------------------------------------------------------------

void simple_vote::addproject(ion::name user, ion::name project, ion::name bank, ion::asset quantity)
{
    require_auth(user);
    ion::check(ion::is_account(user), "account doesn't exist in blockchain");

    auto it = investments.find(project.value);
    ion::check(it == investments.end(), "project already registered in DAO");

    investments.emplace(get_self(), [&](auto& new_data) { 
        new_data.project = project; 
        new_data.bank = bank;
        new_data.quantity = quantity;
    });

    ion::print("project #", project, " successfully registered in DAO");
}

//----------------------------------------------------------------------------------------------------------------------

void simple_vote::version()
{
    printVersion("0.1");
}

//----------------------------------------------------------------------------------------------------------------------

ION_DISPATCH(simple_vote, (registrate)(display)(remove)(addvote)(support)(addproject)(version))
