#include "oid.hpp"

namespace libgit2pp
{
    std::string oid::to_str()
    {
        std::string oid_str(GIT_OID_HEXSZ, '\0');
        git_oid_tostr(oid_str.data(), GIT_OID_HEXSZ, &_oid);
        return oid_str;
    }
}
