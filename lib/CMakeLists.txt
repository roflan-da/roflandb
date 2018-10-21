FILE(GLOB SRC "./*.cpp")

add_library(keklib SHARED ${SRC})
target_include_directories(keklib PUBLIC inc/)
