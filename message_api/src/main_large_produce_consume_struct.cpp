#include <ctime>
#include <iostream>
#include <sstream>
#include <stdint.h>

#include "LargeMessage.h"


int main(int argc, char** argv) {
    int loop_count = 1000;
    std::cout << "Loop " << loop_count << "M. Produce a LargeMessage_Struct. Consume message."  << std::endl;
    loop_count *= 1000 * 1000;

    LargeMessage_Struct msg;

    //std::stringstream ss;

    timespec start;
    clock_gettime(CLOCK_REALTIME, &start);
    uint32_t start_sec  = start.tv_sec;
    uint32_t start_nsec = start.tv_nsec;
    std::cout << "Starting loop at " << start_sec << "." << start_nsec << std::endl;

    for (size_t i = 0; i < sizeof(msg.baz); i++)
    {
        msg.baz[i] = (char)i;
    }
    for (int i = 1; i < loop_count; i++)
    {
        //ss.str("");
        //ss.clear();

        // produce
        msg.baz[i % sizeof(msg.baz)] = (char)(((int)msg.baz[(i - 1) % sizeof(msg.baz)]) + (int)(msg.baz[i % sizeof(msg.baz)]));

        //ss << msg.baz;
        // consume
        //if (msg.foo != i) return 1;
        //if (msg.bar != i % 2) return 1;
    }

    timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    uint32_t end_sec  = end.tv_sec;
    uint32_t end_nsec = end.tv_nsec;
    std::cout << "Ending loop at " << end_sec << "." << end_nsec << std::endl;

    std::cout << "msg.baz[42] " << msg.baz[42] << std::endl;

    return 0;
}
