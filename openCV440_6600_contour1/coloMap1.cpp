#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;

void axis(Point x0, Point x1, Point y0, Point y1, Mat& image);
void ColorScaleBCGYR(int& r, int& g, int& b, int z);

void colorMap1(int numData, double dataX[], double dataY[], double dataZ[]) {
	// image object
		// full color
	const int xShift = 20;
	const int yShift = 20;
	const int xLength = 500;
	const int yLength = 500;
	const int xMaxShift = 20;
	const int yMaxShift = 20;
	const int xMax = xShift + xLength + yMaxShift;
	const int yMax = yShift + yLength + yMaxShift;

	// point size
	const int dx = 25;
	const int dy = 25;


	Mat image(yMax, xMax, CV_8UC3);

	// fill with white
	image = Scalar(255, 255, 255);  // Blue,Green,Red


	// input data
	const int numberData = 1000;
	int x[numberData], y[numberData], z[numberData];
	double zd[numberData];
	//int wave[numberData][numberData];
	//int n = 0;
	double minZ = 10000;
	double maxZ = -10000;
	for (int i = 0; i < numData; i++) {
		x[i] = int(dataX[i]);
		y[i] = int(dataY[i]);
		double tmpz = dataZ[i];
		if (maxZ < tmpz) maxZ = tmpz;
		if (minZ > tmpz) minZ = tmpz;
		zd[i] = tmpz;
	}
	std::cout << sizeof(x) / sizeof(*x);

	//normarize
	for (int i = 0; i < numberData; i++) {
		z[i] = int((zd[i] - minZ) / (maxZ - minZ) * 255);
	}

	int halfZ = 256 / 2;
	// draw rectangles 4
	for (int i = 0; i < sizeof(x) / sizeof(*x); i++) {
		Rect rect(0 + x[i] + xShift, yMax - dy - y[i] - yShift, dx, dy);  // (x, y, width, height)
		int r, g, b;

		ColorScaleBCGYR(r, g, b, z[i]);

		Scalar color(b, g, r);
		rectangle(image, rect, color, -1, LINE_4); // Scalar(Blue,Green,Red)  -1:fill
	}

	//GaussianBlur(image, image, Size(7, 7), 1.5, 1.5);

	//axis
	Point x0(xShift, yMax - yShift);
	Point x1(xMax - xMaxShift, yMax - yShift);
	Point y0(xShift, yMax - yShift);
	Point y1(xShift, yMaxShift);
	axis(x0, x1, y0, y1, image);

	//Show image
	imshow("Map", image);
	imwrite("colorMap1-3.jpg", image);
	waitKey();



}