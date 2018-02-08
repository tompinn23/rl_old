#ifndef FS_H
#define FS_H
#include "config.h"

#if defined(HAVE_FS_H)
#include <filesystem>
#elif defined(HAVE_FS_EXP_H)
#include <experimental/filesystem>
#else
#error Filesystem requried.
#endif

#if defined(FS_STD)
namespace fs = std::filesystem;
#elif defined(FS_EXP)
namespace fs = std::experimental::filesystem;
#endif

#endif
