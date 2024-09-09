#include <iostream>
#include <vector>
#include <fmt/core.h>
#include <chrono>
#include <date.h>
#include "repository.hpp"
#include "revwalk.hpp"
#include "diff.hpp"

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

    commit_info from(const commit &cmt, const repository &repo)
    {
        author = cmt.author().name();
        message = cmt.message();
        time = cmt.time();
        auto dif = cmt.diff_from_parent(repo);
        lines_added = dif.stats_insertions();
        lines_removed = dif.stats_deletions();
        files_changed = dif.stats_files_changed();
        
    }
};

bool is_today(std::chrono::system_clock::time_point tp)
{
    auto today = date::floor<date::days>(std::chrono::system_clock::now());
    auto tp_day = date::floor<date::days>(tp);
    return today == tp_day;
}

std::vector<commit_info> collect_info(std::string_view directory)
{
    std::vector<commit_info> result;
    auto repo = repository::open(directory);
    auto head_commit = repo.head_commit();
    auto walker = revwalk(repo);
    walker.push_head();
    while (auto oid = walker.next())
    {
        auto commit = repo.lookup_commit(*oid);
        auto time = commit.time();
    }
}

int main(int argc, char **argv)
{
    auto cs = collect_info(".");
}