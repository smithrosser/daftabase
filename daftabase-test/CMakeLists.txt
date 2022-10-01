set(SRC_FILES dbmanagement-test.cpp writeread-test.cpp)

add_executable(daftabase-test ${SRC_FILES})
target_link_libraries(daftabase-test daftabase)
target_link_libraries(daftabase-test Catch2 Catch2WithMain)

add_test(DaftabaseTest daftabase-test)
