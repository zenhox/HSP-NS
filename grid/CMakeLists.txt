cmake_minimum_required( VERSION 2.8 )
set (CMAKE_CXX_STANDARD 17)


PROJECT(grid)
MESSAGE(STATUS "Project HSP-NS grid work")

SET(CMAKE_BUILD_TYPE "Debug")
SET(CORE_TYPE "NS3_CORE")      ## HSP_CORE NS3_CORE   MY_CORE
SET(LOG "OFF")                 ## OFF
SET(THREADPOOL "A")            ## A B

if(CORE_TYPE STREQUAL "MY_CORE")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g2 -ggdb ")
    # 头文件
    include_directories(${PROJECT_SOURCE_DIR}/../core/include/)
    # 源文件
    aux_source_directory(${PROJECT_SOURCE_DIR}/../core/src CORE_SRC)
elseif(CORE_TYPE STREQUAL "HSP_CORE")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g2 -ggdb  -D HSP_CORE")
    # 头文件
    include_directories(${PROJECT_SOURCE_DIR}/../core-parallel/include/)
    # 源文件
    aux_source_directory(${PROJECT_SOURCE_DIR}/../core-parallel/src CORE_SRC)
elseif(CORE_TYPE STREQUAL "NS3_CORE")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O2 -Wall -g2 -ggdb  -D NS3_CORE")
    # 头文件
    include_directories(${PROJECT_SOURCE_DIR}/../core/include/)
    # 源文件
    aux_source_directory(${PROJECT_SOURCE_DIR}/../core/src CORE_SRC)
endif()

if(LOG STREQUAL "OFF") 
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D _NO_LOG_")
endif()

if(THREADPOOL STREQUAL "A") 
    # 头文件
    include_directories(${PROJECT_SOURCE_DIR}/../lib/ThreadPool/)
    # 源文件
    aux_source_directory(${PROJECT_SOURCE_DIR}/../lib/ThreadPool/ THREAD_POOL_SRC)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D THREAD_POOL_A")
elseif(THREADPOOL STREQUAL "B")
    # 头文件
    include_directories(${PROJECT_SOURCE_DIR}/../lib/threadpool11/threadpool11/include)
    # 源文件
    aux_source_directory(${PROJECT_SOURCE_DIR}/../lib/threadpool11/threadpool11/src THREAD_POOL_SRC)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D THREAD_POOL_B")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/../network/include/
    ${PROJECT_SOURCE_DIR}/
    ${PROJECT_SOURCE_DIR}/../lib/ns-3-dev/build/
    ${PROJECT_SOURCE_DIR}/../lib/skiplist/include/
)
aux_source_directory(${PROJECT_SOURCE_DIR}/../network/src NETWORK_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/ TEST_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/../lib/skiplist/src/ SKIPLIST_SRC)

set(LIB_CORE_NAME nscore)
add_library(${LIB_CORE_NAME} STATIC ${CORE_SRC})

set(LIB_NETWORK_NAME netwrok)
add_library(${LIB_NETWORK_NAME} STATIC ${NETWORK_SRC})

set(LIB_THREAD_POOL threadpool)
add_library(${LIB_THREAD_POOL} STATIC ${THREAD_POOL_SRC})

set(LIB_SKIPLIST skiplist)
add_library(${LIB_SKIPLIST} STATIC ${SKIPLIST_SRC})


# 找到g3logger
find_package(g3logger CONFIG REQUIRED)

# 找到ns3 core
set(LIB_NS3_CORE "${PROJECT_SOURCE_DIR}/../lib/ns-3-dev/build/lib/libns3-dev-core-debug.so")

## 找到boost
find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

# 编译主函数，生成可执行文件
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${TEST_SRC})

# 把库链接起来
target_link_libraries(${PROJECT_NAME}  ${LIB_NETWORK_NAME} ${LIB_CORE_NAME} pthread g3logger ${LIB_NS3_CORE} ${LIB_THREAD_POOL} ${LIB_SKIPLIST}) 

