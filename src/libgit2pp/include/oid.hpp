#pragma once
#include <string>
#include <git2/oid.h>
#include "git_object.hpp"

namespace libgit2pp
{
    class oid : public git_object
    {
        friend class repository;
        friend class revwalk;

    private:
        git_oid _oid;

    public:
        oid() = default;
        oid(const git_oid *oid) { _oid = *oid; };
        oid(const git_oid &oid) { _oid = oid; };
        // wraps git_oid_tostr
        std::string to_str();
    };
}
