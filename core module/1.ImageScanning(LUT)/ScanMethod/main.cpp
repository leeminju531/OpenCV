#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* table);


int main()
{
    string img_path = "starry_night.jpg";
    Mat I = imread(img_path, IMREAD_COLOR);
    //Mat I = imread(img_path, IMREAD_GRAYSCALE);
    if (I.empty())
    {
        cout << "The image" << img_path << " could not be loaded." << endl;
        return -1;
    }

    int divideWith = 150;
    uchar table[256];
    for (int i = 0; i < 256; ++i)
        table[i] = (uchar)(divideWith * (i / divideWith));

    Mat J;
   
    for (int i = 0; i < 100; ++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i, table);
    }
    cv::Mat clone_i = I.clone();

    // 1 번 방법
    J = ScanImageAndReduceC(clone_i, table);

    // 2 번 방법
    //J = ScanImageAndReduceIterator(clone_i, table);
     
    // 3 번 방법
    //J = ScanImageAndReduceRandomAccess(clone_i, table);
    
    // 4 번 방법
    /*
    //! [table-init]
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for (int i = 0; i < 256; ++i)
        p[i] = table[i];
    //! [table-init]]
    Mat J;
    //! [table-use]
    LUT(I, lookUpTable, J);
    //! [table-use]
    */
    

    imshow("Original Image ", I);
    imshow("after LookupTable(color reduced Image)", J);
    waitKey(0);

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

//! [scan-iterator]
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            MatIterator_<uchar> it, end;
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
    case 3:
        {
            MatIterator_<Vec3b> it, end;
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }

    return I;
}
//! [scan-iterator]

//! [scan-random]
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels)
    {
    case 1:
        {
            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
            break;
        }
    case 3:
        {
         Mat_<Vec3b> _I = I;

         for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j )
               {
                   _I(i,j)[0] = table[_I(i,j)[0]];
                   _I(i,j)[1] = table[_I(i,j)[1]];
                   _I(i,j)[2] = table[_I(i,j)[2]];
            }
         I = _I;
         break;
        }
    }

    return I;
}
//! [scan-random]