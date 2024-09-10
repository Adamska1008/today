#include "error.hpp"
#include "signature.hpp"

namespace libgit2pp
{
    signature::signature(const git_signature *sig)
    {
        if (git_signature_dup(&_signature, sig))
        {
            throw git_error();
        }
    }

    signature::signature(const signature &other)
        : signature(other._signature)
    {
    }

    signature &signature::operator=(const signature &other)
    {
        if (this != &other)
        {
            if (git_signature_dup(&_signature, other._signature))
            {
                throw git_error();
            }
        }
        return *this;
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