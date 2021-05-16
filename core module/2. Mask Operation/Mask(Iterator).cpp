#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void Sharpen(const Mat& myImage, Mat& Result);

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
    Sharpen(src, result);

    imshow("Input", src);
    imshow("Output", result);
    waitKey();

    return 0;
}
//! [basic_method]
void Sharpen(const Mat& myImage, Mat& Result)
{
    //! [8_bit]
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
  //! [8_bit]

  //! [create_channels]
    const int nChannels = myImage.channels();
    Result.create(myImage.size(), myImage.type());
    //! [create_channels]

    //! [basic_method_loop]
    for (int j = 1; j < myImage.rows - 1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current = myImage.ptr<uchar>(j);
        const uchar* next = myImage.ptr<uchar>(j + 1);

        uchar* output = Result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
        {
            *output++ = saturate_cast<uchar>(5 * current[i]
                - current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
        }
    }
    //! [basic_method_loop]

    //! [borders]
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo((0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
    //! [borders]

}
//! [basic_method]
