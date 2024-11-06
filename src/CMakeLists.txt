add_executable(main main.c)

add_library(bruteforce bruteforce.c)
target_link_libraries(bruteforce m)
target_include_directories(bruteforce PUBLIC .)

target_link_libraries(main bruteforce m)
