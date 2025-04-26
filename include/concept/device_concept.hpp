#pragma once

#include <vector>
#include <concepts>

namespace dc
{
  // Binding interface
  template <typename T>
  concept CDevice = requires (T device) {
    { T::find_in_env() } -> std::same_as<std::vector<T>>;
    { device.update() } -> std::same_as<void>;
  };
} // dc
