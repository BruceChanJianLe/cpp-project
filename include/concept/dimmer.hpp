#pragma once

#include "concept/device_concept.hpp"
#include <cstdint>
#include <string>

namespace dc
{
  class Dimmer
  {
  public:
    using value_type = Dimmer;
    Dimmer(const std::string& dimmer_name);

    [[nodiscard]] static auto find_in_env() -> std::vector<Dimmer>;
   auto update() -> void;
  private:
    std::string dimmer_name_;
    uint_fast8_t brightness_;
  };

  static_assert(CDevice<Dimmer>);
} // dc
