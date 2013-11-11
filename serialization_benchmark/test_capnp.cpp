#include "capnpcpp/small_message.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>

int main(void) {
    long loop_count = 1000000000;

    std::cout << "Loop count: " << loop_count << std::endl;

    ::capnp::MallocMessageBuilder message;

    SmallMessage::Builder msg = message.initRoot<SmallMessage>();

    msg.setFoo(42);
    msg.setBar(true);

    struct timeval start, end;

    gettimeofday(&start, NULL);

    shm_unlink("/capnptest");
    for(long i = 0; i < loop_count; ++i) {
        int fd = shm_open("/capnptest", (O_CREAT | O_EXCL | O_RDWR),
            (S_IREAD | S_IWRITE));
        writePackedMessageToFd(fd, message);
        close(fd);
        shm_unlink("/capnptest");
    }

    gettimeofday(&end, NULL);

    uint64_t time = (end.tv_sec * (unsigned int)1e6 + end.tv_usec) -
        (start.tv_sec * (unsigned int)1e6 + start.tv_usec);

    std::cout << "Time (microseconds): " << time << std::endl;
    return 0;
}
