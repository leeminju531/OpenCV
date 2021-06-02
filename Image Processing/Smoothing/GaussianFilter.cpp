#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
    const char* filename = "lena.jpg";

    Mat src = imread(filename, IMREAD_COLOR);
    if (src.empty())
    {
        cout << filename << "Load Fail"<<endl;
        return EXIT_FAILURE;
    }

    Mat dst = src.clone();
 
    //![blur]
    GaussianBlur(src, dst, Size(21,21),0,0);

    imshow("Origin", src);
    imshow("median Filter", dst);
    waitKey(0);
    
    return 0;
}

