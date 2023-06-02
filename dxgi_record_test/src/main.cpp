#include <ctime>
#include <iostream>
#include "Duplication.h"
#include "FFmpegEncoder.h"
#include "Log.h"

#define FFMPEG_ENC_264_QSV "h264_qsv"
#define FFMPEG_ENC_264_CPU "libx264"
#define FFMPEG_ENC_264_NVIDIA "h264_nvenc"
#define FFMPEG_ENC_264_AMD "h264_amf"


int main() 
{
	Duplication dup;
	if (!dup.InitDevice())
	{
		std::cout << "init device failed" << std::endl;
		return 0;
	}
	if (!dup.InitDupl(0))
	{
		std::cout << "init duplication failed" << std::endl;
		return 0;
	}
	av_register_all();

	int fps = 25;
	int bitrate = 2000000;
	int width = 1920;
	int height = 1080;
	const char* outputFileName = "out.h264";


	BYTE* buffer = nullptr;
	BYTE* backupBuffer = nullptr;

	clock_t start, end;
	float duration;
	start = clock();
	int counter = 0;
	int time = 60;

	FFmpegEncoder encoder;
	encoder.ffmpeg_encoder_start(outputFileName, FFMPEG_ENC_264_CPU, width, height, fps, bitrate);

	while (true)
	{
		end = clock();
		duration = (float)(end - start) / (float)CLOCKS_PER_SEC;
		if (duration > time){
			break;
		}
		if (dup.GetFrame()){
			if (dup.copyFrameDataToBuffer(&buffer, width, height)){
				
				dup.DoneWithFrame();
				encoder.frame->pts = counter;
				encoder.ffmpeg_encoder_encode_frame_bgra(buffer);

				delete backupBuffer;
				backupBuffer = buffer;
				buffer = nullptr;
				counter++;
			}else{
				fprintf(stderr, "Get frame failed!\n");
				getchar();
				return 0;
			}
		}else{
			encoder.frame->pts = counter;
			encoder.ffmpeg_encoder_encode_frame_bgra(backupBuffer);
			counter++;
		}
	}
	if (buffer)
		delete buffer;
	if (backupBuffer)
		delete buffer;
	encoder.ffmpeg_encoder_finish();

	LOGI("fps=%f", (float)counter / (float)time);

	//getchar();
	return 0;
}