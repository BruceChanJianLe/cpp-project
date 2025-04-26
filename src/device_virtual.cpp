#include <cstdlib>
#include <print>
#include "virtual/device_manager.hpp"

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  std::println("Example: Device Virtual");

  dv::DeviceManager manager(dv::DeviceManager::get_devices());
  manager.update();

  return EXIT_SUCCESS;
}
