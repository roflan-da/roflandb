#FILE(GLOB SRC "./*.cpp")
SET(SRC lex.yy.cc)

add_library(parser SHARED ${SRC})
add_executable(parser_exe ${SRC})

target_include_directories(parser PUBLIC inc)
target_include_directories(parser_exe PUBLIC inc)
target_link_libraries(parser PUBLIC commands)
