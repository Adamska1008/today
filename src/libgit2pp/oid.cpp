#include "error.hpp"
#include "oid.hpp"

namespace libgit2pp
{
    oid::oid(const git_oid *other)
    {
        if (git_oid_cpy(&_oid, other))
        {
            throw git_error();
        }
    }

    oid::oid(const git_oid &other)
    {
        if (git_oid_cpy(&_oid, &other))
        {
            throw git_error();
        }
    }

    oid::oid(const oid &other)
        : oid(other._oid)
    {
    }

    std::string oid::to_str()
    {
        std::string oid_str(GIT_OID_HEXSZ, '\0');
        git_oid_tostr(oid_str.data(), GIT_OID_HEXSZ, &_oid);
        return oid_str;
    }
}
