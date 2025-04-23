#include "experimental/__p0009_bits/extents.hpp"
#include "experimental/__p0009_bits/mdspan.hpp"
#include "nn/mlp.hpp"
#include <cstdlib>

int main ([[maybe_unused]] int argc,[[maybe_unused]]  char *argv[]) {

  std::print("---------------- LOGIC GATE (XOR) ----------------\n\n");

  nn::MultiLayerPerceptron mlp({2, 2, 1});
  std::vector<std::vector<std::vector<double>>> raw_presets{{{-10.0, -10.0, 15.0}, {15.0, 15.0, -10.0}}, {{10.0, 10.0, -15.0}}};
  // auto presets = nn::flatten_3d(raw_presets);
  // std::experimental::mdspan<const double, std::experimental::dextents<std::size_t, 3>> presets_view(presets.data(), 2, 2, 3);
  mlp.set_weights(raw_presets);
  std::println("Hardcoded weigths:");
  mlp.print_weights();

  std::println("\nHardcoded Test:");
  std::println("0 0 = {}", mlp.feed_forward(std::array{0.0,0.0})[0]);
  std::println("0 1 = {}", mlp.feed_forward(std::array{0.0,1.0})[0]);
  std::println("1 0 = {}", mlp.feed_forward(std::array{1.0,0.0})[0]);
  std::println("1 1 = {}", mlp.feed_forward(std::array{1.0,1.0})[0]);

  std::println("\nNeural Network to be trained:");
  nn::MultiLayerPerceptron mlp2({2, 2, 1});

  std::println("\nWeights before training");
  mlp2.print_weights();

  std::println("\n\nTraining Neural Network as an XOR (3000 epoch)");
  std::println("\n\n==============================================");

  double mse{0.0};
  for (auto i = 0uz; i < 3000; ++i) {
    mse += mlp2.back_propagate(std::array{0.0, 0.0}, std::array{0.0});
    mse += mlp2.back_propagate(std::array{1.0, 0.0}, std::array{1.0});
    mse += mlp2.back_propagate(std::array{0.0, 1.0}, std::array{1.0});
    mse += mlp2.back_propagate(std::array{1.0, 1.0}, std::array{0.0});
    mse /= 4.0;

    if (i % 100 == 0) {
      std::println("mse({}): {}",i , mse);
    }
  }

  std::println("\nWeights after training:");
  mlp2.print_weights();

  std::println("\nTrained Test:");
  std::println("0 0 = {}", mlp2.feed_forward(std::array{0.0,0.0})[0]);
  std::println("0 1 = {}", mlp2.feed_forward(std::array{0.0,1.0})[0]);
  std::println("1 0 = {}", mlp2.feed_forward(std::array{1.0,0.0})[0]);
  std::println("1 1 = {}", mlp2.feed_forward(std::array{1.0,1.0})[0]);

  return EXIT_SUCCESS;
}
