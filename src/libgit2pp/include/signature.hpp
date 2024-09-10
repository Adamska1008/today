#pragma once
#include <chrono>
#include <git2/signature.h>
#include "git_object.hpp"

namespace libgit2pp
{
    class signature
    {
        friend class commit;

    private:
        git_signature *_signature;
        signature(const git_signature *);

    public:
        /* Constructor */
        signature() noexcept : _signature(nullptr) {}
        signature(const signature &);
        signature &operator=(const signature &);
        
        // wraps git_signature.name
        std::string_view name();
        // wraps git_signature.email
        std::string_view email();
        // wraps git_signature.when
        std::chrono::time_point<std::chrono::system_clock> when();
    };
}