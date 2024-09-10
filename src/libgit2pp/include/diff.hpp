#pragma once
#include <git2/diff.h>
#include "git_object.hpp"
#include "repository.hpp"

namespace libgit2pp
{
    class diff : public git_object
    {
        friend class tree;

    private:
        git_diff *_diff;
        git_diff_stats *_stats;
        diff() noexcept : _diff(nullptr) {}
        void update_stats();
        diff(git_diff *_diff) noexcept;

    public:
        /* Constructor */
        diff(diff &&) noexcept;
        diff(const diff &) = delete;

        ~diff();

        /* Assignment */
        diff &operator=(const diff &) = delete;
        diff &operator=(diff &&) noexcept;

        std::size_t stats_files_changed();
        std::size_t stats_insertions();
        std::size_t stats_deletions();
    };
}