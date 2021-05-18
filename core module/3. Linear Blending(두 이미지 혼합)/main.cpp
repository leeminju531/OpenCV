#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;

int main()
{
	Mat src1, src2, dst;
	src1 = imread("LinuxLogo.jpg");
	src2 = imread("WindowsLogo.jpg");
	if (src1.empty()) { cout << "Error loading src1" << endl; return EXIT_FAILURE; }
	if (src2.empty()) { cout << "Error loading src2" << endl; return EXIT_FAILURE; }

	double alpha = 0.5;
	double beta = 1 - alpha;

	addWeighted(src1, alpha, src2, beta, 0, dst);
	imshow("Linear Blending",dst);
	waitKey();

	return 0;
}
