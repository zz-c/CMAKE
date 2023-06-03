//
// Created by sun on 2022/12/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "Adts.h"
#include "fdk-aac/aacdecoder_lib.h"
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
void fill_audio(void* data, Uint8* stream, int len) {
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

int runAac() {
    const char* in_name = "output.aac";

    //SDL2 start
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf("Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }
    SDL_AudioSpec wanted_spec;
    wanted_spec.freq = 44100;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = 2;
    wanted_spec.silence = 0;
    wanted_spec.samples = 1024;
    wanted_spec.callback = fill_audio;

    if (SDL_OpenAudio(&wanted_spec, NULL) < 0) {
        printf("SDL_OpenAudio err \n");
        return -1;
    }
    SDL_PauseAudio(0);
    //SDL2 end
    FILE* infile = fopen(in_name, "rb");
    if (!infile) {
        printf("failed to open %s\n", in_name);
        return -1;
    }
    printf("-----+- ADTS Frame Table -+------+\n");
    printf(" NUM | Profile | Frequency| Size | Decode Size |\n");
    printf("-----+---------+----------+------+\n");
    HANDLE_AACDECODER aacCoder;
    aacCoder = aacDecoder_Open(TT_MP4_ADTS, 1);
    AAC_DECODER_ERROR aacError;

    int cnt = 0;


    struct AdtsHeader adtsHeader;
    int adtsHeaderLen;
    int adtsContentLen;

    unsigned int valid = 0;

    uint8_t* frame = (uint8_t*)malloc(2000);

    unsigned int decFrameSize = 2 * 1024 * sizeof(INT_PCM);
    unsigned char* decFrame = (unsigned char*)malloc(decFrameSize);


    while (true) {
        adtsHeaderLen = fread(frame, 1, 7, infile);
        //        printf("adtsHeaderLen = %d \n",adtsHeaderLen);
        if (adtsHeaderLen <= 0) {
            printf("read adtsHeaderLen err\n");
            break;
        }
        if (parseAdtsHeader(frame, &adtsHeader) < 0) {
            printf("parseAdtsHeader err\n");
            break;
        }
        adtsContentLen = fread(frame + 7, 1, adtsHeader.aacFrameLength - 7, infile);
        //        printf("adtsContentLen = %d \n",adtsContentLen);
        if (adtsContentLen < 0) {
            printf("read adtsContentLen err\n");
            break;
        }

        valid = adtsHeader.aacFrameLength;
        aacError = aacDecoder_Fill(aacCoder, &frame, &adtsHeader.aacFrameLength, &valid);
        if (aacError > 0) {
            printf("aacDecoder_Fill err\n");
            break;
        }
        aacError = aacDecoder_DecodeFrame(aacCoder, (INT_PCM*)decFrame, decFrameSize / sizeof(INT_PCM), 0);
        if (aacError > 0) {
            printf("aacDecoder_DecodeFrame err\n");
            break;
        }

        //Set audio buffer (PCM data)
        audio_chunk = (Uint8*)decFrame;
        //Audio buffer length
        audio_len = decFrameSize;
        audio_pos = audio_chunk;

        while (audio_len > 0) {
            //            SDL_Delay(23);
            SDL_Delay(1);
        }

        printf("cnt=%d,aacFrameLength=%d,decFrameSize=%d \n", cnt, adtsHeader.aacFrameLength, decFrameSize);

        cnt++;
    }

    free(frame);
    free(decFrame);
    fclose(infile);

    SDL_Quit();

    printf("end\n");
    return 0;
}