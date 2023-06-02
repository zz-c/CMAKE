#pragma once
#include"CommonTypes.h"

class FFmpegEncoder
{
public:
	AVCodecContext *c = NULL;
	AVFrame *frame;
	AVPacket pkt;
	FILE *file;
	SwsContext *sws_context = NULL;
public:
	FFmpegEncoder() {}
	void ffmpeg_encoder_set_frame_yuv_from_rgb(uint8_t *rgb);
	void ffmpeg_encoder_set_frame_yuv_from_bgra(uint8_t *bgra);
	void ffmpeg_encoder_start(const char *filename, int codec_id, int width, int height, int fps, int bitrate);
	void ffmpeg_encoder_start(const char *filename, const char *codec_name, int width, int height, int fps, int bitrate);
	void ffmpeg_encoder_finish(void);
	void ffmpeg_encoder_encode_frame_rgb(uint8_t *rgb);
	void ffmpeg_encoder_encode_frame_bgra(uint8_t *bgra);
};