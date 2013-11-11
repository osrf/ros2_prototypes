#include <ctime>
#include <iostream>
#include <stdint.h>

#include "SmallMessage.h"


int main(int argc, char** argv) {
    int loop_count = 1000;
    std::cout << "Loop " << loop_count << "M. Produce a SmallMessage_Method. Consume message."  << std::endl;
    loop_count *= 1000 * 1000;

    SmallMessage_Method msg;
    msg.set_foo(0);
    msg.set_bar(false);

    timespec start;
    clock_gettime(CLOCK_REALTIME, &start);
    uint32_t start_sec  = start.tv_sec;
    uint32_t start_nsec = start.tv_nsec;
    std::cout << "Starting loop at " << start_sec << "." << start_nsec << std::endl;

    for (int i = 0; i < loop_count; i++)
    {
        // produce
        if (msg.get_bar())
        {
            msg.set_foo(msg.get_foo() + 1);
        }
        msg.set_bar(!msg.get_bar());

        // consume
        //if (msg.get_foo() != i) return 1;
        //if (msg.get_bar() != i % 2) return 1;
    }

    timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    uint32_t end_sec  = end.tv_sec;
    uint32_t end_nsec = end.tv_nsec;
    std::cout << "Ending loop at " << end_sec << "." << end_nsec << std::endl;

    std::cout << "msg.foo " << msg.get_foo() << std::endl;

    return 0;
}
