# libgit2pp implement

**libgit2pp** is a modern C++ binding of libgit2. The core concept ofor libgit2pp is

+ use RAII to manage lifetime of all `git_***` pointers and avoid explicitly call `***_free`.
+ provide enhanced api.

## Memory mangement

Implement the binding is tougher than I thought. First thing is the memory management. For example, most of git object is on heap, so I must overload copy constructor and operator=. And `git_oid` is an exception, it's on the stack with a pointer to char inside. `git_diff`, despite being on heap, do not provide copy funtion because it's not recommended, so I just delete the copy and =, using move semantics instead so that the `diff` object won't call `git_diff_free()` when the pointer is null. It runs like this:

```C++
diff &diff::operator=(diff &&other)
{
    if (this != &other)
    {
        git_diff_free(_diff);
        _diff = other._diff;
        other._diff = nullptr;
    }
    return *this;
}
```

Well, `cppgit2` doesn't seems to handle it.

## `object` class

`object` class uses RAII to ensure that git is correctly initialized and shutdown. Each git object is inherited from `object`. When one of the `object` is created, it checks the `static REF_COUNT` and increase it. If `REF_COUNT == 0`, it means git has not been inited yet. Similarly, when the object is dropped, it checks the `REF_COUNT` to decided whether to shutdown git, and decrease it anyway.
