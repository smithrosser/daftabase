set(PROJECT_SRCS daftabase.cpp keystore.cpp)

add_library(daftabase STATIC ${PROJECT_SRCS})
target_include_directories(daftabase PRIVATE .)
target_include_directories(daftabase INTERFACE include)
