#include <array>
#include <cstdlib>
#include <print>
#include "nn/mlp.hpp"

int main ([[maybe_unused]] int argc, [[maybe_unused]]  char *argv[]) {

  std::print("---------------- LOGIC GATE (OR) ----------------\n\n");

  nn::Perceptron p(2);
  p.set_weights(std::array{15.0, 15.0, -10.0});

  std::println("Input: [0, 0]");
  std::println("Result: {:.2f}", p.feed_forward(std::array{0.0, 0.0}));

  std::println("Input: [1, 0]");
  std::println("Result: {:.2f}", p.feed_forward(std::array{1.0, 0.0}));

  std::println("Input: [0, 1]");
  std::println("Result: {:.2f}", p.feed_forward(std::array{0.0, 1.0}));

  std::println("Input: [1, 1]");
  std::println("Result: {:.2f}", p.feed_forward(std::array{1.0, 1.0}));

  return EXIT_SUCCESS;
}
