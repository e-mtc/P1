add_library(scanCords scanCords.c)

add_executable(program main.c)
target_link_libraries(program scanCords)