cmake_minimum_required(VERSION 3.0)

Include(FetchContent)
include(CTest)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.2.0
)

FetchContent_MakeAvailable(Catch2)


add_executable(cobs "cobs.cpp")
target_link_libraries(cobs PUBLIC jac-link Catch2::Catch2WithMain)

add_executable(mux "mux.cpp")
target_link_libraries(mux PUBLIC jac-link Catch2::Catch2WithMain)

add_executable(router "router.cpp")
target_link_libraries(router PUBLIC jac-link Catch2::Catch2WithMain)

add_executable(routerCommunicator "routerCommunicator.cpp")
target_link_libraries(routerCommunicator PUBLIC jac-link Catch2::Catch2WithMain)

add_executable(crc "crc.cpp")
target_link_libraries(crc PUBLIC jac-link Catch2::Catch2WithMain)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC jac-link)

add_test(NAME cobs COMMAND ${EXECUTABLE_OUTPUT_PATH}/cobs)
add_test(NAME mux COMMAND ${EXECUTABLE_OUTPUT_PATH}/mux)
add_test(NAME router COMMAND ${EXECUTABLE_OUTPUT_PATH}/router)
add_test(NAME routerCommunicator COMMAND ${EXECUTABLE_OUTPUT_PATH}/routerCommunicator)
add_test(NAME crc COMMAND ${EXECUTABLE_OUTPUT_PATH}/crc)
