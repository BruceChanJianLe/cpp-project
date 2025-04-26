#include "concept/device_manager.hpp"
#include "concept/switch.hpp"
#include "concept/dimmer.hpp"
#include <cstdlib>

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
  dc::DeviceManager<dc::Switch, dc::Dimmer> manager{};
  manager.update();

  return EXIT_SUCCESS;
}
