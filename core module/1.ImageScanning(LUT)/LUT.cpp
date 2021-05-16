#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace std;
using namespace cv;


int main()
{

    string img_path = "starry_night.jpg";
    Mat I = imread(img_path, IMREAD_GRAYSCALE);
    if (I.empty())
    {
        cout << "The image" << img_path << " could not be loaded." << endl;
        return -1;
    }


    //! [dividewith]
    int divideWith = 150; // convert our input string to number - C++ style

    uchar table[256];
    for (int i = 0; i < 256; ++i)
        table[i] = (uchar)(divideWith * (i / divideWith));
    //! [dividewith]

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

    imshow("Original Image", I);
    imshow("Color Reducted Image ", J);
    waitKey(0);

    return 0;
}

