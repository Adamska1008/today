#pragma once
#include <git2/commit.h>
#include "git_object.hpp"
#include "oid.hpp"
#include "signature.hpp"

namespace libgit2pp
{
    // defined in tree.hpp
    class tree;
    // defined in diff.hpp
    class diff;
    // defined in repository
    class repository;

    class commit : public git_object
    {
        friend class repository;
        friend class tree;

    private:
        git_commit *_commit;
        commit(git_commit *);

    public:
        /* Constructor */
        commit() noexcept : _commit(nullptr) {}
        commit(const commit &);
        /* Destructor */
        ~commit();

        oid id() const noexcept;
        std::string_view message() const noexcept;
        // wraps git_commit_committer
        signature committer() const noexcept;
        // wraps git_commit_author
        signature author() const noexcept;
        // wraps git_commit_time
        std::chrono::time_point<std::chrono::system_clock> time() const noexcept;
        // wraps git_commit_parentcount
        std::size_t parentcount() const noexcept;
        // wraps git_commit_parent
        commit parent() const;
        // wraps git_commit_tree
        tree commit_tree() const;

        diff diff_from_parent(const repository &) const;
    };
}
