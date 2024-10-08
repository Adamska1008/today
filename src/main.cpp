#include <iostream>
#include <vector>
#include <fmt/core.h>
#include <chrono>
#include <tabulate/table.hpp>
#include "date/date.h"
#include "spdlog/spdlog.h"
#include "cxxopts.hpp"
#include "repository.hpp"
#include "revwalk.hpp"
#include "diff.hpp"
#include "tui.hpp"
#include "config.hpp"

using namespace libgit2pp;

bool is_today(std::chrono::system_clock::time_point tp)
{
    auto today = date::floor<date::days>(std::chrono::system_clock::now());
    auto tp_day = date::floor<date::days>(tp);
    return today == tp_day;
}

bool at_day(std::chrono::system_clock::time_point tp, date::sys_days d)
{
    auto tp_day = date::floor<date::days>(tp);
    return tp_day == d;
}

date::sys_days today()
{
    auto now = std::chrono::system_clock::now();
    return date::floor<date::days>(now);
}

std::vector<t_commit_info> collect_info(std::string_view directory, date::sys_days d, std::optional<std::string> opt_author)
{
    std::vector<t_commit_info> result;
    auto repo = repository::open(directory);
    auto cfg_snapshot = repo.repo_config_snapshot();
    std::string author;
    if (opt_author)
    {
        author = *opt_author;
    }
    else
    {
        author = cfg_snapshot.get_string("user.name");
    }
    spdlog::debug("setting author: {}", author);
    auto walker = revwalk(repo);
    walker.push_head();
    while (auto oid = walker.next())
    {
        auto commit = repo.lookup_commit(*oid);
        if (commit.author().name() != author)
        {
            continue;
        }
        if (auto time = commit.time(); at_day(time, d))
        {
            result.push_back(t_commit_info::from(commit, repo));
        }
    }
    spdlog::debug("commit size: {}", result.size());
    return result;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif
    cxxopts::Options options("today", "Use today to review what you accomplished today!");
    options.add_options()("o,offset", "Offset from today", cxxopts::value<int>()->default_value("0"))("d,directory", "The working directory to be check", cxxopts::value<std::string>()->default_value("."))("a,author", "Who's commits that will be checked", cxxopts::value<std::string>())("h,help", "Print usage")("v,version", "Print version");

    auto result = options.parse(argc, argv);
    if (result.count("help"))
    {
        fmt::println("{}", options.help());
        return 0;
    }
    if (result.count("version"))
    {
#ifdef PROJECT_VERSION 
        fmt::println("{}", PROJECT_VERSION);
        return 0;
#else
        fmt::println("exit for undefined version");
#endif
    }
    auto offset = result["offset"].as<int>();
    auto dir = result["directory"].as<std::string>();
    std::optional<std::string> opt_author;
    if (result.count("author"))
    {
        opt_author = result["author"].as<std::string>();
    }
    spdlog::debug("offset: {}", offset);

    auto cs = collect_info(dir, today() + date::days(offset), opt_author);
    print_commits_info(cs);
}