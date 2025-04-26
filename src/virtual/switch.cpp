#include "virtual/switch.hpp"
#include "virtual/devices.hpp"
#include <print>

namespace dv
{
  Switch::Switch(const std::string& switch_name)
    : switch_name_{switch_name}
    , is_on_{false}
  {
    std::println("Constructed {}!", switch_name_);
  }

  [[nodiscard]] auto Switch::find_in_env() -> device_list_t
  {
    device_list_t devices;
    // Imagine we "discover" three switches in the environment
    static constexpr int num_switches = 3;

    std::string device_name{"Switch"};
    for (int i = 0; i < num_switches; ++i) {
        devices.emplace_back(
            std::make_unique<Switch>(device_name + std::to_string(i)));
    }

    return devices;
  }

  auto Switch::update() -> void
  {
    using namespace std::literals;
    is_on_ = !is_on_;
    std::println("{}: is {}!", switch_name_, is_on_ ? "ON"sv : "OFF"sv);
  }
} // dv
