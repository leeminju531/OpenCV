#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    string filename = "lena.jpg";

    Mat src ;

    src = imread(filename, IMREAD_GRAYSCALE);
    // src = imread(samples::findFile(filename), IMREAD_COLOR);

    if (src.empty())
    {
        cerr << "Can't open image [" << filename << "]" << endl;
        return 1;
    }

    Mat result;
    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    filter2D(src, result, src.depth(), kernel);

    imshow("Input", src);
    imshow("Output", result);
    waitKey();
  
    return 0;
}
