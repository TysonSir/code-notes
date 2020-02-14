# cmake最低版本号要求
cmake_minimum_required(VERSION 3.14)

# 项目名
project(gtest_proj)

set(CMAKE_CXX_STANDARD 14)

# 添加头文件
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/include
)

# 添加下级目录，生成.a文件
add_subdirectory( ./googletest)

# 添加连接库
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest
)

set(SOUCE_FLIES
        main.cpp
        lib/add.cpp
        include/add.h)

# 指定可执行文件的生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# 指定生成目标
add_executable(gtest_proj ${SOUCE_FLIES})

# 将目标文件与库文件进行链接
target_link_libraries(gtest_proj gtest)
