#include "nn/mlp.hpp"

namespace nn
{
  Perceptron::Perceptron(const std::size_t input_size, const double bias)
    : bias{bias}
  {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    weights.resize(input_size + 1);
    std::generate(weights.begin(), weights.end(), [&gen, &dist](){ return dist(gen); });
  }

  double Perceptron::feed_forward(const std::span<const double> input)
  {
    auto feed_forward_result = std::transform_reduce(
        std::execution::par,        // parallel execution
        input.begin(), input.end(), // inputs
        weights.begin(),            // weights
        bias * weights.back()       // bias as initial value
      );
    return sigmoid(feed_forward_result);
  }

  void Perceptron::set_weights(const std::span<const double> w_init)
  {
    std::ranges::copy(w_init.begin(), w_init.end(), weights.begin());
  }

  double Perceptron::sigmoid(const double x)
  {
    return 1.0 / (1.0 + std::exp(-x));
  }

  void Perceptron::print_weights()
  {
    for (const auto& weight : weights) {
      std::print("{}, ", weight);
    }
  }

  MultiLayerPerceptron::MultiLayerPerceptron(const std::vector<std::size_t>& layers, const double bias, const double eta)
    : layers{layers}
    , bias{bias}
    , eta{eta}
  {
    for (auto i = 0uz; i < layers.size(); ++i) {
      // Store for locality
      auto curr_nn_size = layers[i];
      auto prev_nn_size = i ? layers[i] : layers[i - 1];

      // Create perceptrons for current layer
      std::vector<Perceptron> perceptrons;
      perceptrons.reserve(curr_nn_size);
      network.emplace_back(perceptrons);

      if (i > 0) { // network[0] is the input layer, hence no neurons
        for (auto j = 0uz; j < curr_nn_size; ++j) {
          network[i].emplace_back(Perceptron{prev_nn_size, bias});
        }

      // Create place holder for feed forward result
      feed_forward_results.emplace_back(curr_nn_size, 0.0);
      }
    }
  }

  //                        Deep Multi-Layer Perceptron (MLP)
  //
  //        Input Layer     Hidden Layer 1     Hidden Layer 2     Output Layer
  //
  //  row0       (x1) ───┬──► ( h1_1 ) ───┬──► ( h2_1 ) ───┬──► ( y1 )
  //                     │                │                │
  //  row1       (x2) ───┼──► ( h1_2 ) ───┼──► ( h2_2 ) ───┼──► ( y2 )
  //                     │                │                │
  //  row2       (x3) ───┼──► ( h1_3 ) ───┼──► ( h2_3 ) ───┘
  //                     │                │
  //            (bias) ──┘                │
  //                          (bias) ─────┘
  //
  //             depth0        depth1            depth2        depth3
  // columns for accessing the weights

  // Set weights for [depth][rows][cols], excluding the input layer
  void MultiLayerPerceptron::set_weights(const std::mdspan<const double, std::dextents<std::size_t, 3>> w_init)
  {
    for (auto i = 0uz; i != w_init.extent(0); ++i) {
      for (auto j = 0uz; j != w_init.extent(1); ++j) {
        auto data = &w_init[i, j, 0];
        std::span curr_weigths{data, w_init.extent(2)};
        network[i][j].set_weights(curr_weigths);
      }
    }
  }

  void MultiLayerPerceptron::print_weights()
  {
    ;
  }

  std::vector<double> MultiLayerPerceptron::feed_forward(std::vector<double> x)
  {
    return {x};
  }

  double MultiLayerPerceptron::back_propagate(std::vector<double> x, std::vector<double> y)
  {
    return x.front() * y.front();
  }

} // nn
