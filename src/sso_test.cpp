#include "sso/sso.hpp"
#include <iostream>

void check_str_alloc(const auto &str) {
  const void *strptr = &str;
  const void *dataptr = str.c_str();
  // note that this is UB I'm not allowed to compare
  // unrelated ptrs, but I'm trying it anyhow

  const auto distance = std::abs(static_cast<const char *>(strptr) -
                                 static_cast<const char *>(dataptr));

  std::cout << strptr << ' ' << dataptr << " is small str: " << (distance < 100)
            << ' ' << str.c_str() << '\n';
}

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  sso::String data;
  check_str_alloc(data);

  data = "Hello World";
  check_str_alloc(data);

  data = "Hello World Long String Of Data";
  check_str_alloc(data);

  data = "short";
  check_str_alloc(data);

  std::cout << "Size of sso::String: " << sizeof(sso::String) << '\n';

  return 0;
}
