add_executable(TestTextFile TestTextFile.c
        TestTextFile.h)
add_executable(test_paths test_paths.c)

target_link_libraries(test_paths bruteforce m)
target_link_libraries(TestTextFile bruteforce m)
add_test(NAME test_paths COMMAND test_paths)
add_test(NAME TestTextFile COMMAND TestTextFile)
