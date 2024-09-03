#include <iostream>
#include <fmt/core.h>
#include "libgit2pp/repository.hpp"
#include "libgit2pp/revwalk.hpp"

using namespace libgit2pp;

int main(int argc, char **argv)
{
    // auto repo = repository::open(".");
    // auto oid = repo.reference_name_to_id("HEAD");
    // fmt::println(oid.to_str());
    std::string_view path;
    if (argc == 1)
    {
        path = ".";
    }
    else if (argc >= 2)
    {
        path = argv[1];
    }
    fmt::println("looking for repo in {}", path);
    auto repo = repository::open(path);
    revwalk walker(repo);
    while (auto oid = walker.next())
    {
        auto cmt = repo.lookup_commit(*oid);
        auto msg = cmt.message();
        fmt::println(msg);
    }
}