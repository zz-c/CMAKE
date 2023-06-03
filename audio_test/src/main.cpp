﻿#include <stdio.h>
#include <SDL.h>


//Buffer:
//|-----------|-------------|
//chunk-------pos---len-----|
static  Uint8* audio_chunk;
static  Uint32  audio_len;
static  Uint8* audio_pos;

/* Audio Callback
 * The audio function callback takes the following parameters:
 * stream: A pointer to the audio buffer to be filled
 * len: The length (in bytes) of the audio buffer
 *
*/
void fill_audio(void* udata, Uint8* stream, int len) {
    //SDL 2.0
    //printf("fill_audio\n");
    SDL_memset(stream, 0, len);
    if (audio_len == 0)
        return;
    len = (len > audio_len ? audio_len : len);

    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    audio_len -= len;
}

int main(int argc, char* argv[]){
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
    wanted_spec.callback = fill_audio;

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
        //Set audio buffer (PCM data)
        audio_chunk = (Uint8*)pcm_buffer;
        //Audio buffer length
        audio_len = pcm_buffer_size;
        audio_pos = audio_chunk;

        while (audio_len > 0)//Wait until finish
        {
            SDL_Delay(23);
        }

    }
    free(pcm_buffer);
    SDL_Quit();
    return 0;
}