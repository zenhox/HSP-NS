# Install script for directory: /home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibrariesx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-0"
      "$ENV{DESTDIR}/usr/local/lib/libg3logger.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg3logger.so.1.3.0-0;/usr/local/lib/libg3logger.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/cmake/libg3logger.so.1.3.0-0"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/cmake/libg3logger.so"
    )
  foreach(file
      "$ENV{DESTDIR}/usr/local/lib/libg3logger.so.1.3.0-0"
      "$ENV{DESTDIR}/usr/local/lib/libg3logger.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g3log/active.hpp;/usr/local/include/g3log/atomicbool.hpp;/usr/local/include/g3log/crashhandler.hpp;/usr/local/include/g3log/filesink.hpp;/usr/local/include/g3log/future.hpp;/usr/local/include/g3log/g3log.hpp;/usr/local/include/g3log/logcapture.hpp;/usr/local/include/g3log/loglevels.hpp;/usr/local/include/g3log/logmessage.hpp;/usr/local/include/g3log/logworker.hpp;/usr/local/include/g3log/moveoncopy.hpp;/usr/local/include/g3log/shared_queue.hpp;/usr/local/include/g3log/sink.hpp;/usr/local/include/g3log/sinkhandle.hpp;/usr/local/include/g3log/sinkwrapper.hpp;/usr/local/include/g3log/stacktrace_windows.hpp;/usr/local/include/g3log/std2_make_unique.hpp;/usr/local/include/g3log/stlpatch_future.hpp;/usr/local/include/g3log/time.hpp;/usr/local/include/g3log/g2log.hpp;/usr/local/include/g3log/generated_definitions.hpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/g3log" TYPE FILE FILES
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/active.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/atomicbool.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/crashhandler.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/filesink.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/future.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/g3log.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/logcapture.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/loglevels.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/logmessage.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/logworker.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/moveoncopy.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/shared_queue.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/sink.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/sinkhandle.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/sinkwrapper.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/stacktrace_windows.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/std2_make_unique.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/stlpatch_future.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g3log/time.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/src/g2log.hpp"
    "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/cmake/include/g3log/generated_definitions.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/cmake/g3logger/g3loggerConfig.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib/cmake/g3logger" TYPE FILE FILES "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/cmake/g3loggerConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/hox/workspace/bysj/HSP-NS/lib/g3log-1.3.1/cmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
