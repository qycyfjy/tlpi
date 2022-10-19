#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

#include "spdlog/spdlog.h"
#include "../helper.h"

constexpr const char *const opt_str = ":a";

inline char printable(char c) {
    if (isprint(c)) {
        return c;
    }
    return '?';
}

void printUsageExit(const char *prog) {
    printf("%s [-a] source dest\n", prog);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printUsageExit(argv[0]);
    }

    bool append_mode = false;
    int opt;
    while ((opt = getopt(argc, argv, opt_str)) != -1) {
        switch (opt) {
        case '?':
            printf("Unrecognized option: %c\n", printable(optopt));
            printUsageExit(argv[0]);
        case 'a':
            append_mode = true;
            break;
        default:
            spdlog::critical("unexpected case");
            exit(-1);
        }
    }

    if (optind + 1 >= argc) {
        printUsageExit(argv[0]);
    }

    int src_fd = helper::OpenFile(argv[optind], O_RDONLY);
    int dest_flags = O_CREAT | O_WRONLY;
    if(append_mode) {
        dest_flags |= O_APPEND;
    } else {
        dest_flags |= O_TRUNC;
    }
    int dest_fd = helper::OpenFile(argv[optind+1], dest_flags);

    char buf[BUF_SIZE];
    ssize_t nread = 0;
    while((nread = read(src_fd, buf, BUF_SIZE)) > 0) {
        if(write(dest_fd, buf, nread) != nread) {
            helper::ErrExit("failed to write whole buffer");
        }
    }
    if(nread == -1) {
        helper::ErrExit("failed to read source file");
    }

    return 0;
}