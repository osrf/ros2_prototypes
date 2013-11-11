#include <cstring>
#include <ctime>
#include <iostream>
#include <stdint.h>

#include "SmallMessage.h"


static inline void copy_message_attributes(SmallMessage_Struct& dst, const SmallMessage_Struct& src)
{
    dst.foo = src.foo;
    dst.bar = src.bar;
}


#define MACRO_copy_message_attributes(dst, src) \
    dst.foo = src.foo; \
    dst.bar = src.bar;


int main(int argc, char** argv) {
    int loop_count = 1000;
    std::cout << "Loop " << loop_count << "M. Produce a SmallMessage_Struct. Copy message. Consume message."  << std::endl;
    loop_count *= 1000 * 1000;

    SmallMessage_Struct msg;
    msg.foo = 0;
    msg.bar = false;
    SmallMessage_Struct msg2;

    timespec start;
    clock_gettime(CLOCK_REALTIME, &start);
    uint32_t start_sec  = start.tv_sec;
    uint32_t start_nsec = start.tv_nsec;
    std::cout << "Starting loop at " << start_sec << "." << start_nsec << std::endl;

    for (int i = 0; i < loop_count; i++)
    {
        // produce
        msg.foo++;
        msg.bar = !msg.bar;

        // +6s - all mostly due to function invocation
        //msg2 = msg;
        //memcpy(&msg2, &msg, sizeof(msg));
        //msg2 = msg; // assignment operator
        //copy_message_attributes(msg2, msg);

        // +.15s
        //msg2.foo = msg.foo;
        //msg2.bar = msg.bar;
        MACRO_copy_message_attributes(msg2, msg);

        // consume
        //if (msg2.foo != i) return 1;
        //if (msg2.bar != i % 2) return 1;
    }

    timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    uint32_t end_sec  = end.tv_sec;
    uint32_t end_nsec = end.tv_nsec;
    std::cout << "Ending loop at " << end_sec << "." << end_nsec << std::endl;

    std::cout << "msg2.foo " << msg2.foo << std::endl;

    return 0;
}
