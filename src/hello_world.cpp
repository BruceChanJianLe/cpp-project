#include "common/struct_defs.hpp"

#include <fmt/core.h>
#include <fmt/ranges.h>
#include <algorithm>
#include <execution>
#include <cstdlib>

int main() {
    fmt::print("Hello, World!\n");

    fmt::print("fix_data: {}\n", fix_data);

    fmt::print("Squaring them!!!\n");
    std::vector<int> result(fix_data.size());
    std::transform(
        std::execution::par_unseq,
        fix_data.begin(), fix_data.end(), result.begin(),
        [](const int val){ return val * val; });
    fmt::print("result: {}\n", result);

    return EXIT_SUCCESS;
}
