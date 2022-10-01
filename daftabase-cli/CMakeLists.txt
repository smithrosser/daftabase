set(SRC_FILES main.cpp app.cpp)

add_executable(daftabase-cli ${SRC_FILES})
target_link_libraries(daftabase-cli PRIVATE daftabase)
target_link_libraries(daftabase-cli PRIVATE cxxopts)