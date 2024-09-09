#include <git2/commit.h>
#include "commit.hpp"
#include "error.hpp"
#include "tree.hpp"
#include "repository.hpp"

namespace libgit2pp
{
    commit::~commit()
    {
        if (_commit)
        {
            git_commit_free(_commit);
        }
    }

    commit::commit(git_commit *cmt)
        : _commit(cmt)
    {
    }

    oid commit::id() const
    {
        return git_commit_id(_commit);
    }

    std::string_view commit::message() const
    {
        return git_commit_message(_commit);
    }

    signature commit::committer() const
    {
        return git_commit_committer(_commit);
    }

    signature commit::author() const
    {
        return git_commit_author(_commit);
    }

    std::chrono::time_point<std::chrono::system_clock> commit::time() const
    {
        return std::chrono::system_clock::from_time_t(git_commit_time(_commit));
    }

    std::size_t commit::parentcount()
    {
        return git_commit_parentcount(_commit);
    }

    commit commit::parent() const
    {
        git_commit *parent_commit = nullptr;
        if (git_commit_parent(&parent_commit, _commit, 0))
        {
            throw git_error();
        }
        return parent_commit;
    }

    tree commit::commit_tree() const
    {
        tree out;
        if (git_commit_tree(&out._tree, _commit))
        {
            throw git_error();
        }
        return out;
    }

    diff commit::diff_from_parent(const repository &repo) const
    {
        auto par = parent();
        auto ct = commit_tree();
        auto pt = par.commit_tree();
        auto dif = ct.diff_tree(pt, repo);
        return dif;
    }
}