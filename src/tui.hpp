#include <string>
#include <chrono>
#include "tabulate/table.hpp"
#include "date/date.h"
#include "commit.hpp"
#include "repository.hpp"

/* t_ stands for TUI */
struct t_commit_info
{
    std::string author;
    std::string message;
    std::chrono::time_point<std::chrono::system_clock> time;
    int lines_added;
    int lines_removed;
    int files_changed;

    static t_commit_info from(const libgit2pp::commit &cmt, const libgit2pp::repository &repo);
};

t_commit_info t_commit_info::from(const libgit2pp::commit &cmt, const libgit2pp::repository &repo)
{
    t_commit_info info;
    info.author = cmt.author().name();
    info.message = cmt.message();
    info.time = cmt.time();
    auto dif = cmt.diff_from_parent(repo);
    info.lines_added = dif.stats_insertions();
    info.lines_removed = dif.stats_deletions();
    info.files_changed = dif.stats_files_changed();
    return info;
}

void print_commits_info(const std::vector<t_commit_info> &infos)
{
    using namespace tabulate;
    Table table;
    // Header
    table.add_row({"Author", "Message", "Time", "Lines Added", "Lines Removed", "Files Changed"});
    std::size_t tot_added = 0;
    std::size_t tot_removed = 0;
    std::size_t tot_files = 0;
    for (const auto &info : infos)
    {
        auto time_str = date::format("%F %R", info.time);
        table.add_row({info.author, info.message, time_str,
                       std::to_string(info.lines_added),
                       std::to_string(info.lines_removed),
                       std::to_string(info.files_changed)});
        tot_added += info.lines_added;
        tot_removed = info.lines_removed;
        tot_files = info.files_changed;
    }
    table.format().border_top("=").border_bottom("=").border_left("|").border_right("|");
    fmt::println("Total: Commits {}, Lines Added {}, Lines Removed {}, Files Changed {}.", infos.size(), tot_added, tot_removed, tot_files);
    std::cout << table << std::endl; // TODO: Specialize the fmt::formatter for the specific table
}