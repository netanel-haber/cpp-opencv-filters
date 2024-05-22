#include <opencv2/opencv.hpp>
#include "./utils.hpp"

auto KSIZE = 5;

int main()
{
    using namespace cv;

    auto median_input = cvutils::read_grayscale("../input-median.png");
    auto dst = median_input.clone();
    medianBlur(median_input, dst, KSIZE);
    imwrite("./median.png", dst);

    auto fabio_input = cvutils::read_grayscale("../input-fabio.png");
    dst = fabio_input.clone();
    GaussianBlur(fabio_input, dst, Size{KSIZE, KSIZE}, 0);
    imwrite("./fabio.png", dst);
}