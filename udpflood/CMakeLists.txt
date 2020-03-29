cmake_minimum_required( VERSION 2.8 )
set( CMAKE_CXX_FLAGS "-std=c++14" )

##是否启用日志


SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -D _NO_LOG_ -D NS3_CORE")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -D _NO_LOG_")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -D NS3_CORE")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -D NS3_CORE")

##[修改这里]##
PROJECT(udpflood)
MESSAGE(STATUS "Project HSP-NS udpflood")

# 头文件
include_directories(
${PROJECT_SOURCE_DIR}/../core/include/
${PROJECT_SOURCE_DIR}/../network/include/
${PROJECT_SOURCE_DIR}/
${PROJECT_SOURCE_DIR}/../lib/ns-3-dev/build/
)

# 源文件
##[修改这里]##
aux_source_directory(${PROJECT_SOURCE_DIR}/../core/src CORE_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/../network/src NETWORK_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/ TEST_SRC)

set(LIB_CORE_NAME nscore)
add_library(${LIB_CORE_NAME} STATIC ${CORE_SRC})

set(LIB_NETWORK_NAME netwrok)
add_library(${LIB_NETWORK_NAME} STATIC ${NETWORK_SRC})

# 编译主函数，生成可执行文件
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${TEST_SRC})

# 找到g3logger
find_package(g3logger CONFIG REQUIRED)

# 找到ns3 core
set(LIB_NS3_CORE "${PROJECT_SOURCE_DIR}/../lib/ns-3-dev/build/lib/libns3-dev-core-debug.so")

# 把库链接起来
target_link_libraries(${PROJECT_NAME} ${LIB_CORE_NAME} ${LIB_NETWORK_NAME} pthread g3logger ${LIB_NS3_CORE}) 

