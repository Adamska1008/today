#include "tree.hpp"
#include "error.hpp"

namespace libgit2pp
{
    tree::tree(git_tree *other)
    {
        if (git_tree_dup(&_tree, other))
        {
            throw git_error();
        }
    }

    tree::tree(const tree &other)
        : tree(other._tree)
    {
    }

    tree &tree::operator=(const tree &other)
    {
        if (this != &other)
        {
            if (_tree)
            {
                git_tree_free(_tree);
            }
            if (git_tree_dup(&_tree, other._tree))
            {
                throw git_error();
            }
        }
        return *this;
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