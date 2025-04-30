#include "common/fibonacci_generator_int.hpp"
#include <cstdlib>
#include <fmt/core.h>

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  fmt::print("INTEGER FIBONACCI GENERATOR\n");
  fmt::print("===========================\n");

  // Compile-time calculation of fibonacci number
  constexpr auto fib10 = ct_int::fibonacci_v<10>;
  fmt::print("\nThe 10th Fibonacci number is {}.\n", fib10);

  // Generate first 15 Fibonacci numbers at compile-time
  constexpr auto fib15_sequence = ct_int::fibonacci_sequence<15>();

  fmt::print("\nThe Fibonacci sequence of first 15th numbers.\n");

  for (const auto& fib_num : fib15_sequence) {
    fmt::print("{}, ", fib_num);
  }
  fmt::print("\n");

  // Access specific element at compile-time
  constexpr auto fib7 = ct_int::fibonacci_at<7, 8>();
  fmt::print("\nThe 7th Fibonacci number is {}.\n", fib7);

  // Verify that calculations are done at compile-time
  static_assert(ct_int::fibonacci_v<0> == 0);
  static_assert(ct_int::fibonacci_v<1> == 1);
  static_assert(ct_int::fibonacci_v<2> == 1);
  static_assert(ct_int::fibonacci_v<3> == 2);
  static_assert(ct_int::fibonacci_v<4> == 3);
  static_assert(ct_int::fibonacci_v<5> == 5);
  static_assert(ct_int::fibonacci_v<6> == 8);
  static_assert(ct_int::fibonacci_v<7> == 13);
  static_assert(ct_int::fibonacci_v<8> == 21);

  return EXIT_SUCCESS;
}
