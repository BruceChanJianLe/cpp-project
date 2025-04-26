#pragma once

#include "virtual/devices.hpp"

namespace dv
{
  class DeviceManager
  {
  public:
    DeviceManager();
    DeviceManager(device_list_t devices);
    auto update() -> void;
    [[nodiscard]] static auto get_devices() -> device_list_t;

  private:
    device_list_t devices_;
  };
} // dv
