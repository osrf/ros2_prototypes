#include <sys/time.h>
#include <ctime>
#include <stdint.h>
#include "protocpp/small_message.pb.h"
#include <iostream>
#include <sstream>

int main(void) {
    long loop_count = 1000000000;
    std::cout << "Serializing " << loop_count <<
        " messages with Protobuf (stringstream)" << std::endl;
    std::stringstream ss;
    SmallMessage msg;
    msg.set_foo(42);
    msg.set_bar(true);

    struct timeval start, end;

    gettimeofday(&start, NULL);

    for(long i = 0; i < loop_count; ++i) {
        ss.str(std::string());
        ss.clear();
        msg.SerializeToOstream(&ss);
    }

    gettimeofday(&end, NULL);

    uint64_t time = (end.tv_sec * (unsigned int)1e6 + end.tv_usec) -
        (start.tv_sec * (unsigned int)1e6 + start.tv_usec);

    std::cout << "Time (microseconds): " << time << std::endl;

    return 0;
}
