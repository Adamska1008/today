#include "tree.hpp"
#include "error.hpp"

namespace libgit2pp
{
    tree::tree(git_tree *t)
        : _tree(t)
    {
    }

    diff tree::diff_tree(tree &parent, const repository &repo)
    {
        diff d;
        if (git_diff_tree_to_tree(&d._diff, repo._repo, parent._tree, _tree, nullptr))
        {
            throw git_error();
        }
        d.update_stats();
        return d;
    }
}