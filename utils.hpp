#pragma once

#include <opencv2/opencv.hpp>
#include <filesystem>

namespace cvutils
{
    using namespace cv;

    void print_image_size(Mat img)
    {
        auto size = img.size();
        std::cout << "width: " << size.width << " height: " << size.height << std::endl;
    }

    Mat read_grayscale(std::filesystem::path img)
    {
        auto image = imread(img, cv::IMREAD_GRAYSCALE);
        if (image.empty())
        {
            std::cout << "Could not read the image: " << img << std::endl;
            exit(EXIT_FAILURE);
        }
        return image;
    }
}