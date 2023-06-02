#include "Common.h"
#include "DXGICapture.h"

#include <opencv2/opencv.hpp>

using namespace BXC;

int main(){
	int64_t t1, t2;
	DXGICapture dxgiCapture;
	int width = 1920;
	int height = 1080;
	int duplWidth = -1;
	int duplHeight = -1;

	if (!dxgiCapture.InitDevice()){
		LOGE("Failed to initialize DXGIScreen device");
		return -1;
	}

	if (!dxgiCapture.InitDupl(0, duplWidth, duplHeight)){
		LOGE("Failed to InitDupl");
		return -1;
	}
	LOGI("InitDupl success,width=%d,height=%d,duplWidth=%d,duplHeight=%d", width, height, duplWidth, duplHeight);

	long mBufferSize = duplWidth * duplHeight * 4;
	uint8_t* mBuffer = new UCHAR[mBufferSize];

	int i = 0;
	while (true) {
		t1 = getCurTimestamp();
		GETFRAMERESULT getFrameResult = dxgiCapture.getFrame();
		if (GETFRAME_SUCCESS == getFrameResult){
			if (dxgiCapture.copyFrameToBuffer(&mBuffer, mBufferSize)){
				t2 = getCurTimestamp();
				LOGI("i=%d getFrame success spend %lld ms", i, (t2 - t1));
				std::string fname = "screenshot_dxgi-" + std::to_string(i) + ".jpg";

				cv::Mat bgra_image(duplHeight, duplWidth, CV_8UC4, mBuffer);
				cv::imwrite(fname, bgra_image);//LNK2019 无法解析的外部符号 d是debug版本，如果是release版本，就不需要加d
			}
			dxgiCapture.doneWithFrame();
		}else {
			if (GETFRAME_DUPLICATION_ERROR == getFrameResult) {
				int w = -1;
				int h = -1;
				if (dxgiCapture.ReInitDupl(0, w, h)) {
					LOGI("ReInitDupl success ,duplWidth=%d,duplHeight=%d", duplWidth, duplHeight);
					if (w != duplWidth || h != duplHeight) {
						duplWidth = w;
						duplHeight = h;

						if (mBuffer) {
							delete mBuffer;
							mBuffer = nullptr;
						}
						mBufferSize = duplWidth * duplHeight * 4;
						mBuffer = new UCHAR[mBufferSize];
					}
				}else {
					LOGI("ReInitDupl error");
				}
			}
		}
		Sleep(2000);
		++i;
	}

	system("pause");
	return 0;
}