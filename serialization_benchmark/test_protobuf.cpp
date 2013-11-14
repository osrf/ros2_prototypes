#include <sys/time.h>
#include <ctime>
#include <stdint.h>
#include "protocpp/small_message.pb.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


template <typename M>
void serialize(long loop_count, M& msg) {

    std::stringstream ss;

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
}


int main(void) {
    long loop_count1 = 1000000000;
    std::cout << "Serializing " << loop_count1 <<
        " small messages with Protobuf (stringstream)" << std::endl;

    SmallMessage small_msg;
    small_msg.set_foo(42);
    small_msg.set_bar(true);

    serialize<SmallMessage>(loop_count1, small_msg);

    LargeMessage large_msg;
    std::ifstream ifs("image.bmp");
    large_msg.set_baz(std::string((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())));

    long loop_count2 = 1000000;
    std::cout << "Serializing " << loop_count2 <<
        " large messages with Protobuf (stringstream)" << std::endl;

    serialize<LargeMessage>(loop_count2, large_msg);

    return 0;
}
