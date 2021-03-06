# cmake最低版本号要求
cmake_minimum_required(VERSION 3.14)

# 项目名
project(test_proj)

set(CMAKE_CXX_STANDARD 14)

# 添加头文件
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/googlemock/include
)

# 添加下级目录，生成.a文件
# googlemock中包含googletest, 此处只引入googlemock即可
add_subdirectory(./googlemock)

# 添加连接库
link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/googlemock
)

set(SOUCE_FLIES
        main_gmock.cpp
        lib/HelloWorld.cpp
        include/HelloWorld.h
        include/Messenger.h
        include/MockMessenger.h)

# 指定可执行文件的生成位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# 指定生成目标
add_executable(test_proj ${SOUCE_FLIES})

# 将目标文件与库文件进行链接
target_link_libraries(test_proj gmock)
