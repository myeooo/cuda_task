cmake_minimum_required(VERSION 3.18)
project(test_cuda LANGUAGES CXX CUDA)

# Tất cả file .cu
file(GLOB CUDA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/cuda/*.cu"
)

# Tất cả file .cpp trong mọi thư mục con
file(GLOB CPP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/practice/*.cpp"
)
add_executable(app
    main.cpp
    practice/add_vector.cpp
    practice/dot_product_vector.cpp
    ${CUDA_SOURCES}
)


set_target_properties(app PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES "75"
)
