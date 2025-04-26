#pragma once

#include <string>

#include "concept/device_concept.hpp"

namespace dc
{
  class Switch
  {
  public:
    Switch(const std::string& switch_name);
    [[nodiscard]] static auto find_in_env() -> std::vector<Switch>;
    auto update() -> void;

  private:
    std::string switch_name_;
    bool is_on_;
  };

  static_assert(CDevice<Switch>);
} // dc
