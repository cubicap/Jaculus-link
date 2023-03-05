cmake_minimum_required(VERSION 3.0)

set(LINK
    "jac/link/router.cpp"
)

if(NOT ESP_PLATFORM)
    add_library(jac-link STATIC ${LINK})
    target_include_directories(jac-link PUBLIC .)

else()
    idf_component_register(
        SRCS ${LINK}
        INCLUDE_DIRS .
    )

endif()
