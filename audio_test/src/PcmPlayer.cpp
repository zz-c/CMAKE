#include <stdio.h>
#include <SDL.h>
#include "PcmPlayer.h"

int PcmPlayer::play()
{
    const char* filename = "output.pcm";

    //Init
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf("Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }
    //SDL_AudioSpec
    SDL_AudioSpec wanted_spec;
    wanted_spec.freq = 44100;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = 2;
    wanted_spec.silence = 0;
    wanted_spec.samples = 1024;
    wanted_spec.callback = PcmPlayer::fill_audio;

    if (SDL_OpenAudio(&wanted_spec, NULL) < 0) {
        printf("SDL_OpenAudio err: %s \n", SDL_GetError());
        return -1;
    }

    FILE* fp = fopen(filename, "rb+");
    if (fp == NULL) {
        printf("cannot open this file\n");
        return -1;
    }
    int pcm_buffer_size = 409600;// 一次性从pcm文件中读取的数据大小
    char* pcm_buffer = (char*)malloc(pcm_buffer_size);
    int data_count = 0;

    //Play 参数是非0值就暂停，如果是0值就播放
    SDL_PauseAudio(0);
    size_t nr;
    while (true) {
        nr = fread(pcm_buffer, 1, pcm_buffer_size, fp);
        if (nr != pcm_buffer_size) {
            printf("读取pcm结束 nr=%zu \n", nr);
            // Loop
            fseek(fp, 0, SEEK_SET);
            fread(pcm_buffer, 1, pcm_buffer_size, fp);
            data_count = 0;
            break;
        }
        printf("Now Playing %10d Bytes data.\n", data_count);
        data_count += pcm_buffer_size;

        //audio_chunk2 = (Uint8*)pcm_buffer;
        audio_pos2 = (Uint8*)pcm_buffer;
        audio_len2 = pcm_buffer_size;
        
        while (audio_len2 > 0)//Wait until finish
        {
            SDL_Delay(23);
        }

    }
    free(pcm_buffer);
    SDL_Quit();
    return 0;
}
void PcmPlayer::fill_audio(void* udata, Uint8* stream, int len) {

    SDL_memset(stream, 0, len);
    if (audio_len2 == 0){
        return;
    }
    len = (len > audio_len2 ? audio_len2 : len);
    SDL_MixAudio(stream, audio_pos2, len, SDL_MIX_MAXVOLUME);
    audio_pos2 += len;
    audio_len2 -= len;
}
void PcmPlayer::test() {
    printf("PcmPlayer test\n");
}