#include <cstring>
#include <ctime>
#include <iostream>
#include <stdint.h>

#include "LargeMessage.h"


int main(int argc, char** argv) {
    int loop_count = 1000;
    std::cout << "Loop " << loop_count << "M. Produce a LargeBoostMessage_Method. Consume message."  << std::endl;
    loop_count *= 1000 * 1000;

    LargeBoostMessage_Method msg;
    for (size_t i = 0; i < msg.get_baz().size(); i++)
    {
        msg.get_baz()[i] = (char)i;
    }

    timespec start;
    clock_gettime(CLOCK_REALTIME, &start);
    uint32_t start_sec  = start.tv_sec;
    uint32_t start_nsec = start.tv_nsec;
    std::cout << "Starting loop at " << start_sec << "." << start_nsec << std::endl;

    for (int i = 0; i < loop_count; i++)
    {
        // produce
        msg.get_baz()[i % msg.get_baz().size()] = (char)i;

        // consume
        //if (msg.foo != i) return 1;
        //if (msg.bar != i % 2) return 1;
    }

    timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    uint32_t end_sec  = end.tv_sec;
    uint32_t end_nsec = end.tv_nsec;
    std::cout << "Ending loop at " << end_sec << "." << end_nsec << std::endl;

    std::cout << "msg.baz[42] " << msg.get_baz()[42] << std::endl;

    return 0;
}
