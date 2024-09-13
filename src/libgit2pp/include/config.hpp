#pragma once
#include <git2/config.h>
#include "git_object.hpp"

namespace libgit2pp
{
    class config_snapshot
    {
        friend class repository;

    private:
        git_config *_snapshot;

    public:
        config_snapshot() : _snapshot(nullptr) {}

        std::string get_string(std::string_view name);
    };

    class config : public git_object
    {
        friend class repository;

    private:
        git_config *_config;

    public:
        config() : _config(nullptr) {}
        ~config();
        config(const config &) = delete;
        config(config &&);
        // wraps git_config_open_default
        static config open_default();
        // wraps git_config_open_global
        static config open_global(config &);

        config &operator=(const config &) = delete;
        config &operator=(config &&);
    };

}