#include "diff.hpp"

namespace libgit2pp
{
    diff::diff(const git_diff *d)
        : _diff(d)
    {
    }
}