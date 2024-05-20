#include <iostream>
#include <filesystem>

using path = std::filesystem::path;

static constexpr auto INPUT_MEDIAN = "./input-median.png";
static constexpr auto OUTPUT_MEDIAN = "./median.png";

void cv_median_filter(path in, path out){

}


int main(){
    std::cout << "hello world";
    cv_median_filter(INPUT_MEDIAN, OUTPUT_MEDIAN);
}