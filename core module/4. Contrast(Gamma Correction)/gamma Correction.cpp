
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;
int main(int argc, char** argv)
{

    Mat image = imread("minju.jpg");
    if (image.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        return -1;
    }

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    double gamma_ = 0.4;
    for (int i = 0; i < 256; ++i)
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
    Mat new_image ;
    LUT(image, lookUpTable, new_image);


    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();
    return 0;
}