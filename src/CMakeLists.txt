file(GLOB sources "*.cpp" "./libgit2pp/*.cpp")

add_executable(today ${sources})

target_link_libraries(today fmt::fmt git2)
