#pragma once
#include <git2/global.h>
#include <spdlog/spdlog.h>

namespace libgit2pp
{
    extern long long REF_COUNT;

    class git_object
    {
    public:
        git_object()
        {
            git_libgit2_init();
            spdlog::debug("Add REFCOUNT {}", ++REF_COUNT);
        }
        virtual ~git_object()
        {
            git_libgit2_shutdown();
            spdlog::debug("Reduce REFCOUNT {}", --REF_COUNT);
        }
    };
}
