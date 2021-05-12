#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);

int main()
{
    string img_path = "starry_night.jpg";
    Mat I = imread(img_path, IMREAD_GRAYSCALE);
    if (I.empty())
    {
        cout << "The image" << img_path << " could not be loaded." << endl;
        return -1;
    }
    int divideWith = 50;
    uchar table[256];
    for (int i = 0; i < 256; ++i)
        table[i] = (uchar)(divideWith * (i / divideWith));
   
    double before_t = (double)getTickCount();

    const int times = 100;
    Mat J;
    for (int i = 0; i < times; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
    }

    double after_t = (double)getTickCount();
    double t = (after_t - before_t) / getTickFrequency();
    
    cout << "Time of reducing with the C operator [] (averaged for "
        << times << " runs): " << t << " seconds." << endl;
    return 0;
}
////! [scan-c]
Mat& ScanImageAndReduceC(Mat& I, const uchar* table)
{
    // cv_assert(expr)
    // cv_assert()는 opencv에서 제공하는 매크로 함수
    // 괄호 안의 조건식이 참(true)이면 정상적으로 함수를 진행
    // 거짓(false)이면 에러를 발생(커맨드창에 에러 메시지를 출력)
    CV_Assert(I.depth() == CV_8U);
    // 1byte unsighned char 형식을 허용하겠다는 의미
    
    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols * channels;
    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }
    int i, j;
    uchar* p;
    for (i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }
    return I;
}