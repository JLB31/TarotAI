cmake_minimum_required(VERSION 3.16)
project(TarotAI VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source and include directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Add executable
add_executable(tarot 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Cards.cpp
    ${SRC_DIR}/Rules.cpp
#    ${SRC_DIR}/DatasetExporter.cpp
    ${SRC_DIR}/GameEngine.cpp
)
target_include_directories(tarot PRIVATE ${INCLUDE_DIR})

include(FetchContent)

# Fetch SFML 3.0.1
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(sfml)

# TENSORFLOW 2.6.0
set(TENSORFLOW_VERSION 2.6.0)
set(TENSORFLOW_URL "https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-cpu-linux-x86_64-${TENSORFLOW_VERSION}.tar.gz")
FetchContent_Declare(
  tensorflow_c
  URL ${TENSORFLOW_URL}
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/tensorflow_c-${TENSORFLOW_VERSION}
)
FetchContent_MakeAvailable(tensorflow_c)
include_directories(${tensorflow_c_SOURCE_DIR}/include)
link_directories(${tensorflow_c_SOURCE_DIR}/lib)

# Link SFML modules
target_link_libraries(tarot PRIVATE sfml-graphics sfml-window sfml-system)
