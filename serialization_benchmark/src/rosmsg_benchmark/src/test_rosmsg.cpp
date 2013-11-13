#include <iostream>
#include <rosmsg_benchmark/SmallMessage.h>
#include <sstream>

using namespace rosmsg_benchmark;
namespace ser = ros::serialization;

int main(void) {
    SmallMessage msg;
    msg.foo = 42;
    msg.bar = true;

    long loop_count = 1000000000;
    std::cout << "Serializing " << loop_count <<
        " messages with ROSMsg (OStream)" << std::endl;

    uint32_t serial_size = ros::serialization::serializationLength(msg);

    struct timeval start, end;

    gettimeofday(&start, NULL);

    for(long i = 0; i < loop_count; ++i) {
        boost::shared_array<uint8_t> buffer(new uint8_t[serial_size]);
        ser::OStream stream(buffer.get(), serial_size);
        ser::serialize(stream, msg);
    }

    gettimeofday(&end, NULL);

    uint64_t time = (end.tv_sec * (unsigned int)1e6 + end.tv_usec) -
        (start.tv_sec * (unsigned int)1e6 + start.tv_usec);

    std::cout << "Time (microseconds): " << time << std::endl;
   
    return 0;
}
