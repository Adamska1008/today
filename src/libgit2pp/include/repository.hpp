#pragma once
#include <string_view>
#include <git2/repository.h>
#include "git_object.hpp"
#include "oid.hpp"
#include "commit.hpp"

namespace libgit2pp
{
    class repository : public git_object
    {
        friend class revwalk;
        friend class tree;

    private:
        git_repository *_repo;

    public:
        repository() : _repo(nullptr) {}
        ~repository();
        // wraps git_repository_open()
        static repository open(std::string_view path);
        // wraps git_reference_name_to_id
        oid reference_name_to_id(std::string_view name);
        // wraps git_commit_lookup
        commit lookup_commit(const oid &oid);
        // get head commit
        commit head_commit();
    };
}
