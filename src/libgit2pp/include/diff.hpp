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
        diff() : _diff(nullptr) {}
        void update_stats();

    public:
        ~diff();
        diff(git_diff *_diff);
        std::size_t stats_files_changed();
        std::size_t stats_insertions();
        std::size_t stats_deletions();
    };
}