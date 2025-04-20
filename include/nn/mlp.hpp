#pragma once

#include <cstddef>
#include <vector>
#include <random>
#include <span>
#include "experimental/__p0009_bits/mdspan.hpp"
#include <ranges>
#include <algorithm>
#include <execution>
#include <print>
#include <ranges>
#include <sstream>

namespace nn
{
  namespace stdex = std::experimental;
  struct Perceptron {
    Perceptron(const std::size_t _inputs, const double _bias = 1.0);
    double feed_forward(const std::span<const double> input);
    void set_weights(const std::span<const double> w_init);
    double sigmoid(const double value);
    void print_weights();

    std::vector<double> weights;
    double bias;
  };

  struct MultiLayerPerceptron {
    MultiLayerPerceptron(const std::vector<std::size_t>& _layers, const double _bias = 1.0, const double _eta = 0.5);
    void set_weights(const std::vector<std::vector<std::vector<double>>>& w_init);
    void set_weights(const stdex::mdspan<const double, std::experimental::dextents<std::size_t, 3>> w_init);
    void print_weights();

    std::vector<double> feed_forward(const std::span<const double> input);
    double back_propagate(const std::span<const double> input,const std::span<const double> ground_truth);

    /// number of neurons for each layer
    /// layers[0]: number of input elements (input layer with no neurons)
    std::vector<std::size_t> layers; 
    double bias;
    /// Learning Rate
    double eta;
    std::vector<std::vector<Perceptron>> network;
    std::vector<std::vector<double>> feed_forward_results;
    std::vector<std::vector<double>> delta_errors;
  };


  // Helper function to flatten a nested 3D vector
  std::vector<double> flatten_3d(const std::vector<std::vector<std::vector<double>>>& nested);

} // nn
