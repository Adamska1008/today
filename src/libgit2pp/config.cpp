#include "config.hpp"
#include "error.hpp"
#include "repository.hpp"

namespace libgit2pp
{
    std::string config_snapshot::get_string(std::string_view name)
    {
        const char *out = nullptr;
        if (git_config_get_string(&out, _snapshot, name.data()))
        {
            throw git_error();
        }
        return out;
    }

    config::~config()
    {
        if (_config)
        {
            git_config_free(_config);
        }
    }

    config::config(config &&other)
        : _config(other._config)
    {
        other._config = nullptr;
    }

    config &config::operator=(config &&other)
    {
        if (this != &other)
        {
            if (_config)
            {
                git_config_free(_config);
            }
            _config = other._config;
            other._config = nullptr;
        }
        return *this;
    }

    config config::open_default()
    {
        config cfg;
        if (git_config_open_default(&cfg._config))
        {
            throw git_error();
        }
        return cfg;
    }

    config config::open_global(config &cfg)
    {
        config out;
        if (git_config_open_global(&out._config, cfg._config))
        {
            throw git_error();
        }
        return out;
    }
}