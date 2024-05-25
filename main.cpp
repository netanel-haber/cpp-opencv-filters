#include "./utils.hpp"

#include "opencv2/highgui/highgui.hpp"

int main()
{
    cv::namedWindow(cvutils::WINDOW_NAME);
    cvutils::cv_filters("./median.png", "./gaussian.png", "./laplacian.png");
    cvutils::our_filters("./our_median.png", "./our_gaussian.png", "./our_laplacian.png");
}