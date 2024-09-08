#include "tree.hpp"
#include "error.hpp"

namespace libgit2pp
{
    tree::tree(git_tree *t)
        : _tree(t)
    {
    }
}