#include <opencv2/opencv.hpp>
#include <iostream>

#include <chrono>
#include <thread>


int testVideoCapture2() {
	//https://code-database.com/knowledges/96
	// 動画ファイルのパスの文字列を格納するオブジェクトを宣言する
//	std::string filepath = "D:\\OneDrive\\Programing\\openCV\\P1020792.MP4";
//	std::string filepath = "D:\\OneDrive\\Programing\\openCV\\P1020792.MP4";
	// 動画ファイルを取り込むためのオブジェクトを宣言する
	cv::VideoCapture video;
	// 動画ファイルを開く
	//video.open(filepath);
	video.open(0);
	if (video.isOpened() == false) {
		// 動画ファイルが開けなかったときは終了する
		return 0;
	}
	cv::VideoWriter writer; // 動画ファイルを書き出すためのオブジェクトを宣言する
	int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); // ビデオフォーマットの指定( ISO MPEG-4 / .mp4)
	int    width, height; // , fourcc; // 作成する動画ファイルの設定
	double fps;
	width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);	// フレーム横幅を取得
	height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);	// フレーム縦幅を取得
	fps = video.get(cv::CAP_PROP_FPS);				// フレームレートを取得

	std::cout << "width:" << width << " , height:" << height << " , fps:" << fps << std::endl;

	//fps /= 6;

	writer.open("CloneVideo2b.mp4", fourcc, fps, cv::Size(width, height));
	cv::Mat image;// 画像を格納するオブジェクトを宣言する


	// display string
	//cv::Mat dst;
	//dst = image.clone();

	int numFrame = 0;

	while (1) {
		numFrame++;

		video >> image; // videoからimageへ1フレームを取り込む

		//if (numFrame % 10 != 0)continue;
		//std::cout << numFrame << "\n";

		if (image.empty() == true) break; // 画像が読み込めなかったとき、無限ループを抜ける

		// display rectagnles
		cv::Rect rect(numFrame, numFrame, 50, 50);  // (x, y, width, height)
		rectangle(image, rect, cv::Scalar(255, 0, 0), -1, cv::LINE_4); // (Blue,Green,Red)

		// display string
		cv::putText(
			image,
			std::to_string(numFrame),
			//	std::to_string((int)video.get(cv::CAP_PROP_FRAME_COUNT)),
			cv::Point(100, 100),
			cv::FONT_HERSHEY_SIMPLEX,
			2., //font size
			cv::Scalar(0, 0, 255),//color(Blue,Green,Red)
			2  // font thickness
		);


		cv::imshow("showing", image); // ウィンドウに動画を表示する
		writer << image;  // 画像 image を動画ファイルへ書き出す
		if (cv::waitKey(1) == 'q') break; //qを押すと終了

		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}


	return 0;
}