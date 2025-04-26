#pragma once

#include "virtual/devices.hpp"
#include <cstdint>

namespace dv
{
  class Dimmer final : public DeviceInterface
  {
  public:
    Dimmer(const std::string& dimmer_name);

    [[nodiscard]] static auto find_in_env() -> device_list_t;
    auto update() -> void override;
  private:
    std::string dimmer_name_;
    uint_fast8_t brightness_;
  };
} // dv
