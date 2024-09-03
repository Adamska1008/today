#include "error.hpp"
#include "signature.hpp"

namespace libgit2pp
{
    signature::signature(git_signature const *sig)
    {
        if (git_signature_dup(&_signature, sig))
        {
            throw git_error();
        }
    }
}