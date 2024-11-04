add_executable(main main.c)

add_library(bruteforce bruteforce.c)
target_link_libraries(main bruteforce)
