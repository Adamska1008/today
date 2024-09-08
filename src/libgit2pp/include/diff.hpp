#pragma once
#include <git2/diff.h>
#include "git_object.hpp"

namespace libgit2pp
{
    class diff : public git_object
    {
    private:
        const git_diff *_diff;

    public:
        diff(const git_diff *_diff);
    };
}