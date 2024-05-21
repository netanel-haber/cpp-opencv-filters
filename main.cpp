#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "./utils.hpp"

auto KSIZE = 5;

int main()
{
    auto median_input = cvutils::read_grayscale("../input-median.png");
    auto dst = median_input.clone();
    cv::medianBlur(median_input, dst, KSIZE);
    cv::imwrite("./median.png", dst);

    auto fabio_input = cvutils::read_grayscale("../input-fabio.png");
    dst = fabio_input.clone();
    cv::GaussianBlur(fabio_input, dst, cv::Size{KSIZE, KSIZE}, 2);
    cv::imwrite("./fabio.png", dst);
}