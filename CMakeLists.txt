cmake_minimum_required(VERSION 2.6)
project(ch2d)

include(ExternalProject)

# Set paths to external MPI library files

set( MPI_LIBRARIES "~/Projects/AEOLUS/cahn_hilliard_2d/build/external/petsc/linux-gnu-c-debug/lib/libmpi.so" )
# find_package(MPI REQUIRED)

set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  #set(CMAKE_BUILD_TYPE "Release")
endif()

add_definitions( -DSRCDIR=\"${CMAKE_SOURCE_DIR}/\")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -Werror=reorder")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -DBOOST_LOG_DYN_LINK -DNDEBUG")

# Build external dependencies

set( EXTERNAL_INSTALL_DIR ${CMAKE_BINARY_DIR}/external_install )
add_subdirectory(external)

include_directories(
                     ${MPI_INCLUDE_PATH}
                     ${CMAKE_SOURCE_DIR}
		     ${PETSC_INCLUDES}	     
)

MESSAGE( STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}" )
MESSAGE( STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}" )
MESSAGE( STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}" )
MESSAGE( STATUS "C++ compiler string: ${CXX_COMPILER_STRING}" )
MESSAGE( STATUS "MPI C++ compiler: ${MPI_CXX_COMPILER}" )
MESSAGE( STATUS "MPI C++ compiler options: ${MPI_CXX_COMPILE_OPTIONS}" )
MESSAGE( STATUS "MPI libraries: ${MPI_LIBRARIES}")
MESSAGE( STATUS "Petsc include dir: ${PETSC_INCLUDES}" )
MESSAGE( STATUS "Petsc libraries: ${PETSC_LIBRARIES}")

#############################################
# Postprocessing
#############################################

add_executable( postprocess
  src/postprocess.cpp
  src/utils_ch.cpp
)

add_dependencies(postprocess petsc_external)

target_link_libraries( postprocess
  m
  ${MPI_LIBRARIES}
  ${PETSC_LIBRARIES}
)

#############################################
# Preprocessing
#############################################

add_executable( preprocess
  src/preprocess.cpp
  src/utils_ch.cpp
)

add_dependencies( preprocess petsc_external )

target_link_libraries( preprocess
  m
  ${MPI_LIBRARIES}
  ${PETSC_LIBRARIES}
)

#############################################
# Petsc solver
#############################################

add_executable( ch2d
  src/ch2d.cpp
  src/utils_ch.cpp
  src/boundary_conditions.cpp
  src/initial_conditions.cpp
  src/rhs.cpp
  src/petsc_event_handling.cpp
  src/temperature_dependence.cpp
)

add_dependencies(ch2d petsc_external)

target_link_libraries( ch2d
  m
  ${MPI_LIBRARIES}
  ${PETSC_LIBRARIES}
)

#############################################
# MMS test for solver 
#############################################

add_executable( mmstest_ch2d
  src/mmstest_ch2d.cpp
  src/utils_ch.cpp
  src/boundary_conditions.cpp
  src/initial_conditions.cpp
  src/rhs.cpp
  src/petsc_event_handling.cpp
  src/temperature_dependence.cpp
)

add_dependencies(mmstest_ch2d petsc_external)

target_link_libraries( mmstest_ch2d
  m
  ${MPI_LIBRARIES}
  ${PETSC_LIBRARIES}
)
