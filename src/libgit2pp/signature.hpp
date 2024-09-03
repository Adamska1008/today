#pragma once
#include <git2/signature.h>
#include "git_object.hpp"

namespace libgit2pp
{
    class signature
    {
        friend class commit;

    private:
        git_signature *_signature;
        signature(git_signature const *);

    public:
        signature() noexcept : _signature(nullptr) {}
    };
}