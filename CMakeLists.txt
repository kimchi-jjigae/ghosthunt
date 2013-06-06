#cmake ver req
cmake_minimum_required(VERSION 2.8.3)

set(USE_CLANG FALSE CACHE BOOL "Select this if you want to use CLANG")
set(CLANG_PATH "/usr/bin/clang++" CACHE PATH "Path to run CLANG from")
set(STRICT_BUILD TRUE CACHE BOOL "Makes use of the -Wall -Wextra and -Werror flags")
set(DEBUG_BUILD TRUE CACHE BOOL "Turns off optimisation and builds debug info")
set(FRAMEWORK_PATH "/change/this/" CACHE PATH "Path to the root of the framework")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for executables

#project name
set(project_name ghosthunt)
project(${project_name})

if(USE_CLANG)
    set(CMAKE_CXX_COMPILER ${CLANG_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    if(STRICT_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")
    endif()
    if(DEBUG_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    endif()
else()
    if(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        if(STRICT_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter")
        endif()

        if(DEBUG_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

        if(DEBUG_BUILD)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
        endif()
    endif()
endif()

include_directories(${FRAMEWORK_PATH}/include)
link_directories("${FRAMEWORK_PATH}/lib")

file(GLOB_RECURSE ghosthunt_source_files "src/*.cpp")
file(GLOB_RECURSE ghosthunt_header_files "src/*.h")

add_executable(${project_name} ${ghosthunt_header_files} ${ghosthunt_source_files})
target_link_libraries(${project_name} windlab-entity windlab-ui windlab-app libsfml-graphics.so libsfml-window.so)
