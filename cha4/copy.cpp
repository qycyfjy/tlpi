#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "../helper.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

constexpr int RWRWRW =
    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

int main(int argc, char *argv[]) {
    spdlog::set_pattern("%v");
    if (argc != 3) {
        printf("Usage: %s source dest\n", argv[0]);
        return 0;
    }

    int srcfd = open(argv[1], O_RDONLY);
    if (srcfd < 0) {
        helper::ErrExit("failed to open file: {}", argv[1]);
    }
    int destfd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, RWRWRW);
    if (destfd < 0) {
        spdlog::error("failed to open {}: {}", argv[2], strerror(errno));
        return -1;
    }

    char buf[BUF_SIZE];

    ssize_t nread = 0;
    while ((nread = read(srcfd, buf, BUF_SIZE)) > 0) {
        if (write(destfd, buf, nread) != nread) {
            spdlog::error("failed to write while buffer: {}", strerror(errno));
            return -1;
        }
    }

    if (nread < 0) {
        spdlog::error("failed to read src file: {}", strerror(errno));
        return -1;
    }

    if (close(srcfd) < 0) {
        spdlog::error("failed to close src file: {}", strerror(errno));
        return -1;
    }
    if (close(destfd) < 0) {
        spdlog::error("failed to close dest file: {}", strerror(errno));
        return -1;
    }

    return 0;
}