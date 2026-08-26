# CMake configurations.
cmake_minimum_required(VERSION 3.20)
project(ProjectName LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch dependencies.
include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY "https://github.com/glfw/glfw.git" GIT_TAG 3.5.1)
FetchContent_Declare(glm GIT_REPOSITORY "https://github.com/g-truc/glm.git" GIT_TAG 1.0.3)
FetchContent_Declare(stb GIT_REPOSITORY "https://github.com/nothings/stb" GIT_TAG master)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(stb)

# Create executable.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*")
add_executable(${PROJECT_NAME} ${SOURCES} "${PROJECT_SOURCE_DIR}/third_party/glad/src/glad.c")

# Add header search paths.
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/shaders")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/third_party/glad/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${stb_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm::glm)

# Extra.
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_ROOT="${PROJECT_SOURCE_DIR}")