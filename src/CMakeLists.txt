project(GravSim)
cmake_minimum_required(VERSION 3.0)

# System libraries and includes.
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})
set(LIBS ${LIBS} ${wxWidgets_LIBRARIES})

# Local includes.
include_directories("${PROJECT_SOURCE_DIR}/gui")
add_subdirectory(gui)
set(LIBS ${LIBS} gui)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} ${LIBS})
