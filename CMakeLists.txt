cmake_minimum_required(VERSION 3.18)
project(test_cuda LANGUAGES CXX CUDA)

# --------------------
# Compiler settings
# --------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# --------------------
# Dependencies (via vcpkg hoặc conan)
# --------------------
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# --------------------
# Source files
# --------------------
file(GLOB CUDA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/compute/*.cu"
)

file(GLOB CPP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/data_binding/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/app/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/context/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/render/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/algorithm/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/render/circleRenderer/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/render/shader/*.cpp"

)

add_executable(app
    ${CPP_SOURCES}
    ${CUDA_SOURCES}
)

target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/compute
    ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data_binding
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render
    ${CMAKE_CURRENT_SOURCE_DIR}/src/context
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/circleRenderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/render/shader
)

# --------------------
# CUDA settings
# --------------------
set_target_properties(app PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_ARCHITECTURES "75"          # Nếu GPU khác: 61, 70, 75, 86, 89...
)

# --------------------
# Link libraries
# --------------------
target_link_libraries(app PRIVATE
    glfw
    GLEW::GLEW
    imgui::imgui
    glm::glm
)

