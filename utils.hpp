#pragma once

#include <assert.h>
#include <stddef.h>

#include <filesystem>
#include <iostream>
#include <numeric>
#include <opencv2/opencv.hpp>
#include <string>

#include "./gaussian_kernels.hpp"
#include "./laplacian_kernels.hpp"

namespace {
using Img = cv::Mat;
Img pad(const Img& src, int ksize) {
  auto border = (ksize - 1) / 2;
  Img padded;
  cv::copyMakeBorder(src, padded, border, border, border, border, cv::BORDER_CONSTANT, 0);
  assert((src.rows + (border * 2)) == padded.rows);
  assert((src.cols + (border * 2)) == padded.cols);
  return padded;
}

Img op_on_windows(const Img& src, int ksize, std::function<uint8_t(std::vector<uint8_t>&)> operation_on_window) {
  auto dst = src.clone();
  auto padded = pad(src, ksize);
  auto padding = (ksize - 1) / 2;
  auto klength = ksize * ksize;
  auto window = std::vector<uint8_t>(klength);
  for (auto r = padding; r < padded.rows - padding; r++)
  {
    for (auto c = padding; c < padded.cols - padding; c++)
    {
      for (auto i = 0; i < klength; i++)
        window[i] = padded.at<uint8_t>(r + floor(i / ksize), c + (i % ksize));
      dst.at<uint8_t>(r - padding, c - padding) = operation_on_window(window);
    }
  }
  return dst;
}

template <typename T>
Img convolve(const Img& src, const std::vector<T>& kernel) {
  auto ksize = static_cast<int>(floor(sqrt(kernel.size())));
  return op_on_windows(src, ksize, [kernel](std::vector<uint8_t> window) {
    auto product = static_cast<uint8_t>(std::inner_product(window.begin(), window.end(), kernel.begin(), 0.0));
    return product;
  });
}
} // namespace

namespace cvutils {
using Img = cv::Mat;
Img read_grayscale(std::filesystem::path img) {
  auto image = cv::imread(img, cv::IMREAD_GRAYSCALE);
  if (image.empty())
  {
    std::cout << "Could not read the image: " << img << std::endl;
    exit(EXIT_FAILURE);
  }
  assert(image.channels() == 1);
  return image;
}

/*
Median for even number of elements cannot use `nth_element`, it needs a mean of
the two middle elements. We take advantage of kernels always being odd sized=odd
number of elements.
*/
Img median_blur(const Img& src, int ksize) {
  assert(ksize % 2 == 1);
  auto medianth_index = (ksize * ksize) / 2;
  return op_on_windows(src, ksize, [medianth_index](auto window) {
    std::nth_element(window.begin(), window.begin() + medianth_index, window.end());
    return window[medianth_index];
  });
}

Img gaussian_blur(const Img& src, int ksize) {
  auto kernel = gaussian_kernel(ksize);
  return convolve(src, kernel);
}

Img laplacian_blur(const Img& src, int ksize) {
  auto kernel = laplacian_kernel(ksize);
  return convolve(src, kernel);
}

} // namespace cvutils