#include <cstring>
#include <ctime>
#include <iostream>
#include <stdint.h>

#include "LargeMessage.h"


int main(int argc, char** argv) {
    int loop_count = 1000;
    std::cout << "Loop " << loop_count << "M. Produce a LargeMessage_Struct. Copy message. Consume message."  << std::endl;
    loop_count *= 1000 * 1000;

    LargeMessage_Struct msg;
    LargeMessage_Struct msg2;
    for (size_t i = 0; i < sizeof(msg.baz); i++)
    {
        msg.baz[i] = (char)i;
    }

    timespec start;
    clock_gettime(CLOCK_REALTIME, &start);
    uint32_t start_sec  = start.tv_sec;
    uint32_t start_nsec = start.tv_nsec;
    std::cout << "Starting loop at " << start_sec << "." << start_nsec << std::endl;

    for (int i = 0; i < loop_count; i++)
    {
        // produce
        msg.baz[i % sizeof(msg.baz)] = (char)i;

        // really slow 6s for 10K
        msg2 = msg;

        // fast (!)
        //memcpy(&msg2, &msg, sizeof(msg));

        // consume
        //if (msg.foo != i) return 1;
        //if (msg.bar != i % 2) return 1;
    }

    timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    uint32_t end_sec  = end.tv_sec;
    uint32_t end_nsec = end.tv_nsec;
    std::cout << "Ending loop at " << end_sec << "." << end_nsec << std::endl;

    std::cout << "msg2.baz[42] " << msg2.baz[42] << std::endl;

    return 0;
}
