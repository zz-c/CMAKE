#pragma once

#include <cstdint>

struct AdtsHeader {
    unsigned int syncword;  //12 bit ͬ���� '1111 1111 1111'��˵��һ��ADTS֡�Ŀ�ʼ
    unsigned int id;        //1 bit MPEG ��ʾ���� 0 for MPEG-4��1 for MPEG-2
    unsigned int layer;     //2 bit ����'00'
    unsigned int protectionAbsent;  //1 bit 1��ʾû��crc��0��ʾ��crc
    unsigned int profile;           //1 bit ��ʾʹ���ĸ������AAC
    unsigned int samplingFreqIndex; //4 bit ��ʾʹ�õĲ���Ƶ��
    unsigned int privateBit;        //1 bit
    unsigned int channelCfg; //3 bit ��ʾ������
    unsigned int originalCopy;         //1 bit
    unsigned int home;                  //1 bit

    /*�����Ϊ�ı�Ĳ�����ÿһ֡����ͬ*/
    unsigned int copyrightIdentificationBit;   //1 bit
    unsigned int copyrightIdentificationStart; //1 bit
    unsigned int aacFrameLength;               //13 bit һ��ADTS֡�ĳ��Ȱ���ADTSͷ��AACԭʼ��
    unsigned int adtsBufferFullness;           //11 bit 0x7FF ˵�������ʿɱ������

    /* number_of_raw_data_blocks_in_frame
     * ��ʾADTS֡����number_of_raw_data_blocks_in_frame + 1��AACԭʼ֡
     * ����˵number_of_raw_data_blocks_in_frame == 0
     * ��ʾ˵ADTS֡����һ��AAC���ݿ鲢����˵û�С�(һ��AACԭʼ֡����һ��ʱ����1024���������������)
     */
    unsigned int numberOfRawDataBlockInFrame; //2 bit
};

int parseAdtsHeader(uint8_t* headerBuf, struct AdtsHeader* adtsHeader);
int convertAdtsHeaderToBuf(struct AdtsHeader* adtsHeader, uint8_t* adtsHeaderBuf);

