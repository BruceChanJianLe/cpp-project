#include "nn/mlp.hpp"
#include <algorithm>
#include <ranges>

namespace nn
{
  Perceptron::Perceptron(const std::size_t _input_size, const double _bias)
    : bias{_bias}
  {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    weights.resize(_input_size + 1);
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

  double Perceptron::sigmoid(const double value)
  {
    return 1.0 / (1.0 + std::exp(-value));
  }

  void Perceptron::print_weights()
  {
    for (const auto& weight : weights) {
      std::print("{:.2f}, ", weight);
    }
  }

  MultiLayerPerceptron::MultiLayerPerceptron(const std::vector<std::size_t>& _layers, const double _bias, const double _eta)
    : layers{_layers}
    , bias{_bias}
    , eta{_eta}
  {
    for (auto i = 0uz; i < layers.size(); ++i) {
      // Store for locality
      auto curr_nn_size = layers[i];
      auto prev_nn_size = i ? layers[i - 1] : layers[i];

      // Create perceptrons for current layer
      std::vector<Perceptron> perceptrons;
      perceptrons.reserve(curr_nn_size);
      network.emplace_back(perceptrons);

      if (i > 0) { // network[0] is the input layer, hence no neurons
        for (auto j = 0uz; j < curr_nn_size; ++j) {
          network[i].emplace_back(Perceptron{prev_nn_size, bias});
        }
      }

      // Create place holder for feed forward result
      feed_forward_results.emplace_back(curr_nn_size, 0.0);
      // Create place holder where delta errors are store
      delta_errors.emplace_back(curr_nn_size, 0.0);
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
  void MultiLayerPerceptron::set_weights(const stdex::mdspan<const double, stdex::dextents<std::size_t, 3>> w_init)
  {
    auto indexes = std::views::cartesian_product(
        std::views::iota(0uz, w_init.extent(0)),
        std::views::iota(0uz, w_init.extent(1))
      );

    std::for_each(std::execution::par_unseq,
      indexes.begin(), indexes.end(),
      [this,&w_init](const auto index) {
        auto& [i, j] = index;
        // Break into smaller steps for future ref
        auto data = &w_init[i, j, 0];
        std::span curr_weigths{data, w_init.extent(2)};
        network[i][j].set_weights(curr_weigths);
      }
    );
  }

  void MultiLayerPerceptron::set_weights(const std::vector<std::vector<std::vector<double>>>& w_init)
  {
    for (auto i = 0uz; i < w_init.size(); i++) {
      for (auto j = 0uz; j < w_init[i].size(); j++) {
        network[i + 1][j].set_weights(w_init[i][j]);
      }
    }
  }

  void MultiLayerPerceptron::print_weights()
  {
    auto indexes = std::views::iota(1uz, network.size());
    std::for_each(indexes.begin(), indexes.end(),
      [this](const auto index) {
        std::println("Layer {}", index);
        std::println("========", index);
        for (auto i = 0uz; i < layers[index]; ++i) {
          std::stringstream ss;
          for (const auto& weight : network[index][i].weights) {
            ss << std::format("{:.2f}", weight) << ", ";
          }
          std::println("Neuron {}: weights = [ {}]", i, ss.str());
        }
        return;
      }
    );
  }

  std::vector<double> MultiLayerPerceptron::feed_forward(const std::span<const double> input)
  {
    // Copy over input input feed_forward_results 
    // and use it as input to first hidden layer
    std::ranges::copy(input.begin(), input.end(), feed_forward_results.front().begin());

    auto indexes = std::views::iota(1uz, network.size());
    std::for_each(std::execution::seq,
      indexes.begin(), indexes.end(),
      [this](const auto index) {
        for (auto i = 0uz; i < layers[index]; ++i) {
          feed_forward_results[index][i] = network[index][i].feed_forward(feed_forward_results[index - 1]);
        }
      }
    );
    return feed_forward_results.back();
  }

  double MultiLayerPerceptron::back_propagate(const std::span<const double> input,const std::span<const double> ground_truth)
  {
    // Backpropagation:

    // Step 1: Compute feed forward result
    auto outputs = feed_forward(input);

    // Step 2: Calculate MSE
    if (outputs.size() != ground_truth.size()) {
      std::println("Mismatch in size of feed forward results and labels!");
      return -9999.9999;
    }

    auto indexes = std::views::iota(0uz, outputs.size());
    std::vector<double> error(indexes.size());
    double mse = std::transform_reduce(std::execution::par_unseq,
      indexes.begin(), indexes.end(),
      error.begin(), 0.0,
      std::plus<>(),
      [&outputs, &ground_truth](auto index, auto& err) {
        err = ground_truth[index] - outputs[index];
        return err * err;
      }
    );

    // Step 3: Calculate error term (output neuron)
    std::for_each(std::execution::par_unseq,
      indexes.begin(), indexes.end(),
      [this, &outputs, &error](const auto index) {
        delta_errors.back()[index] =
          outputs[index] * (1 - outputs[index]) * error[index];
      }
    );

    // Step 4: Calculate error term (hidden layer)
    auto reverse_indexes = std::views::iota(0uz, network.size())
      | std::views::take(network.size() - 1) // take away the last layer
      | std::views::reverse; // reverse from back to front

    std::for_each(std::execution::par_unseq,
      reverse_indexes.begin(), reverse_indexes.end(),
      [this](const auto index) {
        for (auto h = 0uz; h < network[index].size(); ++h) {
          double ff_error{0.0};
          for (auto k = 0uz; k < layers[index + 1]; ++k) {
            ff_error +=
              network[index + 1][k].weights[h] * delta_errors[index + 1][k];
          }
          delta_errors[index][h] =
            feed_forward_results[index][h] * (1 - feed_forward_results[index][h]) * ff_error;
        }
      }
    );

    // Step 5 & 6: Apply delta rule to update weights
    for (auto i = 1uz; i < network.size(); ++i) {
      for (auto j = 0uz; j < layers[i]; ++j) {
        for (auto k = 0uz; k < layers[i - 1] + 1; ++k) {
          if (k == layers[i - 1]) {
            network[i][j].weights[k] += eta * delta_errors[i][j] * bias;
          } else {
            network[i][j].weights[k] += eta * delta_errors[i][j] * feed_forward_results[i - 1][k];
          }
        }
      }
    }

    return mse / static_cast<double>(layers.back());
  }

  std::vector<double> flatten_3d(const std::vector<std::vector<std::vector<double>>>& nested) {
    std::vector<double> flat(nested.size() * nested.front().size() * nested.front().front().size());
    for (const auto& mat : nested) {
      for (const auto& row : mat) {
        for (const auto& val : row) {
          flat.push_back(val);
        }
      }
    }
    return flat;
  }
} // nn
