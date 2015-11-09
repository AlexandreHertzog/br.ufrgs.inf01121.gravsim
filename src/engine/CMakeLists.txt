# For the debug flags.
include_directories("${PROJECT_BINARY_DIR}")

# For the GUI stuff
include_directories("${PROJECT_SOURCE_DIR}/gui")
set(LIBS ${LIBS} gui)

set(CMAKE_BUILD_TYPE Debug)
add_library(engine storage.cc logger.cc)
target_link_libraries(engine ${LIBS})
set_property(TARGET engine PROPERTY CXX_STANDARD 11)
