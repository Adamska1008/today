cmake_minimum_required(VERSION 3.22)

project(today
        VERSION 0.1.0)

# set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

find_package(PkgConfig)
if (PkgConfig_FOUND)
    PKG_CHECK_MODULES(LIBGIT2 libgit2>=0.99)
endif()

set(SPDLOG_FMT_EXTERNAL on)
set(BUILD_TZ_LIB ON CACHE BOOL "build/install of TZ library")
# tz databse
set(USE_SYSTEM_TZ_DB ON CACHE BOOL "use system date-zone DB")

add_subdirectory(deps)
add_subdirectory(src)

# Install
install(TARGETS today
        RUNTIME DESTINATION bin
        COMPONENT binary)