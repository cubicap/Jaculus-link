cmake_minimum_required(VERSION 3.0)

project(Jaculus-link)


if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_EXTENSIONS ON)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_EXTENSIONS ON)

    if (CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "-Wall -Wold-style-cast -Wshadow -fdiagnostics-color")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()

endif()


add_subdirectory(src)


if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    enable_testing()
    add_subdirectory(tests)

endif()
