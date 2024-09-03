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
        return oid(_oid);
    }

    commit repository::lookup_commit(oid &oid)
    {
        commit commit;
        if (git_commit_lookup(&commit._commit, _repo, &oid._oid))
        {
            throw git_error();
        }
        return commit;
    }
}
