MESSAGE(STATUS "This is CMake ${CMAKE_VERSION}")
MESSAGE(STATUS "")

cmake_minimum_required(VERSION 3.10)

project(
  HW_4
  VERSION 1.0
  LANGUAGES CXX
)

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# project source files 
add_executable(my_program
    main.cc
    my_matrix.cc
)

# runtime output directory
set_target_properties(my_program PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/EXECUTABLE"
)

# Header search path
target_include_directories(my_program PRIVATE ${CMAKE_SOURCE_DIR})

# BLAS / LAPACK
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
target_link_libraries(my_program PRIVATE ${LAPACK_LIBRARIES} ${BLAS_LIBRARIES})
