file(GLOB sources "*.cpp")

add_executable(today ${sources})

add_subdirectory(libgit2pp)

target_link_libraries(today fmt::fmt libgit2pp tabulate date::date)
