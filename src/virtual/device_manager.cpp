#include "virtual/device_manager.hpp"
#include "virtual/switch.hpp"
#include "virtual/dimmer.hpp"
#include <iterator>

namespace dv
{
  DeviceManager::DeviceManager()
    : devices_{}
  {}

  DeviceManager::DeviceManager(device_list_t devices)
    : devices_{std::move(devices)}
  {}

  auto DeviceManager::update() -> void
  {
    for (auto& device : devices_)
    {
      device->update();
    }
  }

  [[nodiscard]] auto DeviceManager::get_devices() -> device_list_t
  {
    device_list_t output{};

    { // Switch
      auto device_list = Switch::find_in_env();
      output.insert(
        std::end(output),
        std::make_move_iterator(std::begin(device_list)),
        std::make_move_iterator(std::end(device_list))
      );
    }

    { // Dimmer
      auto device_list = Dimmer::find_in_env();
      output.insert(
        std::end(output),
        std::make_move_iterator(std::begin(device_list)),
        std::make_move_iterator(std::end(device_list))
      );
    }

    return output;
  }
} // dv
