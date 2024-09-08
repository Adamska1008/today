#pragma once
#include <git2/commit.h>
#include "git_object.hpp"
#include "oid.hpp"
#include "signature.hpp"

namespace libgit2pp
{
    // defined in tree.hpp
    class tree;

    class commit : public git_object
    {
        friend class repository;
        friend class tree;

    private:
        git_commit *_commit;

    public:
        commit() : _commit(nullptr) {}
        commit(git_commit *);
        ~commit();
        oid id() const;
        std::string_view message();
        // wraps git_commit_committer
        signature committer();
        // wraps git_commit_author
        signature author();
        // wraps git_commit_time
        std::chrono::time_point<std::chrono::system_clock> time();
        // wraps git_commit_parentcount
        std::size_t parentcount();
        // wraps git_commit_parent
        commit parent();
        // wraps git_commit_tree
        tree commit_tree();
    };
}
