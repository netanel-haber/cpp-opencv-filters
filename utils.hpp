#pragma once

#include <opencv2/opencv.hpp>
#include <filesystem>

auto static constexpr KSIZE = 5;

namespace cvutils
{
    using namespace cv;
    Mat read_grayscale(std::filesystem::path img)
    {
        auto image = imread(img, IMREAD_GRAYSCALE);
        if (image.empty())
        {
            std::cout << "Could not read the image: " << img << std::endl;
            exit(EXIT_FAILURE);
        }
        assert(image.channels() == 1);
        return image;
    }

    void cv_filters(std::string outputMedian, std::string outputGaussian, std::string outputLaplacian)
    {

        auto median_input = cvutils::read_grayscale("../input-median.png");
        auto dst = median_input.clone();
        medianBlur(median_input, dst, KSIZE);
        imwrite(outputMedian, dst);

        auto fabio_input = cvutils::read_grayscale("../input-fabio.png");
        dst = fabio_input.clone();
        GaussianBlur(fabio_input, dst, Size{KSIZE, KSIZE}, 0);
        imwrite(outputGaussian, dst);

        dst = fabio_input.clone();
        Laplacian(fabio_input, dst, -1, 5);
        imwrite(outputLaplacian, dst);
    }
}