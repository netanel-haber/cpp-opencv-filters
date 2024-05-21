#pragma once

#include <opencv2/opencv.hpp>
#include <filesystem>

namespace cvutils
{
    cv::Mat read_grayscale(std::filesystem::path img)
    {
        auto image = imread(img, cv::IMREAD_GRAYSCALE);
        if (image.empty())
        {
            std::cout << "Could not read the image: " << img << std::endl;
            exit(EXIT_FAILURE);
        }
        assert(image.channels() == 1);
        return image;
    }
}