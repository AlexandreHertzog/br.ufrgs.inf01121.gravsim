# For the debug flags.
include_directories("${PROJECT_BINARY_DIR}")

# wxWidgets libraries and includes.
find_package(wxWidgets COMPONENTS core base gl REQUIRED)
include(${wxWidgets_USE_FILE})
set(LIBS ${LIBS} ${wxWidgets_LIBRARIES})

# GLU libraries.
find_package(OpenGL REQUIRED)
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})

# Glut libraries.
find_package(GLUT REQUIRED)
set(LIBS ${LIBS} ${GLUT_LIBRARY})

# All OpenGL includes.
include_directories(${GLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

# Engine includes.
include_directories("${PROJECT_SOURCE_DIR}/engine")

set(CMAKE_BUILD_TYPE Debug)
add_library(gui canvas.cc window.cc point.cc)
target_link_libraries(gui ${LIBS})
set_property(TARGET gui PROPERTY CXX_STANDARD 11)
