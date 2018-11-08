FILE(GLOB SRC "./*.cpp")

add_library(query_conditions SHARED ${SRC})

target_include_directories(query_conditions PUBLIC inc)
