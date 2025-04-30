#include <cstddef>
#include <type_traits>
#include <utility>
#include <array>

// ct_int - compile time
namespace ct_int
{
  // Define a concept for integral types
  template <typename T>
  concept Type = std::is_integral_v<T>;

  // Primary template for compile-time Fibonacci calculation
  template <Type auto N>
  struct Fibonacci {
    static constexpr auto value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
  };

  // Base case 1
  template <>
  struct Fibonacci<0> {
    static constexpr auto value = 0;
  };

  // Base case 2
  template <>
  struct Fibonacci<1> {
    static constexpr auto value = 1;
  };

  // Helper variable template for cleaner syntax
  template <Type auto N>
  inline constexpr auto fibonacci_v = Fibonacci<N>::value;

  // Compile-time fibonacci sequence generator
  template <Type auto... Indexes>
  constexpr auto make_fibonacci_sequence(std::integer_sequence<int, Indexes...>) {
    return std::array<int, sizeof...(Indexes)>{fibonacci_v<Indexes>...};
  }

  template <Type auto N>
  constexpr auto fibonacci_sequence() {
    return make_fibonacci_sequence(std::make_integer_sequence<int, N>{});
  }

  template <Type auto N, std::size_t Size>
  constexpr auto fibonacci_at() {
    constexpr auto sequence = fibonacci_sequence<Size>();
    static_assert(N < Size, "Index out of bounds");
    return sequence[N];
  }
} // ct
