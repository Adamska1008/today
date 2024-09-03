#include "revwalk.hpp"

namespace libgit2pp
{
    revwalk::revwalk(repository &repo)
    {
        if (git_revwalk_new(&_walker, repo._repo))
        {
            throw git_error();
        }
    }

    revwalk::~revwalk()
    {
        if (_walker)
        {
            git_revwalk_free(_walker);
        }
    };

    std::optional<oid> revwalk::next()
    {
        oid oid;
        int error = git_revwalk_next(&oid._oid, _walker);
        if (error == GIT_ITEROVER)
        {
            return std::nullopt;
        }
        else if (error)
        { // should never execute - defensive style
            throw git_error();
        }
        return oid;
    };

    void revwalk::push_head()
    {
        if (git_revwalk_push_head(_walker))
        {
            throw git_error();
        }
    }
}