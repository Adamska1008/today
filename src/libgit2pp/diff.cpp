#include <stdexcept>
#include "error.hpp"
#include "diff.hpp"

namespace libgit2pp
{
    void diff::update_stats()
    {
        if (!_diff)
        {
            throw std::runtime_error("git_diff not initialized");
        }
        if (git_diff_get_stats(&_stats, _diff))
        {
            throw git_error();
        }
    }

    diff::~diff()
    {
        if (_diff)
        {
            git_diff_free(_diff);
        }
    }

    diff::diff(git_diff *d) noexcept
        : _diff(d)
    {
        update_stats();
    }

    diff::diff(diff &&other) noexcept
        : _diff(other._diff)
    {
        other._diff = nullptr;
    }

    diff &diff::operator=(diff &&other) noexcept
    {
        if (this != &other)
        {
            if (_diff)
            {
                git_diff_free(_diff);
            }
            _diff = other._diff;
            other._diff = nullptr;
        }
        return *this;
    }

    std::size_t diff::stats_insertions()
    {
        if (!_stats)
        {
            update_stats();
        }
        return git_diff_stats_insertions(_stats);
    }

    std::size_t diff::stats_files_changed()
    {
        if (!_stats)
        {
            update_stats();
        }
        return git_diff_stats_files_changed(_stats);
    }

    std::size_t diff::stats_deletions()
    {
        if (!_stats)
        {
            update_stats();
        }
        return git_diff_stats_deletions(_stats);
    }
}