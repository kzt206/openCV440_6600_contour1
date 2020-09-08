#include <opencv2/opencv.hpp>

using namespace cv;

void axis(Point x0, Point x1, Point y0, Point y1, Mat& image);


void axis(Point x0, Point x1, Point y0, Point y1, Mat& image) {

	int linetype = LINE_8;
	int lineWidth = 1;

	// x axis
	line(image, x0, x1, Scalar(0, 0, 0), lineWidth, linetype);

	// y axis
	line(image, y0, y1, Scalar(0, 0, 0), lineWidth, linetype);

}