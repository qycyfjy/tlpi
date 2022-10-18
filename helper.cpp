#include "helper.h"
#include "fmt/core.h"
#include "fmt/format.h"
#include "spdlog/fmt/bundled/core.h"
#include <algorithm>
#include <fcntl.h>

namespace helper {
int OpenFile(const char *fname, int flags, int mode) {
    int fd = 0;
    if ((fd = open(fname, flags, mode)) == -1) {
        ErrExit("failed to open file: {}", fname);
    }
    return fd;
}

// TODO: 多次调用的输出连续, 可能的函数签名: HexOutput(const char *data, long len, bool more = false, long cur_pos = 0);
void HexOutput(const char *data, long len) {
    fmt::print("{:^10} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} "
               "{:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} {:02X} \n",
               "Offset", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    int idx = 0;
    while (len > 0) {
        auto nbyte = std::min(16l, len);
        auto start = data + idx * 16;
        fmt::print("{:010X} ", idx);
        for(int i = 0; i < nbyte; ++i) {
            fmt::print("{:02X} ", start[i]);
        }
        fmt::print("\n");
        idx += 1;
        len -= 16;
    }
}
} // namespace helper