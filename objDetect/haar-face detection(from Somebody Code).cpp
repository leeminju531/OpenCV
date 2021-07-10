#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace std;
using namespace cv;


/** Global variables */
CascadeClassifier face_cascade;

Mat detection(Mat img);

/** @function main */
int main(int argc, const char** argv)
{

    String face_cascade_name = "haarcascade_frontalface_alt.xml";

    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };


    VideoCapture capture;
    //-- 2. Read the video stream
    capture.open(0);
    if (!capture.isOpened())
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }

    Mat frame;
    while (capture.read(frame))
    {
        if (frame.empty())
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        frame = detection(frame);
        imshow("frame", frame);

        if (waitKey(10) == 27)
        {
            break; // escape
        }
    }
    return 0;
}

Mat preprocessImage(Mat input)
{
    //cout<<"-->>function preprocessImage"<<endl;
    Mat result;

    resize(input, input, Size(), 0.5, 0.5, INTER_AREA);

    cvtColor(input, result, COLOR_BGR2GRAY);
    // Equalize the histogram
    equalizeHist(result, result);

    return result;
}
Mat extractFace(Mat input, vector<Rect>* faces)
{
    Mat result;


    result = preprocessImage(input);

    Mat zero = Mat::zeros(result.rows, result.cols, CV_8UC1);

    face_cascade.detectMultiScale(result, *faces, \
        1.1, 2, 0 | CV_HAL_CMP_GE, Size(100, 100), Size(200, 200));

   if ((*faces).size() == 0)
        return zero;

    Mat grayc = result.clone();
    grayc = grayc((*faces)[0]);//

    return grayc; 
}

Mat detection(Mat img)
{
    vector<Rect> faces;

    Mat grayt = extractFace(img, &faces);
    
    Scalar he = sum(grayt);
    if (he[0] == 0)
    {
        resize(img, img, Size(), 0.5, 0.5, INTER_AREA);
        return img;
    }

    resize(img, img, Size(), 0.5, 0.5, INTER_AREA);
    rectangle(img, faces[0], Scalar(255, 255, 255), 2);
    
    
    return img;
} 

