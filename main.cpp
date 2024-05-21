#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "./utils.hpp"

using path = std::filesystem::path;

static constexpr auto INPUT_MEDIAN = "../input-median.png";
static constexpr auto OUTPUT_MEDIAN = "./median.png";
static constexpr auto KSIZE = 9;

int main()
{
    auto median_input = cvutils::read_grayscale(INPUT_MEDIAN);
    cvutils::filter_to_file(median_input, OUTPUT_MEDIAN, cv::medianBlur, KSIZE);
}