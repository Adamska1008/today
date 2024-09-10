#pragma once
#include <optional>
#include <git2/revwalk.h>
#include "git_object.hpp"
#include "repository.hpp"
#include "oid.hpp"
#include "error.hpp"

namespace libgit2pp
{
    class revwalk : public git_object
    {
    private:
        git_revwalk *_walker;

    public:
        /* Constructor */
        // wraps git_revwalk_new
        revwalk(repository &repo);
        revwalk(const revwalk &) = delete;
        revwalk &operator=(const revwalk &) = delete;
        ~revwalk();
        // wraps git_revwalk_next
        std::optional<oid> next();
        // wraps git_revwalk_push_head
        void push_head();
    };
}