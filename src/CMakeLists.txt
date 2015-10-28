project(GravSim)
cmake_minimum_required(VERSION 3.0)

# System libraries and includes.
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})
set(LIBS ${LIBS} ${wxWidgets_LIBRARIES})

# Local includes.
include_directories("${PROJECT_SOURCE_DIR}/gui")
include_directories("${PROJECT_SOURCE_DIR}/assets")
add_subdirectory(gui)
add_subdirectory(assets)
set(LIBS ${LIBS} gui)
set(LIBS ${LIBS} assets)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} ${LIBS})
set_property(TARGET GravSim PROPERTY CXX_STANDARD 11)
