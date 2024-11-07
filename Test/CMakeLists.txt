add_executable(Tester Tester.c)
target_link_libraries(Tester VisualOutput)

add_test(NAME Tester COMMAND Tester)

