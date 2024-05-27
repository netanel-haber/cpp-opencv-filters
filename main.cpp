#include "./utils.hpp"
#include "opencv2/highgui/highgui.hpp"

auto static constexpr KSIZE = 3;
static_assert(KSIZE % 2 == 1);

void cv_filters(std::string outputMedian, std::string outputGaussian, std::string outputLaplacian) {
  cv::Mat dst;
  auto median_input = cvutils::read_grayscale("input-median.png");
  dst = median_input.clone();
  medianBlur(median_input, dst, KSIZE);
  imwrite(outputMedian, dst);

  auto fabio_input = cvutils::read_grayscale("input-fabio.png");
  dst = fabio_input.clone();
  GaussianBlur(fabio_input, dst, cv::Size {KSIZE, KSIZE}, 1, 1);
  imwrite(outputGaussian, dst);

  dst = fabio_input.clone();
  Laplacian(fabio_input, dst, -1, 5);
  imwrite(outputLaplacian, dst);
}

void our_filters(std::string outputMedian, std::string outputGaussian, std::string outputLaplacian) {
  cv::Mat dst;
  auto median_input = cvutils::read_grayscale("input-median.png");
  dst = cvutils::median_blur(median_input, KSIZE);
  imwrite(outputMedian, dst);

  auto fabio_input = cvutils::read_grayscale("input-fabio.png");
  dst = cvutils::gaussian_blur(fabio_input, KSIZE);
  imwrite(outputGaussian, dst);
}

int main() {
  cv_filters("./build/median.png", "./build/gaussian.png", "./build/laplacian.png");
  our_filters("./build/our_median.png", "./build/our_gaussian.png", "./build/our_laplacian.png");
}