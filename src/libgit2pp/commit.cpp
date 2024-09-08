#include <git2/commit.h>
#include "commit.hpp"
#include "error.hpp"

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

    std::string_view commit::message()
    {
        return git_commit_message(_commit);
    }

    signature commit::committer()
    {
        return git_commit_committer(_commit);
    }

    signature commit::author()
    {
        return git_commit_author(_commit);
    }

    std::chrono::time_point<std::chrono::system_clock> commit::time()
    {
        return std::chrono::system_clock::from_time_t(git_commit_time(_commit));
    }

    std::size_t commit::parentcount()
    {
        return git_commit_parentcount(_commit);
    }

    commit commit::parent()
    {
        git_commit *parent_commit = nullptr;
        if (git_commit_parent(&parent_commit, _commit, 0))
        {
            throw git_error();
        }
        return parent_commit;
    }
}