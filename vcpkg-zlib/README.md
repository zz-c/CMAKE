# ��¡ vcpkg�������δ��װ��
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

# ��ʼ�� vcpkg��Windows ʹ�� .\bootstrap-vcpkg.bat��
.\bootstrap-vcpkg.bat

# ��װ zlib��������Ŀ�ܹ�ѡ��
.\vcpkg install zlib:x64-windows    # 64λ
.\vcpkg install zlib:x86-windows    # 32λ

# ���� vcpkg �� Visual Studio
.\vcpkg integrate install

���Ӧ��ʾ��
Applied user-wide integration for this vcpkg root.
All MSBuild C++ projects can now #include any installed libraries.