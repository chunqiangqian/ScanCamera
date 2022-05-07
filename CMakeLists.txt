# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Scane_Cameras)

SET (CMAKE_CXX_COMPILER "g++")
SET (CMAKE_CXX_FLAGS "-O3 -g -lm -ldl -pthread")
SET (CMAKE_C_COMPILER "gcc")
SET (CMAKE_C_FLAGS "-O3 -g -lm -ldl -pthread")

include_directories(./lib/)

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./lib                   LIB_SRCS)

# 指定生成目标
add_executable(main /
main.cpp
${LIB_SRCS}
)

