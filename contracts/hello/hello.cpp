#include "hello.hpp"

#include <ion/print.hpp>

void hello::hi( name user )
{
  ion::require_auth(user);
  print("Hello, ", user);
}

void hello::test( std::string id )
{
  print(id);
}

ION_DISPATCH( hello, (hi)(test))
