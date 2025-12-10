cmake_minimum_required(VERSION 3.18)
project(test_cuda LANGUAGES CXX CUDA)

# Bật tất cả CUDA file trong folder cuda/
file(GLOB CUDA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/cuda/*.cu"
)
file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Tạo executable
add_executable(app ${CPP_SOURCES} ${CUDA_SOURCES})

# Compile options
set_target_properties(app PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES "75"   # RTX 2060 = compute capability 7.5
)
