add_library(scanCords scanCords.c)
add_library(bruteforce bruteforce.c)

add_executable(main main.c)

target_link_libraries(main scanCords bruteforce)
