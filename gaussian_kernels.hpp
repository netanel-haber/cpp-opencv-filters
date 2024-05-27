#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace { // Basically like using `static` [only visible at module level] on all top level identifiers:
            // https://llvm.org/docs/CodingStandards.html#anonymous-namespaces
template <size_t N>
constexpr std::array<float, N> normalize_kernel(const std::array<uint8_t, N>& kernel) {
  std::array<float, N> normalizedKernel {};
  uint8_t sum = 0;
  for (auto el : kernel)
    sum += el;
  for (size_t i = 0; i < N; ++i)
    normalizedKernel[i] = static_cast<float>(kernel[i]) / sum;
  return normalizedKernel;
}

// clang-format off
constexpr std::array<uint8_t, 9> gaussian3x3 = {
    1, 2, 1,
    2, 40, 2,
    1, 2, 1
};

constexpr std::array<uint8_t, 25> gaussian5x5 = {
    1,  4,  7,  4, 1,
    4, 16, 26, 16, 4,
    7, 26, 41, 26, 7,
    4, 16, 26, 16, 4,
    1,  4,  7,  4, 1
};

constexpr std::array<uint8_t, 49> gaussian7x7 = {
    1,  4,  7, 11,  7,  4,  1,
    4, 20, 33, 50, 33, 20,  4,
    7, 33, 55, 83, 55, 33,  7,
    11, 50, 83,125, 83, 50, 11,
    7, 33, 55, 83, 55, 33,  7,
    4, 20, 33, 50, 33, 20,  4,
    1,  4,  7, 11,  7,  4,  1
};

constexpr std::array<uint8_t, 81> gaussian9x9 = {
    1,  3,  7, 12, 15, 12,  7,  3,  1,
    3, 12, 26, 41, 52, 41, 26, 12,  3,
    7, 26, 55, 85,105, 85, 55, 26,  7,
    12, 41, 85,135,165,135, 85, 41, 12,
    15, 52,105,165,200,165,105, 52, 15,
    12, 41, 85,135,165,135, 85, 41, 12,
    7, 26, 55, 85,105, 85, 55, 26,  7,
    3, 12, 26, 41, 52, 41, 26, 12,  3,
    1,  3,  7, 12, 15, 12,  7,  3,  1
};

constexpr std::array<uint8_t, 121> gaussian11x11 = {
    1,  2,  4,  8, 11, 12, 11,  8,  4,  2,  1,
    2,  5,  9, 18, 26, 28, 26, 18,  9,  5,  2,
    4,  9, 17, 33, 49, 54, 49, 33, 17,  9,  4,
    8, 18, 33, 65, 96,107, 96, 65, 33, 18,  8,
    11,26, 49, 96,143,160,143, 96, 49, 26, 11,
    12,28, 54,107,160,178,160,107, 54, 28, 12,
    11,26, 49, 96,143,160,143, 96, 49, 26, 11,
    8, 18, 33, 65, 96,107, 96, 65, 33, 18,  8,
    4,  9, 17, 33, 49, 54, 49, 33, 17,  9,  4,
    2,  5,  9, 18, 26, 28, 26, 18,  9,  5,  2,
    1,  2,  4,  8, 11, 12, 11,  8,  4,  2,  1
};
// clang-format on

auto constexpr normalized3X3 = normalize_kernel(gaussian3x3);
auto constexpr normalized5X5 = normalize_kernel(gaussian5x5);
auto constexpr normalized7X7 = normalize_kernel(gaussian7x7);
auto constexpr normalized9X9 = normalize_kernel(gaussian9x9);
auto constexpr normalized11X11 = normalize_kernel(gaussian11x11);

auto constexpr MAX_GAUSSIAN_KSIZE = 11;

// clang-format off
constexpr std::array<const float*, MAX_GAUSSIAN_KSIZE + 1> gaussian_kernel_lookup = { // + 1 so we can lookup nicely.
    nullptr,
    nullptr,
    nullptr,
    normalized3X3.data(),
    nullptr,
    normalized5X5.data(),
    nullptr,
    normalized7X7.data(),
    nullptr,
    normalized9X9.data(),
    nullptr,
    normalized11X11.data()
};
// clang-format on

} // namespace

std::vector<float> gaussian_kernel(int ksize) {
  assert(ksize <= 3);
  assert(ksize <= MAX_GAUSSIAN_KSIZE);
  assert(ksize % 2 == 1);

  const float* kernel = gaussian_kernel_lookup[ksize];
  if (!kernel)
    throw std::runtime_error("The asserts above should have caught this...");

  return std::vector<float> {kernel, kernel + ksize * ksize};
}