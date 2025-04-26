#pragma once

#include "concept/device_concept.hpp"

namespace dc
{
  template <CDevice... TDevices>
  class DeviceManager
  {
  public:
    DeviceManager() : devices{get_devices()} {}
    auto update() -> void
    {
      std::apply(
        [this](auto &... device_list)
        {
          (update_device(device_list), ...);
        },
        devices
      );
    }

  private:
    using device_list_t = std::tuple<std::vector<TDevices>...>;
    auto update_device(auto& device_list) -> void
    {
      for (auto& device : device_list)
      {
        device.update();
      }
    }
    [[nodiscard]] static auto get_devices() -> device_list_t
    {
      return std::tuple{TDevices::find_in_env()...};
    }

    device_list_t devices;
  };
} // dc
