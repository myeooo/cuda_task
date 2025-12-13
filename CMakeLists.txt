cmake_minimum_required(VERSION 3.18)
project(test_cuda LANGUAGES CXX CUDA)

file(GLOB CUDA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/cuda/*.cu"
)

file(GLOB CPP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/algorithm/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data_binding/*.cpp"
)

add_executable(app
    main.cpp
    algorithm/vector_processing.cpp
    ${CUDA_SOURCES}
    ${CPP_SOURCES}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cuda
    ${CMAKE_CURRENT_SOURCE_DIR}/data_binding
)

set_target_properties(app PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES "75"
)
