cmake_minimum_required(VERSION 3.20)
project(daftabase VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third-party)
add_subdirectory(daftabase)
add_subdirectory(daftabase-cli)
add_subdirectory(daftabase-test)
