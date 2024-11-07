add_executable(test-VisMinefelt test-VisMinefelt.c)

target_link_libraries(test-VisMinefelt VisualoutputAnas)

add_test(NAME test-VisMinefelt
        COMMAND test-VisMinefelt)

