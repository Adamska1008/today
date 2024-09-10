#include <iostream>
#include <vector>
#include <fmt/core.h>
#include <chrono>
#include <tabulate/table.hpp>
#include "date/date.h"
#include "spdlog/spdlog.h"
#include "repository.hpp"
#include "revwalk.hpp"
#include "diff.hpp"

using namespace libgit2pp;

struct commit_info
{
    std::string author;
    std::string message;
    std::chrono::time_point<std::chrono::system_clock> time;
    int lines_added;
    int lines_removed;
    int files_changed;

    static commit_info from(const commit &cmt, const repository &repo)
    {
        commit_info info;
        info.author = cmt.author().name();
        info.message = cmt.message();
        info.time = cmt.time();
        auto dif = cmt.diff_from_parent(repo);
        info.lines_added = dif.stats_insertions();
        info.lines_removed = dif.stats_deletions();
        info.files_changed = dif.stats_files_changed();
        return info;
    }
};

bool is_today(std::chrono::system_clock::time_point tp)
{
    auto today = date::floor<date::days>(std::chrono::system_clock::now());
    auto tp_day = date::floor<date::days>(tp);
    return today == tp_day;
}

bool is_day(std::chrono::system_clock::time_point tp, date::sys_days d)
{
    auto tp_day = date::floor<date::days>(tp);
    return tp_day == d;
}

date::sys_days today()
{
    auto now = std::chrono::system_clock::now();
    return date::floor<date::days>(now);
}

std::vector<commit_info> collect_info(std::string_view directory, date::sys_days d)
{
    std::vector<commit_info> result;
    auto repo = repository::open(directory);
    auto walker = revwalk(repo);
    walker.push_head();
    while (auto oid = walker.next())
    {

        auto commit = repo.lookup_commit(*oid);
        auto time = commit.time();
        if (is_day(time, d))
        {
            result.push_back(commit_info::from(commit, repo));
        }
    }
    return result;
}

void print_commits_info(const std::vector<commit_info> &infos)
{
    using namespace tabulate;
    Table table;
    // Header
    table.add_row({"Author", "Message", "Time", "Lines Added", "Lines Removed", "Files Changed"});
    for (const auto &info : infos)
    {
        auto time_str = date::format("%T", info.time);
        table.add_row({info.author, info.message, time_str,
                       std::to_string(info.lines_added),
                       std::to_string(info.lines_removed),
                       std::to_string(info.files_changed)});
    }
    table.format().border_top("=").border_bottom("=").border_left("|").border_right("|");
    std::cout << table << std::endl;
}

int main()
{
    spdlog::set_level(spdlog::level::debug);
    auto cs = collect_info(".", today());
    print_commits_info(cs);
}