#pragma once
#include <git2/global.h>

namespace libgit2pp
{
    class git_object
    {
    public:
        git_object() { git_libgit2_init(); };
    };
}
