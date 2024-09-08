#pragma once
#include <git2/tree.h>
#include "git_object.hpp"
#include "diff.hpp"
#include "commit.hpp"

namespace libgit2pp
{
    class tree : public git_object
    {
        friend class commit;

    private:
        git_tree *_tree;

        tree() : _tree(nullptr) {}
        tree(git_tree *);

    public:
        diff diff_tree(tree &, repository &);
    };
}