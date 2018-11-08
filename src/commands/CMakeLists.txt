FILE(GLOB SRC "./*.cpp")

add_library(commands SHARED ${SRC})

target_include_directories(commands PUBLIC inc)
target_link_libraries(commands PUBLIC query_conditions)
