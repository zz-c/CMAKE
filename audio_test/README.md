ffmpeg������ ��mp4��Ƶ�ļ���ȡaac ��Ƶ�ļ�
ffmpeg -i test.mp4  -vn -acodec aac output.aac
��ע��-i ��ʾ�����ļ� 
      -vn ������Ƶ
      -acodec ������Ƶ�����ʽ

ffmpeg ��aac��Ƶ�ļ�����Ϊpcm��Ƶ�ļ�
ffmpeg -i output.aac -f s16le output.pcm
��ע��-i ��ʾ�����ļ� 
      -f ��ʾ�����ʽ
