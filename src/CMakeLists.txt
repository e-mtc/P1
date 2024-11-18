add_library(scanCords scanCords.c)
add_library(bruteforce bruteforce.c)

target_link_libraries(bruteforce m)
target_include_directories(bruteforce PUBLIC .)

add_executable(main main.c)

target_link_libraries(main scanCords bruteforce)
