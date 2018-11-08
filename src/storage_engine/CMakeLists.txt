FILE(GLOB SRC "./*.cpp")

add_library(storage_engine SHARED ${SRC})
target_include_directories(storage_engine PUBLIC inc)
target_link_libraries(storage_engine PUBLIC table)
