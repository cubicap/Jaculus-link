cmake_minimum_required(VERSION 3.0)


if(ESP_PLATFORM)
    idf_component_register(
        INCLUDE_DIRS .
    )

else()
    add_library(jac-link INTERFACE)
    target_include_directories(jac-link INTERFACE .)

endif()
