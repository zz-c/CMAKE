ffmpeg命令行 从mp4视频文件提取aac 音频文件
ffmpeg -i test.mp4  -vn -acodec aac output.aac
备注：-i 表示输入文件 
      -vn 丢掉视频
      -acodec 设置音频编码格式

ffmpeg 从aac音频文件解码为pcm音频文件
ffmpeg -i output.aac -f s16le output.pcm
备注：-i 表示输入文件 
      -f 表示输出格式
