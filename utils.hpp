#pragma once

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>
#include <assert.h>
#include <stddef.h>
#include <iostream>


namespace cvutils
{
using Img = cv::Mat;

auto constexpr WINDOW_NAME = "Display Image";
void show_image(const Img& img)
{
    cv::imshow(WINDOW_NAME, img);
    cv::waitKey(3000);
}

Img read_grayscale(std::filesystem::path img)
{
    auto image = cv::imread(img, cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cout << "Could not read the image: " << img << std::endl;
        exit(EXIT_FAILURE);
    }
    assert(image.channels() == 1);
    return image;
}

Img pad(const Img& src, int ksize)
{
    auto border = (ksize - 1) / 2;
    Img padded;
    cv::copyMakeBorder(src, padded, border, border, border, border, cv::BORDER_CONSTANT, 0);
    assert((src.rows + (border * 2)) == padded.rows);
    assert((src.cols + (border * 2)) == padded.cols);
    return padded;
}

/*
Median for even number of elements cannot use `nth_element`, it needs a mean of the two middle elements.
We take advantage of kernels always being odd sized=odd number of elements.
*/
int mutating_median_odd_vector(std::vector<uint8_t>& v)
{
    auto size = v.size();
    assert(size % 2 == 1);
    size_t n = size / 2;
    std::nth_element(v.begin(), v.begin() + n, v.end());
    return v[n];
}

Img median_blur(const Img& src, int ksize)
{
    Img dst = src.clone();
    Img padded = pad(src, ksize);

    auto kernel_size = ksize * ksize;
    std::vector<uint8_t> kernel = std::vector<uint8_t>(kernel_size);

    auto padding = (ksize - 1) / 2;

    for (auto r = padding; r < padded.rows - padding; r++)
    {
        for (auto c = padding; c < padded.cols - padding; c++)
        {
            for (auto i = 0; i < kernel_size; i++)
                kernel[i] = padded.at<uint8_t>(r + floor(i / ksize), c + (i % ksize));
            dst.at<uint8_t>(r - padding, c - padding) = mutating_median_odd_vector(kernel);
        }
    }
    return dst;
}


}