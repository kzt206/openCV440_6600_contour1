#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat drawContourLine(Mat src, int contourNum, Scalar contourColor);

int main()
{
	//https://qrunch.net/@Negizoku/entries/UN1PYUAcnomTq9uW?ref=qrunch
    //ガウス関数を作成  
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

    //�@0〜255に正規化して、MatTypeをCV_8UC1に変更  
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
    //�A等高線の数から、等高線の高さを計算  
    int step = 256 / contourNum;

    //�A階調変換用のヒストグラムを作成  
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

    //�A階調を粗くする  
    Mat roughGrad;
    LUT(src, lookUpTable, roughGrad);
    //cout << roughGrad;
    //return roughGrad;
    imshow("roughGrad", roughGrad);
    waitKey(0);



    //�B階調を荒くした画像のエッジ検出  
    Mat contour = src.clone();
    //cv::Canny(roughGrad, contour, 1., 2.);
    imshow("contour", contour);
    waitKey(0);


    return contour;

    ////�Cカラーマップに変更  
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