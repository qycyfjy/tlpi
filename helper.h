#ifndef HELPER_H_
#define HELPER_H_

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <utility>

#include "ename.c"
#include "spdlog/spdlog.h"
#include "fmt/format.h"

namespace helper {
template <typename... Args>
static void outputError(bool useErr, const char *fmt, Args &&...args) {
    std::string errMsg("");
    std::string userMsg = fmt::format(fmt, std::forward<Args>(args)...);
    if (useErr) {
        int err = errno;
        errMsg = fmt::format(
            "[{} {}]: ", err >= 0 && err <= MAX_ENAME ? ename[err] : "Unknown",
            strerror(err));
    }
    spdlog::error("{}{}", errMsg, userMsg);
    exit(EXIT_FAILURE);
}

template <typename... Args> void ErrExit(const char *fmt, Args &&...args) {
    outputError(true, fmt, std::forward<Args>(args)...);
}
} // namespace helper

#endif