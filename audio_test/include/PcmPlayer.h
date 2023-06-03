#pragma once

//static Uint8* audio_chunk2;
static Uint32  audio_len2;
static Uint8* audio_pos2;


class PcmPlayer {

public:
	PcmPlayer() {}
	int play();

	static void fill_audio(void* udata, Uint8* stream, int len);
    static void test();
};
