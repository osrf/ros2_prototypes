#include <iostream>
#include <rosmsg_benchmark/SmallMessage.h>
#include <rosmsg_benchmark/LargeMessage.h>
#include <sstream>
#include <fstream>
#include <string>


using namespace rosmsg_benchmark;
namespace ser = ros::serialization;

template <typename M>
void serialize(long loop_count, M& msg) {
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
}

int main(void) {
    long loop_count = 1000000000;

    SmallMessage small_msg;
    small_msg.foo = 42;
    small_msg.bar = true;

    std::cout << "Serializing " << loop_count <<
        " small messages with ROSMsg (OStream)" << std::endl;
    serialize<SmallMessage>(loop_count, small_msg);

    LargeMessage large_msg;
    std::ifstream ifs("image.bmp");
    large_msg.baz = std::string((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));

    std::cout << "Serializing " << loop_count <<
        " large messages with ROSMsg (OStream)" << std::endl;
    serialize<LargeMessage>(loop_count, large_msg);

    return 0;
}
