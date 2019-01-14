# CMakeList.txt: miniplayer 的 CMake 项目，包括源和定义
# 此处特定于项目的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories (../combase)

# 将源添加到此项目的可执行文件。
add_library (mythread "mythread.h" "mythread.cpp")

# TODO: 如有需要，请添加测试并安装目标。
