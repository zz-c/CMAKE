# java

## 生成 JNI 头文件
javac -h . HelloWorldJNI.java  
## 编译  
javac top/zhost/jni/HelloWorldJNI.java  
java top.zhost.jni.HelloWorldJNI  

# linux bulid

## 创建构建目录
mkdir build && cd build

## 运行 CMake 配置
cmake ..

## 编译
make