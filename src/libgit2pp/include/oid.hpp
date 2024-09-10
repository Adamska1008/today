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
        friend class commit;

    private:
        git_oid _oid;
        oid(const git_oid *other);
        oid(const git_oid &other);

    public:
        /* Constructor */
        oid() = default;
        oid(const oid &);

        // wraps git_oid_tostr
        std::string to_str();
    };
}
