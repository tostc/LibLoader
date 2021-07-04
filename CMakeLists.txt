cmake_minimum_required(VERSION 3.3.0)
project(libloader VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(SRCS 
    "${PROJECT_SOURCE_DIR}/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/LibLoader.cpp")
set(LIBS "")

if(UNIX)
    set(SRCS ${SRCS} "${PROJECT_SOURCE_DIR}/src/Unix/UnixLibHandle.cpp")
    set(LIBS "dl")
else(UNIX)
    set(SRCS ${SRCS} "${PROJECT_SOURCE_DIR}/src/Windows/WindowsLibHandle.cpp")
endif(UNIX)

add_library(${PROJECT_NAME} STATIC ${SRCS})
target_link_libraries(${PROJECT_NAME} ${LIBS})