#include "error.hpp"
#include "diff.hpp"

namespace libgit2pp
{
    void diff::update_stats()
    {
        if (git_diff_get_stats(&_stats, _diff))
        {
            throw git_error();
        }
    }

    diff::diff(git_diff *d)
        : _diff(d)
    {
        update_stats();
    }
}