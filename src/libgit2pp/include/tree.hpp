#pragma once
#include <git2/tree.h>
#include "git_object.hpp"
#include "diff.hpp"
#include "commit.hpp"

namespace libgit2pp
{
    class tree : public git_object
    {
    private:
        git_tree *_tree;

        tree(git_tree *);

    public:
        diff diff_tree(tree &);
    };
}