#pragma once

#include "virtual/devices.hpp"

namespace dv
{
  class Switch final : public DeviceInterface
  {
  public:
    Switch(const std::string& switch_name);

    [[nodiscard]] static auto find_in_env() -> device_list_t;
    auto update() -> void override;
  private:
    std::string switch_name_;
    bool is_on_;
  };
} // dv
