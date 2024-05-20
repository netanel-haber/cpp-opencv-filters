#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using path = std::filesystem::path;

static constexpr auto INPUT_MEDIAN = "../input-median.png";
static constexpr auto OUTPUT_MEDIAN = "./median.png";

cv::Mat read_grayscale(path img)
{
    auto image = cv::imread(img, cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cout << "Could not read the image: " << img << std::endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

void cv_median_filter(path in, path out)
{
}

void print_image_size(cv::Mat img)
{
    auto size = img.size();
    std::cout << "width: " << size.width << " height: " << size.height << std::endl;
}

int main()
{
    auto image = read_grayscale(INPUT_MEDIAN);
    print_image_size(image);
    // cv_median_filter(INPUT_MEDIAN, OUTPUT_MEDIAN);
}