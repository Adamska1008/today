#pragma once
#include <git2/commit.h>
#include "git_object.hpp"
#include "oid.hpp"
#include "signature.hpp"

namespace libgit2pp
{
    class commit : public git_object
    {
        friend class repository;

    private:
        git_commit *_commit;

    public:
        commit() : _commit(nullptr) {}
        ~commit();
        oid id() const;
        std::string_view message();
        signature committer();
    };
}
