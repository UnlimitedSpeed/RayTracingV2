cmake_minimum_required(VERSION 3.16)
project(RayTracingV2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/SDL-release-3.4.16"
    "${CMAKE_BINARY_DIR}/SDL3"
    EXCLUDE_FROM_ALL
)

add_executable(raytracer
    main.cpp
    src/World/World.cpp
    src/Camera/Camera.cpp
    src/Geometry/Object.cpp
)

target_include_directories(raytracer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../libs/nlhoman/single_include"
)
target_link_libraries(raytracer PRIVATE SDL3::SDL3)

if(WIN32 AND SDL_SHARED)
    add_custom_command(TARGET raytracer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3>"
            "$<TARGET_FILE_DIR:raytracer>"
    )
endif()