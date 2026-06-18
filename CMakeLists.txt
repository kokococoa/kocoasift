cmake_minimum_required(VERSION 3.16)

project(kocoasift
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(KOCOASIFT_OPENCV_DIR "" CACHE PATH "OpenCV build directory used by kocoasift")

if(KOCOASIFT_OPENCV_DIR)
  set(OpenCV_DIR "${KOCOASIFT_OPENCV_DIR}" CACHE PATH "OpenCV package directory" FORCE)
endif()

# ================ Dependencies ================
find_package(OpenCV REQUIRED COMPONENTS core features2d imgcodecs imgproc)
find_package(CUDAToolkit REQUIRED)

message(STATUS "kocoasift OpenCV version: ${OpenCV_VERSION}")
message(STATUS "kocoasift OpenCV_DIR: ${OpenCV_DIR}")
message(STATUS "kocoasift OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "kocoasift OpenCV libraries: ${OpenCV_LIBS}")
message(STATUS "kocoasift CUDA Toolkit version: ${CUDAToolkit_VERSION}")
message(STATUS "kocoasift CUDA Toolkit root: ${CUDAToolkit_TARGET_DIR}")
message(STATUS "kocoasift CUDA Toolkit bin dir: ${CUDAToolkit_BIN_DIR}")
message(STATUS "kocoasift CUDA Toolkit include dirs: ${CUDAToolkit_INCLUDE_DIRS}")
message(STATUS "kocoasift CUDA Toolkit library dir: ${CUDAToolkit_LIBRARY_DIR}")


set(LIBS 
  opencv_core
  opencv_features2d
  opencv_imgcodecs
  opencv_imgproc
  CUDA::cudart
)

# ================ KocoaSIFT Source Library ================
add_library(kocoasift
  src/detect.cpp
  src/frontend.cpp
  src/parameters.cpp
)

target_include_directories(kocoasift
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(kocoasift
  PUBLIC
    ${LIBS}
)

target_compile_features(kocoasift PUBLIC cxx_std_17)

# ================ Tests ================
add_executable(test_main
  test/test_main.cpp
)
target_link_libraries(test_main
  PRIVATE
    kocoasift
    ${LIBS}
)

add_executable(test_frontend
  test/test_frontend.cpp
)
target_link_libraries(test_frontend
  PRIVATE
    kocoasift
    ${LIBS}
)

add_executable(test_gaussian
  test/test_gaussian.cpp
)
target_link_libraries(test_gaussian
  PRIVATE
    kocoasift
    ${LIBS}
)

# ================ Testing ================
enable_testing()
add_test(NAME test_main COMMAND test_main)
add_test(NAME test_frontend COMMAND test_frontend)
add_test(NAME test_gaussian COMMAND test_gaussian)
