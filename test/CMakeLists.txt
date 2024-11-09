
add_executable(test_paths test_paths.c)

target_link_libraries(test_paths bruteforce m)
add_test(NAME test_paths COMMAND test_paths)
