#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat drawContourLine(Mat src, int contourNum, Scalar contourColor);

int main()
{
	//https://qrunch.net/@Negizoku/entries/UN1PYUAcnomTq9uW?ref=qrunch
    //ƒKƒEƒXŠÖ”‚ğì¬  
    float wave[500][500];
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            double r = sqrt(i * i + 2 * j * j);
            wave[i][j] = (float) exp( -r * r / 150000);
        }
    }
    Mat src (500, 500, CV_32FC1, wave);

    imshow("src", src);
    waitKey(0);

    //‡@0`255‚É³‹K‰»‚µ‚ÄAMatType‚ğCV_8UC1‚É•ÏX  
    normalize(src, src, 0, 255, NORM_MINMAX);
    src.convertTo(src,CV_8UC1);
    imshow("src2", src);
    //src.ImWrite(@"D:\src1.png");
    waitKey(0);


    Mat dst = drawContourLine(src, 10,Scalar(255,0,0));

    imshow("dst", dst);
    waitKey(0);

	return 0;

}

Mat drawContourLine(Mat src, int contourNum, Scalar contourColor) {
    //‡A“™‚ü‚Ì”‚©‚çA“™‚ü‚Ì‚‚³‚ğŒvZ  
    int step = 256 / contourNum;

    //‡AŠK’²•ÏŠ·—p‚ÌƒqƒXƒgƒOƒ‰ƒ€‚ğì¬  
    //unsigned char lut[256] ;
    //for (int i = 0; i < sizeof(lut)/sizeof(lut[0]); i++) {
    //    lut[i] = (unsigned char)(floor((double)i / step) * step);
    //}
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for (int i = 0; i < 256; ++i) {
        p[i] = floor(double(i) /step) * step;
    }

    //Console.WriteLine(Scalar.White);

    //‡AŠK’²‚ğ‘e‚­‚·‚é  
    Mat roughGrad;
    LUT(src, lookUpTable, roughGrad);
    //cout << roughGrad;
    //return roughGrad;
    imshow("roughGrad", roughGrad);
    waitKey(0);



    //‡BŠK’²‚ğr‚­‚µ‚½‰æ‘œ‚ÌƒGƒbƒWŒŸo  
    Mat contour = src.clone();
    //cv::Canny(roughGrad, contour, 1., 2.);
    imshow("contour", contour);
    waitKey(0);


    return contour;

    ////‡CƒJƒ‰[ƒ}ƒbƒv‚É•ÏX  
    //if (colormapTypes == null) {
    //    return contour;
    //}
    //else {
    //    ApplyColorMap(roughGrad, roughGrad, (ColormapTypes)colormapTypes);
    //    for (int j = 0; j < contour.rows; j++) {
    //        for (int i = 0; i < contour.cols; i++) {

    //            if (contour.At<char>(j, i) > 0) roughGrad.Set<Vec3b>(j, i, new Vec3b((byte)contourColor[0], (byte)contourColor[1], (byte)contourColor[2]));
    //        }
    //    }
    //}
    //return contour;
}