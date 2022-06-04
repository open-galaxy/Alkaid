#Alkaid
project(alkaid) 
cmake_minimum_required(VERSION 3.2)

# V8 高版本需要 C++14 以上
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
set(V8_ROOT ${CMAKE_CURRENT_LIST_DIR}/deps/v8)

# 链接 V8 头文件
include_directories(${V8_ROOT}/include)
include_directories(${V8_ROOT})
# 链接 V8 库文件
link_directories(${V8_ROOT})
link_libraries(v8_monolith)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ROOT)
add_executable(${PROJECT_NAME} ${ROOT})

# 添加编译 V8 embed 所需要的定义
target_compile_definitions(${PROJECT_NAME} PRIVATE V8_COMPRESS_POINTERS V8_31BIT_SMIS_ON_64BIT_ARCH)
# 链接系统动态库 dlopen、dlclose、dlsym
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})