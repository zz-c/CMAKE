#pragma once

static Uint8* audio_chunk2;
static Uint32  audio_len2;
static Uint8* audio_pos2;


class PcmPlayer {

public:
	PcmPlayer() {}
	int play();

    static void fill_audio(void* udata, Uint8* stream, int len) {

        SDL_memset(stream, 0, len);
        if (audio_len2 == 0)
            return;
        len = (len > audio_len2 ? audio_len2 : len);

        SDL_MixAudio(stream, audio_pos2, len, SDL_MIX_MAXVOLUME);
        audio_pos2 += len;
        audio_len2 -= len;
    }

};
