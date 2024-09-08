file(GLOB sources "*.cpp")

add_library(libgit2pp ${sources})

target_include_directories(libgit2pp PUBLIC "include")

target_link_libraries(libgit2pp fmt::fmt git2)
