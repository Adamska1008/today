# libgit2pp implement

**libgit2pp** is a modern C++ binding of libgit2. The core concept ofor libgit2pp is

+ use RAII to manage lifetime of all `git_***` pointers and avoid explicitly call `***_free`.
+ provide enhanced api.

## Memory mangement

Implementing the binding turned out to be more challenging than I thought, especially the memory management. Most of git object is allocated on heap, requiring me to overload the copy constructor and assignment operator. However there's some exceptions like `git_oid` and `git_signature`, as they resides on the stack with a pointer to char.

For objects like `git_diff`, despite being on heap, there's not provided copy funtion because of several issue like owenership. I delete the copy constructor and copy assignment, opting instead for move semantics. This ensures that the `diff` object doesn't call `git_diff_free()` since the original pointer points to null. It is implemented as:

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
