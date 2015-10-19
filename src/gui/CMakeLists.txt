# wxWidgets libraries and includes.
find_package(wxWidgets COMPONENTS core base gl REQUIRED)
include(${wxWidgets_USE_FILE})
set(LIBS ${LIBS} ${wxWidgets_LIBRARIES})

# Glut libraries and includes.
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLUT_LIBRARIES})

add_library(gui canvas.cc window.cc)
set(LIBS ${LIBS})
target_link_libraries(gui GL ${LIBS})
