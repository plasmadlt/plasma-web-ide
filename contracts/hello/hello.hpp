#pragma once

#include <ion/ion.hpp>

using namespace ion;

CONTRACT hello : public contract
{
public:
  using contract::contract;

  ACTION hi( name user );
  ACTION test( std::string id );
};
