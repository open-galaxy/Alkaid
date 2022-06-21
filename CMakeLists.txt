#Alkaid
project(alkaid) 
cmake_minimum_required(VERSION 3.2)

# V8 高版本需要 C++17 以上
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(V8_ROOT ${CMAKE_CURRENT_LIST_DIR}/deps/v8)
set(LLHTTP_ROOT ${CMAKE_CURRENT_LIST_DIR}/deps/llhttp)

# 链接 V8 头文件
include_directories(${V8_ROOT}/include)
# 链接 V8 库文件
link_directories(${V8_ROOT})
link_libraries(v8_monolith)

# 支持打印错误栈
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/deps/backward-cpp)

# llhttp
include_directories(${LLHTTP_ROOT}/build)
link_directories(${LLHTTP_ROOT}/build)
link_libraries(llhttp)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ROOT)
add_executable(${PROJECT_NAME} ${ROOT} ${BACKWARD_ENABLE})

# 添加编译 V8 embed 所需要的定义
target_compile_definitions(${PROJECT_NAME} PRIVATE V8_COMPRESS_POINTERS V8_31BIT_SMIS_ON_64BIT_ARCH)
# 链接系统动态库 dlopen、dlclose、dlsym
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
add_backward(${PROJECT_NAME})