set(CMAKE_BUILD_TYPE Debug)
add_library(engine storage.cc logger.cc gsobject.cc runner.cc)
set_property(TARGET engine PROPERTY CXX_STANDARD 11)
