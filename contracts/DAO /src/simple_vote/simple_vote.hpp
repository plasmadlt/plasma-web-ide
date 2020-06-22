#pragma once

#include <ion/ion.hpp>
#include <ion/print.hpp>

#include "../core/contract.hpp"
#include "../core/vote.hpp"

class [[ion::contract]] simple_vote : public plasma::contractBase
{
public:
    simple_vote(ion::name receiver, ion::name code, ion::datastream<const char*> ds);
    virtual ~simple_vote() {}

    [[ion::action]]
    void registrate(ion::name account);

    [[ion::action]]
    void display();

    [[ion::action]]
    void remove();

    [[ion::action]]
    void addvote(ion::name account, ion::name candidate);

    [[ion::action]]
    void support(ion::name project, ion::name delegate);

    [[ion::action]]
    void addproject(ion::name user, ion::name project, ion::name bank, ion::asset quantity);

    [[ion::action]]
    void version();

private:
    void registrate_delegate(ion::name delegate);
    void donate_project(ion::name project);

private:
    TABLE candidate_data : public plasma::candidate {};
    using TableCandidate_t = ion::multi_index<"candidates"_n, candidate_data>;
    TableCandidate_t candidates;

    TABLE delegate_data : public plasma::delegate {};
    using TableDelegates_t = ion::multi_index<"delegates"_n, delegate_data>;
    TableDelegates_t delegates;

    TABLE investment_data : public plasma::investment {};
    using TableInvestments_t = ion::multi_index<"investments"_n, investment_data>;
    TableInvestments_t investments;
};
