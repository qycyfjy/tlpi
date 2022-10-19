#include <unistd.h>

#include "../helper.h"

int main(int argc, char *argv[]) {
    int fd = helper::OpenFile(argv[1], O_WRONLY|O_APPEND);
    lseek(fd, 0, SEEK_SET);
    write(fd, "ok", 2);
}