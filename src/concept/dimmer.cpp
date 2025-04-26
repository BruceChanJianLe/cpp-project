#include "concept/dimmer.hpp"
#include <print>

namespace dc
{
  Dimmer::Dimmer(const std::string& dimmer_name)
    : dimmer_name_{dimmer_name}
    , brightness_{0}
  {
    std::println("Constructed {}!", dimmer_name_);
  }

  [[nodiscard]] auto Dimmer::find_in_env() -> std::vector<Dimmer>
  {
    std::vector<Dimmer> devices;
    // Imagine we "discover" two dimmers in the environment
    static constexpr int num_switches = 2;

    std::string device_name{"Dimmer"};
    for (int i = 0; i < num_switches; ++i) {
      devices.emplace_back(
        std::string(device_name + std::to_string(i)));
    }

    return devices;
  }

  auto Dimmer::update() -> void
  {
    ++brightness_;
    std::println("{}: brightness is {}!", dimmer_name_, brightness_);
  }
} // dc
