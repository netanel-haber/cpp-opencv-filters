#include "./utils.hpp"

#include "opencv2/highgui/highgui.hpp"

auto static constexpr KSIZE = 11;

void cv_filters(std::string outputMedian, std::string outputGaussian, std::string outputLaplacian)
{
    auto median_input = cvutils::read_grayscale("../input-median.png");
    auto dst = median_input.clone();
    medianBlur(median_input, dst, KSIZE);
    imwrite(outputMedian, dst);

    auto fabio_input = cvutils::read_grayscale("../input-fabio.png");
    dst = fabio_input.clone();
    GaussianBlur(fabio_input, dst, cv::Size{ KSIZE, KSIZE }, 0);
    imwrite(outputGaussian, dst);

    dst = fabio_input.clone();
    Laplacian(fabio_input, dst, -1, 5);
    imwrite(outputLaplacian, dst);
}

void our_filters(std::string outputMedian, std::string outputGaussian, std::string outputLaplacian)
{
    auto median_input = cvutils::read_grayscale("../input-median.png");
    auto dst = cvutils::median_blur(median_input, KSIZE);
    cvutils::show_image(dst);
}

int main()
{
    cv::namedWindow(cvutils::WINDOW_NAME);
    cv_filters("./median.png", "./gaussian.png", "./laplacian.png");
    our_filters("./our_median.png", "./our_gaussian.png", "./our_laplacian.png");
}