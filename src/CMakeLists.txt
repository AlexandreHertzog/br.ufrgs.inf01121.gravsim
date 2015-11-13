project(GravSim)
cmake_minimum_required(VERSION 3.0)

# Debug flags
set(_TEST_RENDER_ 1)
set(_DEBUG_)

# System libraries and includes.
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})
set(LIBS ${LIBS} ${wxWidgets_LIBRARIES})

# CMake-to-code configuration file
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake_defines.hh.in"
  "${PROJECT_BINARY_DIR}/cmake_defines.hh"
)
include_directories("${PROJECT_BINARY_DIR}")

# Local includes.
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/gui")
include_directories("${PROJECT_SOURCE_DIR}/assets")
include_directories("${PROJECT_SOURCE_DIR}/engine")
include_directories("${PROJECT_SOURCE_DIR}/exception")
add_subdirectory(gui)
add_subdirectory(assets)
add_subdirectory(engine)
set(LIBS ${LIBS} engine)
set(LIBS ${LIBS} gui)
set(LIBS ${LIBS} assets)

# The wrap-up stuff
set(CMAKE_BUILD_TYPE Debug)
add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} ${LIBS})
set_property(TARGET GravSim PROPERTY CXX_STANDARD 11)
