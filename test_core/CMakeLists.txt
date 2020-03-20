cmake_minimum_required( VERSION 2.8 )
set( CMAKE_CXX_FLAGS "-std=c++11" )


PROJECT(nstest)
MESSAGE(STATUS "Project HSP-NS test") #打印相关消息消息

# 头文件
include_directories(
${PROJECT_SOURCE_DIR}/../core/include/
${PROJECT_SOURCE_DIR}/../lib/rlog/include/
${PROJECT_SOURCE_DIR}/
)

# 源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/ TEST_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/../core/src CORE_SRC)

set(LIB_CORE_NAME nscore)
add_library(${LIB_CORE_NAME} STATIC ${CORE_SRC})

# 编译主函数，生成可执行文件
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${TEST_SRC})

# 找到g3logger
#link_libraries(${PROJECT_SOURCE_DIR}/../lib/g3log-1.3.1/build/libg3logger.so)

# 把库链接起来
target_link_libraries(${PROJECT_NAME} ${LIB_CORE_NAME} pthread -lg3logger) 

