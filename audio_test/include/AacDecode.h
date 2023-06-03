#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fdk-aac/aacdecoder_lib.h"

int getADTSframe(unsigned char* buffer, int buf_size, unsigned char* data, unsigned int* data_size) {
    int size = 0;

    if (!buffer || !data || !data_size) {
        return -1;
    }

    while (1) {
        if (buf_size < 7) {
            return -1;
        }
        //Sync words
        if ((buffer[0] == 0xff) && ((buffer[1] & 0xf0) == 0xf0)) {
            size |= ((buffer[3] & 0x03) << 11);     //high 2 bit
            size |= buffer[4] << 3;                //middle 8 bit
            size |= ((buffer[5] & 0xe0) >> 5);        //low 3bit
            break;
        }
        --buf_size;
        ++buffer;
    }

    if (buf_size < size) {
        return 1;
    }

    memcpy(data, buffer, size);
    *data_size = size;

    return 0;
}

int runDecode() {
    const char* in_name = "output.aac";

    int data_size = 0;
    int cnt = 0;
    int offset = 0;

    //FILE *myout=fopen("output_log.txt","wb+");
    FILE* myout = stdout;

    unsigned char* aacframe = (unsigned char*)malloc(1024 * 5);
    unsigned char* aacbuffer = (unsigned char*)malloc(1024 * 1024);

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
    //    aacCoder = aacDecoder_Open(TT_MP4_RAW , 1);
    AAC_DECODER_ERROR aacError;
    /*
    int conceal_method=2;//0 muting 1 noise 2 interpolation
    UCHAR eld_conf[] = { 0xF8, 0xE8, 0x50, 0x00 };//ste eld 44.1k
//    UCHAR ld_conf[] = { 0xBA, 0x88, 0x00, 0x00 };//mono ld 32k

    UCHAR *conf[] = { eld_conf };
    static UINT conf_len = sizeof(eld_conf);
    AAC_DECODER_ERROR err = aacDecoder_ConfigRaw(aacCoder, conf, &conf_len);
    if(err>0){
        fprintf(myout,"conf err\n");
    }
    aacDecoder_SetParam(aacCoder, AAC_CONCEAL_METHOD,conceal_method);
    aacDecoder_SetParam(aacCoder,  AAC_PCM_MAX_OUTPUT_CHANNELS,1); //MONO:1
    */
    unsigned int valid = 0;
    unsigned int size = 0;
    unsigned int decsize = 8 * 1024 * sizeof(INT_PCM);
    unsigned char* decdata = (unsigned char*)malloc(decsize);


    while (!feof(infile)) {
        data_size = fread(aacbuffer + offset, 1, 1024 * 1024 - offset, infile);
        unsigned char* input_data = aacbuffer;

        while (true)
        {
            int ret = getADTSframe(input_data, data_size, aacframe, &size);
            if (ret == -1) {
                printf("adtsÖ¡½áÊø\n");
                break;
            }
            else if (ret == 1) {
                memcpy(aacbuffer, input_data, data_size);
                offset = data_size;
                printf("µ±Ç°adtsÖ¡Ëð»µ\n");
                break;
            }
            valid = size;
            aacError = aacDecoder_Fill(aacCoder, &aacframe, &size, &valid);
            if (aacError > 0) {
                fprintf(myout, "fill err\n");
            }
            aacError = aacDecoder_DecodeFrame(aacCoder, (INT_PCM*)decdata, decsize / sizeof(INT_PCM), 0);
            if (aacError > 0) {
                fprintf(myout, "decode err\n");
            }

            CStreamInfo* pcmFrame = aacDecoder_GetStreamInfo(aacCoder);

            fprintf(myout, "pcmFrame: channels=%d,simmpleRate=%d,frameSize=%d\n",
                pcmFrame->numChannels, pcmFrame->sampleRate, pcmFrame->frameSize);


            char profile_str[10] = { 0 };
            char frequence_str[10] = { 0 };

            unsigned char profile = aacframe[2] & 0xC0;
            profile = profile >> 6;
            switch (profile) {
            case 0: sprintf(profile_str, "Main"); break;
            case 1: sprintf(profile_str, "LC"); break;
            case 2: sprintf(profile_str, "SSR"); break;
            default:sprintf(profile_str, "unknown"); break;
            }

            unsigned char sampling_frequency_index = aacframe[2] & 0x3C;
            sampling_frequency_index = sampling_frequency_index >> 2;

            switch (sampling_frequency_index) {
            case 0: sprintf(frequence_str, "96000Hz"); break;
            case 1: sprintf(frequence_str, "88200Hz"); break;
            case 2: sprintf(frequence_str, "64000Hz"); break;
            case 3: sprintf(frequence_str, "48000Hz"); break;
            case 4: sprintf(frequence_str, "44100Hz"); break;
            case 5: sprintf(frequence_str, "32000Hz"); break;
            case 6: sprintf(frequence_str, "24000Hz"); break;
            case 7: sprintf(frequence_str, "22050Hz"); break;
            case 8: sprintf(frequence_str, "16000Hz"); break;
            case 9: sprintf(frequence_str, "12000Hz"); break;
            case 10: sprintf(frequence_str, "11025Hz"); break;
            case 11: sprintf(frequence_str, "8000Hz"); break;
            default:sprintf(frequence_str, "unknown"); break;
            }


            fprintf(myout, "%5d| %8s|  %8s| %5d| %5d |\n", cnt, profile_str, frequence_str, size, decsize);
            data_size -= size;
            input_data += size;
            cnt++;
        }
        printf("--------------------------\n");
    }
    free(decdata);
    free(aacbuffer);
    free(aacframe);
    fclose(infile);

    return 0;
}