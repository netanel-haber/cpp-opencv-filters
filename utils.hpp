#pragma once

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <functional>

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

    template <typename... Args>
    using Filter = void (*)(cv::InputArray src, cv::OutputArray dst, Args...);

    template <typename... Args>
    void filter_to_file(cv::Mat input_image, std::filesystem::path out, Filter<Args...> filter, Args... args)
    {
        auto dst = input_image.clone();
        filter(input_image, dst, args...);
        imwrite(out, dst);
    }
}