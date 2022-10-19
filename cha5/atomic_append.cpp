#include <fcntl.h>
#include <unistd.h>

#include "../helper.h"
#include "absl/strings/numbers.h"
#include "fmt/printf.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fmt::printf("{} filename length [x]", argv[0]);
        exit(-1);
    }
    bool append_mode = true;
    if(argc == 4 && argv[3][0] == 'x') {
        append_mode = false;
    }
    
    int open_flags = O_CREAT | O_WRONLY;
    if(append_mode) {
        open_flags |= O_APPEND;
    }
    int fd = helper::OpenFile(argv[1], open_flags);

    long total_write = 0;
    if(!absl::SimpleAtoi(argv[2], &total_write)) {
        fmt::printf("invalid length: {}", argv[2]);
        exit(-1);
    }

    for(int i = 0; i < total_write; ++i) {
        if(!append_mode) {
            lseek(fd, 0, SEEK_END);
        }
        write(fd, "a", 1);
    }

    return 0;
}