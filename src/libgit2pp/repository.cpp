#include <git2/refs.h>
#include "repository.hpp"
#include "error.hpp"

namespace libgit2pp
{
    repository::~repository()
    {
        if (_repo)
        {
            git_repository_free(_repo);
        }
    }

    repository::repository(repository &&other)
        : _repo(other._repo)
    {
        other._repo = nullptr;
    }

    repository &repository::operator=(repository &&other)
    {
        if (this != &other)
        {
            if (_repo)
            {
                git_repository_free(_repo);
            }
            _repo = other._repo;
            other._repo = nullptr;
        }
        return *this;
    }

    repository repository::open(std::string_view path)
    {
        repository repo;
        if (git_repository_open(&repo._repo, path.data()))
        {
            throw git_error();
        }
        return repo;
    }

    oid repository::reference_name_to_id(std::string_view name)
    {
        git_oid _oid;
        if (git_reference_name_to_id(&_oid, this->_repo, name.data()))
        {
            throw git_error();
        }
        return _oid;
    }

    commit repository::lookup_commit(const oid &oid)
    {
        commit commit;
        if (git_commit_lookup(&commit._commit, _repo, &oid._oid))
        {
            throw git_error();
        }
        return commit;
    }

    commit repository::head_commit()
    {
        git_oid id;
        if (git_reference_name_to_id(&id, _repo, "HEAD"))
        {
            throw git_error();
        }
        return lookup_commit(&id);
    }

    config repository::repo_config()
    {
        config cfg;
        if (git_repository_config(&cfg._config, _repo))
        {
            throw git_error();
        }
        return cfg;
    }

    config_snapshot repository::repo_config_snapshot()
    {
        config_snapshot snapshot;
        if (git_repository_config_snapshot(&snapshot._snapshot, _repo))
        {
            throw git_error();
        }
        return snapshot;
    }
}
