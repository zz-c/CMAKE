#include <opencv2/opencv.hpp>

int main(){
	int duplWidth = 1920;
	int duplHeight = 1080;
	long mBufferSize = duplWidth * duplHeight * 4;
	uint8_t* mBuffer = new uint8_t[mBufferSize];
	for (int i = 0; i < mBufferSize;i++) {
		mBuffer[i] = i%255;
	}

	std::string fname = "opencv.jpg";

	cv::Mat bgra_image(duplHeight, duplWidth, CV_8UC4, mBuffer);
	cv::imwrite(fname, bgra_image);//LNK2019 无法解析的外部符号 d是debug版本，如果是release版本，就不需要加d

	system("pause");
	return 0;
}