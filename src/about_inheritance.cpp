#include <cstdint>
#include <print>

class PluginBase
{
public:
  PluginBase() : enable_{true} {}
  bool enable_;

  void enable_plugin() { enable_ = true; }
  void disable_plugin() { enable_ = false; }
  bool get_status() { return enable_; }
};

class PluginOne : public PluginBase
{
public:
  const bool& get_local() const { return enable_; };
  const bool& get_base() const { return PluginBase::enable_; };
};

int main ()
{
  PluginBase pb;
  std::println("PluginBase current status: {}", pb.get_status());

  pb.disable_plugin();
  std::println("PluginBase disable plugin: {}", pb.get_status());

  pb.enable_plugin();
  std::println("PluginBase enable plugin: {}", pb.get_status());

  PluginOne one;
  std::println("PluginOne current status: {}", one.get_status());

  one.disable_plugin();
  std::println("PluginOne disable plugin: {}", one.get_status());

  one.enable_plugin();
  std::println("PluginOne enable plugin: {}", one.get_status());

  std::println("local and base are {}",
      (reinterpret_cast<uintptr_t>(&one.get_local())
       == reinterpret_cast<uintptr_t>(&one.get_base())) ? "SAME" : "DIFF");

  return 0;
}
