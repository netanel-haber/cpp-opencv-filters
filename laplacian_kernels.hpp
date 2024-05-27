#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace {
// clang-format off
constexpr std::array<int8_t, 9> laplacian3x3 = {
    0, -1,  0,
    -1, 4,  -1,
    0,  -1,  0
};

constexpr std::array<int8_t, 25> laplacian5x5 = {
    0,  0, -1,  0,  0,
    0, -1, -2, -1,  0,
   -1, -2, 16, -2, -1,
    0, -1, -2, -1,  0,
    0,  0, -1,  0,  0
};

constexpr std::array<int8_t, 49> laplacian7x7 = {
    0,   0,   -1,  -1,  -1,  0,   0,
    0,   -1,  -3,  -3,  -3,  -1,  0,
    -1,  -3,  0,   7,   0,   -3,  -1,
    -1,  -3,  7,   24,  7,   -3,  -1,
    -1,  -3,  0,   7,   0,   -3,  -1,
    0,   -1,  -3,  -3,  -3,  -1,  0,
    0,   0,   -1,  -1,  -1,  0,   0
};

constexpr std::array<int8_t, 81> laplacian9x9 = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, 80, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1
};

constexpr std::array<int8_t, 121> laplacian11x11 = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 120,-1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};
// clang-format on

auto constexpr MAX_LAPLACIAN_KSIZE = 11;

// clang-format off
constexpr std::array<const int8_t*, MAX_LAPLACIAN_KSIZE + 1> laplacian_kernel_lookup = { // + 1 so we can lookup nicely.
    nullptr,
    nullptr,
    nullptr,
    laplacian3x3.data(),
    nullptr,
    laplacian5x5.data(),
    nullptr,
    laplacian7x7.data(),
    nullptr,
    laplacian9x9.data(),
    nullptr,
    laplacian11x11.data()
};
// clang-format on

} // namespace

std::vector<int8_t> laplacian_kernel(int ksize) {
  assert(3 <= ksize && ksize <= MAX_LAPLACIAN_KSIZE);
  assert(ksize % 2 == 1);

  auto kernel = laplacian_kernel_lookup[ksize];
  if (!kernel)
    throw std::runtime_error("The asserts above should have caught this...");

  return std::vector<int8_t> {kernel, kernel + ksize * ksize};
}