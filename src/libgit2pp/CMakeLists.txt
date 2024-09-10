file(GLOB sources "*.cpp")

add_library(libgit2pp ${sources})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(libgit2pp PRIVATE -DDEBUG)
endif()

target_include_directories(libgit2pp PUBLIC "include")

target_link_libraries(libgit2pp fmt::fmt git2 spdlog::spdlog)

