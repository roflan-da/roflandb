FILE(GLOB SRC "./*.cpp")

add_library(table SHARED ${SRC})

target_include_directories(table PUBLIC inc)
