
add_library(Draw draw.cpp draw.hpp)

#target_link_libraries(Draw sfml-graphics)

target_include_directories(Draw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})