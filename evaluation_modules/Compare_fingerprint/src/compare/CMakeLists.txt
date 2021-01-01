# Build and run sample using CMake:
# mkdir _build && cd _build
# cmake ..
# cmake --build .
# ctest -V


cmake_minimum_required(VERSION 3.12)
project(compare)

# idkit library
if(NOT TARGET idkit::idkit)
  set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/../../lib/cmake/idkit ${CMAKE_PREFIX_PATH})
  find_package(idkit REQUIRED)
endif()

# Build sample
add_executable(${CMAKE_PROJECT_NAME} compare.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} idkit::idkit)
if(IDKIT_BUILD_ANDROID AND (IDKIT_FACIAL_MODALITY OR IDKIT_IRIS_MODALITY))
  target_link_libraries(${CMAKE_PROJECT_NAME} ../../log)
endif()


# Install components
install(FILES "compare.cpp" DESTINATION ${CMAKE_CURRENT_LIST_DIR})
install(TARGETS "${CMAKE_PROJECT_NAME}" DESTINATION ../../bin)

