cmake_minimum_required(VERSION 3.0)

set(JAC_LINK_SRC
    "jac/link/router.cpp"
)


if(ESP_PLATFORM)
    idf_component_register(
        SRCS ${JAC_LINK_SRC}
        INCLUDE_DIRS .
    )

else()
    add_library(jac-link STATIC ${JAC_LINK_SRC})
    target_include_directories(jac-link PUBLIC .)

endif()
