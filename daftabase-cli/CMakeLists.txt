set(SRC_FILES main.cpp)

add_executable(daftabase-cli ${SRC_FILES})
target_link_libraries(daftabase-cli daftabase)