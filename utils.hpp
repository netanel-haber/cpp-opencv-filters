#pragma once

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>
#include <assert.h>
#include <stddef.h>
#include <iostream>

auto static constexpr KSIZE = 11;

namespace cvutils
{
    using namespace cv;

    auto constexpr WINDOW_NAME = "Display Image";
    void show_image(const Mat &img)
    {
        imshow(WINDOW_NAME, img);
        waitKey(3000);
    }

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

    Mat pad(const Mat &src, int ksize)
    {
        auto border = (ksize - 1) / 2;
        Mat padded;
        copyMakeBorder(src, padded, border, border, border, border, BORDER_CONSTANT, 0);
        assert((src.rows + (border * 2)) == padded.rows);
        assert((src.cols + (border * 2)) == padded.cols);

        return padded;
    }

    Mat median_blur(const Mat &src, int ksize)
    {
        Mat dst = src.clone();
        Mat padded = pad(src, ksize);

        auto padding = (ksize - 1) / 2;
        for (auto r = padding; r < padded.rows - padding; r++)
        {
            for (auto c = padding; c < padded.cols - padding; c++)
            {
                int sum = 0;
                for (auto i = r - padding; i < r + padding + 1; i++)
                {
                    for (auto j = c - padding; j < c + padding + 1; j++)
                    {
                        sum += padded.at<uint8_t>(i, j);
                    }
                }
                dst.at<uint8_t>(r - padding, c - padding) = sum / (ksize * ksize);
            }
        }
        return dst;
    }

    void our_filters(std::string outputMedian, std::string outputGaussian, std::string outputLaplacian)
    {
        auto median_input = cvutils::read_grayscale("../input-median.png");
        Mat dst = median_blur(median_input, KSIZE);
        show_image(dst);
    }
}