#include "Adts.h"
#include <cstring>
#include <stdio.h>

int parseAdtsHeader(uint8_t* headerBuf, struct AdtsHeader* adtsHeader) {
    //    static int frame_number = 0;
    memset(adtsHeader, 0, sizeof(*adtsHeader));

    if ((headerBuf[0] == 0xFF) && ((headerBuf[1] & 0xF0) == 0xF0)) {

        adtsHeader->id = ((unsigned int)headerBuf[1] & 0x08) >> 3;
        adtsHeader->layer = ((unsigned int)headerBuf[1] & 0x06) >> 1;
        adtsHeader->protectionAbsent = (unsigned int)headerBuf[1] & 0x01;
        adtsHeader->profile = ((unsigned int)headerBuf[2] & 0xc0) >> 6;
        adtsHeader->samplingFreqIndex = ((unsigned int)headerBuf[2] & 0x3c) >> 2;
        adtsHeader->privateBit = ((unsigned int)headerBuf[2] & 0x02) >> 1;
        adtsHeader->channelCfg = ((((unsigned int)headerBuf[2] & 0x01) << 2) | (((unsigned int)headerBuf[3] & 0xc0) >> 6));
        adtsHeader->originalCopy = ((unsigned int)headerBuf[3] & 0x20) >> 5;
        adtsHeader->home = ((unsigned int)headerBuf[3] & 0x10) >> 4;
        adtsHeader->copyrightIdentificationBit = ((unsigned int)headerBuf[3] & 0x08) >> 3;
        adtsHeader->copyrightIdentificationStart = (unsigned int)headerBuf[3] & 0x04 >> 2;
        adtsHeader->aacFrameLength = (((((unsigned int)headerBuf[3]) & 0x03) << 11) |
            (((unsigned int)headerBuf[4] & 0xFF) << 3) |
            ((unsigned int)headerBuf[5] & 0xE0) >> 5);
        adtsHeader->adtsBufferFullness = (((unsigned int)headerBuf[5] & 0x1f) << 6 |
            ((unsigned int)headerBuf[6] & 0xfc) >> 2);
        adtsHeader->numberOfRawDataBlockInFrame = ((unsigned int)headerBuf[6] & 0x03);

        return 0;
    }
    else {
        printf("failed to parse adts header\n");
        return -1;
    }
}
int convertAdtsHeaderToBuf(struct AdtsHeader* adtsHeader, uint8_t* adtsHeaderBuf) {

    adtsHeaderBuf[0] = 0xFF;
    adtsHeaderBuf[1] = 0xF1;
    adtsHeaderBuf[2] = ((adtsHeader->profile) << 6) + (adtsHeader->samplingFreqIndex << 2) + (adtsHeader->channelCfg >> 2);
    adtsHeaderBuf[3] = (((adtsHeader->channelCfg & 3) << 6) + (adtsHeader->aacFrameLength >> 11));
    adtsHeaderBuf[4] = ((adtsHeader->aacFrameLength & 0x7FF) >> 3);
    adtsHeaderBuf[5] = (((adtsHeader->aacFrameLength & 7) << 5) + 0x1F);
    adtsHeaderBuf[6] = 0xFC;

    return 0;
}