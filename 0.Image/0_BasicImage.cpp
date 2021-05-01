#include <opencv2/core.hpp> // basic building blocks of the library
#include <opencv2/imgcodecs.hpp> // provides function for reading and writing
#include <opencv2/highgui.hpp> // this contains the functions to show an image in a window

#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	string image_path = "starry_night.jpg";

	Mat img = imread(image_path, IMREAD_COLOR);

	if (img.empty())
	{
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}
	imshow("asd window", img);
	int k = waitKey(5000); // wait for 키보드 입력

	if (k == 's')
		imwrite("starry_night.png", img);

	return 0;
}
