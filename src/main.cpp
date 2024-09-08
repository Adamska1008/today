#include <iostream>
#include <vector>
#include <fmt/core.h>
#include <chrono>
#include "repository.hpp"
#include "revwalk.hpp"

using namespace libgit2pp;

struct commit_info
{
    std::string author;
    std::string message;
    std::chrono::time_point<std::chrono::system_clock> time;
    std::string branch;
    int lines_added;
    int lines_removed;
    int files_changed;
};

std::vector<commit_info> collect_info(std::string_view directory)
{
    std::vector<commit_info> result;
    auto repo = repository::open(directory);
    auto walker = revwalk(repo);
    walker.push_head();
    while (auto oid = walker.next())
    {
        auto commit = repo.lookup_commit(*oid);
    }
}

int main(int argc, char **argv)
{
    auto cs = collect_info(".");
}