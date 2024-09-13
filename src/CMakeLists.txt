file(GLOB sources "*.cpp")

add_executable(today ${sources})

add_subdirectory(libgit2pp)

# pthread is required for date-tz
target_link_libraries(today fmt::fmt libgit2pp tabulate date::date date::date-tz spdlog::spdlog cxxopts::cxxopts pthread)

target_compile_definitions(today PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    PROJECT_VERSION="${CMAKE_PROJECT_VERSION}"
)
