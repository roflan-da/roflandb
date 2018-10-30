FILE(GLOB SRC "./*.cpp")

add_library(parser SHARED ${SRC} inc/createStatement.h createStatement.cpp)

target_include_directories(parser PUBLIC inc)

target_link_libraries(parser PUBLIC commands)
