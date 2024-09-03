#include <git2/commit.h>
#include "commit.hpp"

namespace libgit2pp
{
    commit::~commit()
    {
        if (_commit)
        {
            git_commit_free(_commit);
        }
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
}