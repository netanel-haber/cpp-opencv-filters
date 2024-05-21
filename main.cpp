#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "./utils.hpp"

using path = std::filesystem::path;

static constexpr auto INPUT_MEDIAN = "../input-median.png";
static constexpr auto OUTPUT_MEDIAN = "./median.png";

void cv_median_filter(path in, path out)
{
    auto image = cvutils::read_grayscale(INPUT_MEDIAN);
    cvutils::print_image_size(image);
}

int main()
{
    cv_median_filter(INPUT_MEDIAN, OUTPUT_MEDIAN);
}