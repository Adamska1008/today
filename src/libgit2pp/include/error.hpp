#pragma once
#include <exception>
#include <string_view>
#include <optional>
#include <git2/errors.h>

namespace libgit2pp
{
    class git_error : public std::exception
    {
    private:
        std::string_view _message;

    public:
        git_error()
        {
            auto error = git_error_last();
            _message = error ? error->message : "incorrectly calls git_error()";
        }
        virtual ~git_error() noexcept = default;
        virtual const char *what() const noexcept { return _message.data(); }
    };
}
