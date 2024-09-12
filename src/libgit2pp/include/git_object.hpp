#pragma once
#include <git2/global.h>
#include <spdlog/spdlog.h>

namespace libgit2pp
{
    class git_object
    {
    public:
        git_object()
        {
            git_libgit2_init();
        }
        virtual ~git_object()
        {
            git_libgit2_shutdown();
        }
    };
}
