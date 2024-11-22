add_library(scanCords scanCords.c)
add_library(bruteforce bruteforce.c)
add_library(VisualOutput VisualOutput.c)

target_link_libraries(bruteforce m)
target_include_directories(bruteforce PUBLIC .)
#target_include_directories(VisualOutput PUBLIC .)

add_executable(main main.c)

target_link_libraries(main scanCords VisualOutput bruteforce)
