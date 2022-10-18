#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#include "../helper.h"
#include "absl/strings/numbers.h"
#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s file {r<length>|w<string>|s<offset>}...\n", argv[0]);
        return 0;
    }

    int fd = helper::OpenFile(argv[1], O_CREAT | O_RDWR, RWRWRW);

    char buf[BUF_SIZE];
    int readn = 0;
    int totalread = 0;
    ssize_t nread = 0;
    off_t offset = 0;
    size_t single_read = 0;
    const char *write_buf = nullptr;
    ssize_t write_buf_len = 0;
    off_t cur_pos = 0;

    for (int i = 2; i < argc; ++i) {
        switch (argv[i][0]) {
        case 'r':
            if (!absl::SimpleAtoi(argv[i] + 1, &readn)) {
                spdlog::warn("invalid offset in {}th arg(\"{}\"), read nothing",
                             i + 1, argv[i] + 1);
                continue;
            }
            totalread = 0;
            nread = 0;
            single_read = std::min(readn, BUF_SIZE);
            while (totalread < readn &&
                   (nread = read(fd, buf, single_read)) > 0) {
                helper::HexOutput(buf, nread);
                totalread += nread;
            }
            if (nread == -1) {
                helper::ErrExit("failed to read from file");
            } else if (nread == 0) {
                spdlog::info("eof after read {} bytes: from offset {}", totalread, lseek(fd, 0, SEEK_CUR));
            }
            break;

        case 'w':
            write_buf = argv[i] + 1;
            write_buf_len = strlen(write_buf);
            if (write(fd, write_buf, write_buf_len) != write_buf_len) {
                helper::ErrExit("failed to write whole buffer");
            }
            printf("%s: wrote %ld bytes\n", argv[i], write_buf_len);
            break;

        case 's':
            if (!absl::SimpleAtoi(argv[i] + 1, &offset)) {
                spdlog::warn("invalid offset in {}th arg(\"{}\"), seek 0",
                             i + 1, argv[i] + 1);
                continue;
            }
            cur_pos = lseek(fd, offset, SEEK_CUR);
            printf("seek to %ld\n", cur_pos);
            break;
        }
    }

    return 0;
}