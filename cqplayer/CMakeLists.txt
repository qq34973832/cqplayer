# CMakeList.txt: cqplayer 的 CMake 项目，包括源和定义
# 此处特定于项目的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories (../combase ../mythread ../basetype)
include_directories (./interface ./krender ./ksource ./kclock ./kframe)
link_directories (../)

aux_source_directory (./interface source_interface)
aux_source_directory (./krender krender)
aux_source_directory (./ksource ksource)
aux_source_directory (./kclock kclock)
aux_source_directory (./kframe kframe)
aux_source_directory (. source_root)

# 将源添加到此项目的可执行文件。
add_executable (cqplayer ${source_interface} ${source_root} ${krender} ${ksource} ${kclock} ${kframe})
target_link_libraries (cqplayer combase mythread)

# TODO: 如有需要，请添加测试并安装目标。
