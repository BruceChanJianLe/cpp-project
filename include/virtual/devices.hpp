#pragma once

#include <vector>
#include <memory>

namespace dv
{
  class DeviceInterface;
  using device_list_t = std::vector<std::unique_ptr<DeviceInterface>>;

  class DeviceInterface
  {
  public:
    DeviceInterface();
    virtual ~DeviceInterface() = default;

    // Copy constructor
    DeviceInterface (const DeviceInterface &) = default;
    // Copy assignment
    DeviceInterface &operator=(DeviceInterface &) = default;

    // Move constructor
    DeviceInterface (DeviceInterface &&) noexcept = default;
    // Move assignment
    DeviceInterface &operator=(DeviceInterface &&) noexcept = default;

    virtual auto update() -> void = 0;
  };
} // dv
