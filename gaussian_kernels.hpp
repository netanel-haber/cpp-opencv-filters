#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <cassert>
#include <vector>

template <size_t N>
static constexpr std::array<float, N> normalize_kernel(const std::array<uint8_t, N>& kernel) {
    std::array<float, N> normalizedKernel{};
    uint8_t sum = 0;
    for (auto el : kernel) sum += el;
    for (size_t i = 0; i < N; ++i) normalizedKernel[i] = static_cast<float>(kernel[i]) / sum;
    return normalizedKernel;
}

// 3x3 Gaussian Kernel
static constexpr std::array<uint8_t, 9> gaussianKernel3x3 = {
    1, 2, 1,
    2, 40, 2,
    1, 2, 1
};

// 5x5 Gaussian Kernel
static constexpr std::array<uint8_t, 25> gaussianKernel5x5 = {
    1,  4,  7,  4, 1,
    4, 16, 26, 16, 4,
    7, 26, 41, 26, 7,
    4, 16, 26, 16, 4,
    1,  4,  7,  4, 1
};

// 7x7 Gaussian Kernel
static constexpr std::array<uint8_t, 49> gaussianKernel7x7 = {
    1,  4,  7, 11,  7,  4,  1,
    4, 20, 33, 50, 33, 20,  4,
    7, 33, 55, 83, 55, 33,  7,
    11, 50, 83,125, 83, 50, 11,
    7, 33, 55, 83, 55, 33,  7,
    4, 20, 33, 50, 33, 20,  4,
    1,  4,  7, 11,  7,  4,  1
};

// 9x9 Gaussian Kernel
static constexpr std::array<uint8_t, 81> gaussianKernel9x9 = {
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

// 11x11 Gaussian Kernel
static constexpr std::array<uint8_t, 121> gaussianKernel11x11 = {
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

static auto constexpr k3X3 = normalize_kernel(gaussianKernel3x3);
static auto constexpr k5X5 = normalize_kernel(gaussianKernel5x5);
static auto constexpr k7X7 = normalize_kernel(gaussianKernel7x7);
static auto constexpr k9X9 = normalize_kernel(gaussianKernel9x9);
static auto constexpr k11X11 = normalize_kernel(gaussianKernel11x11);

static auto constexpr MAX_GAUSSIAN_KSIZE = 11;

static constexpr std::array<const float*, MAX_GAUSSIAN_KSIZE + 1> gaussian_kernel_lookup = { // + 1 so we can lookup nicely.
    nullptr,
    nullptr,
    nullptr,
    k3X3.data(),
    nullptr,
    k5X5.data(),
    nullptr,
    k7X7.data(),
    nullptr,
    k9X9.data(),
    nullptr,
    k11X11.data()
};


std::vector<float> produce_gaussian_kernel(int ksize) {
    assert(ksize <= 3);
    assert(ksize <= MAX_GAUSSIAN_KSIZE);
    assert(ksize % 2 == 1);

    const float* kernel = gaussian_kernel_lookup[ksize];

    return std::vector<float>{kernel, kernel + ksize * ksize};
}