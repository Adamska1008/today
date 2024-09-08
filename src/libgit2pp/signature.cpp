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

    std::string_view signature::name()
    {
        return _signature->name;
    }

    std::string_view signature::email()
    {
        return _signature->email;
    }

    std::chrono::time_point<std::chrono::system_clock> signature::when()
    {
        return std::chrono::system_clock::from_time_t(_signature->when.time);
    }
}