#include <iostream>
#include<SDL.h>

#include "Test.h"
extern "C" {
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h" 
}

int Test::testRtsp()
{
	std::cout << "testRtsp..." << std::endl;
	//��ʼ����װ��
	av_register_all();
	//��ʼ������� �����Դ�rtsp rtmp http Э�����ý����Ƶ��
	avformat_network_init();

	const char* url = "rtsp://admin:zz369369@10.52.8.106:554/stream1";
	//const char* url = "https://inner-5wge0usz.yangkg.xyz:8000/1E1DD851F4SSXKLS2/stream262.live.flv?st=fYqbrHIOyvVlH3FlGhFNXQ&e=1684834954&t=3&s=2&r=262&uuid=1554d287-79ea-4a5b-bf8e-bc89d84fcdf8";
	//const char* url = "rtsp://172.26.144.239";

	AVFormatContext* pFormatCtx = avformat_alloc_context();
	//��������
	AVDictionary* dictionaryOpts = NULL;
	//����rtsp����tcpЭ���
	av_dict_set(&dictionaryOpts, "rtsp_transport", "tcp", 0);
	//������ʱʱ��
	av_dict_set(&dictionaryOpts, "max_delay", "500", 0);

	int ret = -1;
	ret = avformat_open_input(&pFormatCtx, url, 0, &dictionaryOpts);
	if (ret != 0) {
		fprintf(stderr, "fail to open url: %s, return value: %d\n", url, ret);
		return -1;
	}

	// Read packets of a media file to get stream information
	ret = avformat_find_stream_info(pFormatCtx, nullptr);
	if (ret < 0) {
		fprintf(stderr, "fail to get stream information: %d\n", ret);
		return -1;
	}

	// audio/video stream index
	int video_stream_index = -1;
	int audio_stream_index = -1;
	fprintf(stdout, "Number of elements in AVFormatContext.streams: %d\n", pFormatCtx->nb_streams);
	for (int i = 0; i < pFormatCtx->nb_streams; ++i) {
		const AVStream* stream = pFormatCtx->streams[i];
		fprintf(stdout, "type of the encoded data: %d\n", stream->codecpar->codec_id);
		if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			video_stream_index = i;
			fprintf(stdout, "dimensions of the video frame in pixels: width: %d, height: %d, pixel format: %d\n",
				stream->codecpar->width, stream->codecpar->height, stream->codecpar->format);
		}
		else if (stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
			audio_stream_index = i;
			fprintf(stdout, "audio sample format: %d\n", stream->codecpar->format);
		}
	}
	//��ȡ��Ƶ���еı����������
	//AVCodecContext* pCodecCtx = pFormatCtx->streams[video_stream_index]->codec;��ʱ
	AVCodecContext* pCodecCtx = avcodec_alloc_context3(NULL);
	if (pCodecCtx == NULL)
	{
		printf("Could not allocate AVCodecContext\n");
		return -1;
	}
	avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[video_stream_index]->codecpar);
	//���ݱ�����������еı���id���Ҷ�Ӧ�Ľ���
	AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		printf("%s", "�Ҳ���������\n");
		return -1;
	}
	//�򿪽�����
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		printf("%s", "�������޷���\n");
		return -1;
	}
	//�����Ƶ��Ϣ
	printf("��Ƶ��pix_fmt��%d\n", pCodecCtx->pix_fmt);//AV_PIX_FMT_YUV420P
	printf("��Ƶ�Ŀ��ߣ�%d,%d\n", pCodecCtx->width, pCodecCtx->height);
	printf("��Ƶ�����������ƣ�%s\n", pCodec->name);


	AVPacket* packet = av_packet_alloc();// (AVPacket*)av_malloc(sizeof(AVPacket));
	AVFrame* pFrame = av_frame_alloc();

	AVFrame* pFrameRGB = av_frame_alloc();
	//������Ƶ֡��Ҫ�ڴ� (���ԭʼ������)
	int numBytes;		//��Ҫ���ڴ��С
	uint8_t* buffer = NULL;
	//��ȡ��Ҫ���ڴ��С
	/*
	1. av_image_fill_arrays ���������� frame �����Ǹղŷ�����ڴ�
	2. av_malloc ��һ�� FFmpeg �� malloc��
	��Ҫ�Ƕ� malloc ����һЩ��װ����֤��ַ����֮������飬
	���ᱣ֤��Ĵ��벻�����ڴ�й©������ͷŻ����� malloc ����
	*/
	numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);//��ȡ��Ҫ���ڴ��С
	buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
	//����frame�͸ղŷ��������
	av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);

	SwsContext* sws_ctx = NULL;
	sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);

	//sdl
	SwsContext* pSwsCtx = nullptr;
	pSwsCtx = sws_alloc_context();
	ret = sws_init_context(pSwsCtx, nullptr, nullptr);
	if (ret < 0) {
		printf("init sws_context failed\n");
		return -1;
	}
	pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, this->w, this->h, AV_PIX_FMT_YUV420P, SWS_BICUBIC, nullptr, nullptr, nullptr);
	if (nullptr == pSwsCtx) {
		printf("get sws context failed\n");
		return -1;
	}

	AVFrame* pFrameYuv = nullptr;
	pFrameYuv = av_frame_alloc();
	av_image_alloc(pFrameYuv->data,
		pFrameYuv->linesize,
		this->w,
		this->h,
		AV_PIX_FMT_YUV420P,
		1);

	SDL_Texture* texture = nullptr;
	texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_TARGET, this->w, this->h);

	while (1) {
		ret = av_read_frame(pFormatCtx, packet);
		if (ret < 0) {
			fprintf(stderr, "error or end of file: %d\n", ret);
			continue;
		}
		if (packet->stream_index == audio_stream_index) {
			//fprintf(stdout, "audio stream, packet size: %d\n", packet->size);
			continue;
		}
		if (packet->stream_index == video_stream_index) {
			fprintf(stdout, "video stream, packet size: %d\n", packet->size);

			//ret = avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, packet);
			ret = avcodec_send_packet(pCodecCtx, packet);
			av_packet_unref(packet);
			if (ret < 0) {
				printf("%s", "�������");
			}
			//if (frameFinished) {
				//����Ƶ֡ԭ���ĸ�ʽpCodecCtx->pix_fmtת����RGB
				//saveFrame2JPEG(pFrame, pCodecCtx->width, pCodecCtx->height, cnt);
				//break;
			//}
			ret = avcodec_receive_frame(pCodecCtx, pFrame);
			if (ret != 0) {
				fprintf(stderr, "avcodec_receive_frame failed !\n");
				char errbuf[128];
				const char* errbuf_ptr = errbuf;
				av_strerror(ret, errbuf, sizeof(errbuf));
				fprintf(stderr, "avcodec_receive_frame failed %s\n", errbuf);
			}
			ret = sws_scale(pSwsCtx, pFrame->data, pFrame->linesize, 0, pFrame->height, pFrameYuv->data, pFrameYuv->linesize);
			if (ret < 0) {
				printf("sws_scale implement failed\n");
				break;
			}

			SDL_RenderClear(render);
			SDL_UpdateYUVTexture(texture, nullptr,
				pFrameYuv->data[0], pFrameYuv->linesize[0],
				pFrameYuv->data[1], pFrameYuv->linesize[1],
				pFrameYuv->data[2], pFrameYuv->linesize[2]);
			SDL_RenderCopy(render, texture, nullptr, nullptr);
			SDL_RenderPresent(render);

			//else {
			//	saveFrame2JPEG(pFrame, pCodecCtx->width, pCodecCtx->height, 0);

			//	sws_scale(sws_ctx, (uint8_t const* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
			//	saveFrame2Ppm(pFrameRGB, pCodecCtx->width, pCodecCtx->height, 0);

			//	break;
			//}
			//break;
		}


	}

	avformat_free_context(pFormatCtx);
	return 0;
}
