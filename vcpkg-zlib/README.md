# 克隆 vcpkg（如果尚未安装）
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

# 初始化 vcpkg（Windows 使用 .\bootstrap-vcpkg.bat）
.\bootstrap-vcpkg.bat

# 安装 zlib（根据项目架构选择）
.\vcpkg install zlib:x64-windows    # 64位
.\vcpkg install zlib:x86-windows    # 32位

# 集成 vcpkg 到 Visual Studio
.\vcpkg integrate install

输出应显示：
Applied user-wide integration for this vcpkg root.
All MSBuild C++ projects can now #include any installed libraries.