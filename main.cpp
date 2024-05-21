#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "./utils.hpp"

using path = std::filesystem::path;

static constexpr auto INPUT_MEDIAN = "../input-median.png";
static constexpr auto OUTPUT_MEDIAN = "./median.png";
static constexpr auto KSIZE = 3;

void cv_median_filter(path in, path out, int ksize = KSIZE)
{
    auto image = cvutils::read_grayscale(INPUT_MEDIAN);
    cvutils::filter_to_file(image, OUTPUT_MEDIAN, cv::medianBlur, ksize);
}

int main()
{
    cv_median_filter(INPUT_MEDIAN, OUTPUT_MEDIAN);
}