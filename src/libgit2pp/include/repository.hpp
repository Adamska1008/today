#pragma once
#include <string_view>
#include <git2/repository.h>
#include "git_object.hpp"
#include "oid.hpp"
#include "commit.hpp"
#include "config.hpp"

namespace libgit2pp
{
    class repository : public git_object
    {
        friend class revwalk;
        friend class tree;

    private:
        git_repository *_repo;

    public:
        /* Constructor */
        repository() : _repo(nullptr) {}
        repository(const repository &) = delete;
        repository(repository &&);

        /* Assignement */
        repository &operator=(const repository &) = delete;
        repository &operator=(repository &&);

        ~repository();
        // wraps git_repository_open()
        static repository open(std::string_view path);
        // wraps git_reference_name_to_id
        oid reference_name_to_id(std::string_view name);
        // wraps git_commit_lookup
        commit lookup_commit(const oid &oid);
        // get head commit
        commit head_commit();
        // wraps git_repository_config
        config repo_config();
        // wraps git_repository_config_snapshot
        config_snapshot repo_config_snapshot();
    };
}
