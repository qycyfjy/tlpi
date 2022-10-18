#ifndef HELPER_H_
#define HELPER_H_

#include <cerrno>
#include <cstddef>
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

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

constexpr int RWRWRW =
    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

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

int OpenFile(const char* fname, int flags, int mode=0600);

void HexOutput(const char* data, long len);
} // namespace helper

#endif