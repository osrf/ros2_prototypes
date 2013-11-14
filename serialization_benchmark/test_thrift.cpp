#include <sys/time.h>
#include <ctime>
#include <stdint.h>
#include "gen-cpp/small_message_types.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <sstream>
#include <string>
#include <fstream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

class TStringStream : public TTransport {
    public:
        void open () {}

        bool isOpen() {
            return true;
        }

        void resetBuffer() {
            ss.str("");
            ss.clear();
        }

        void write_virt(const uint8_t* buf, uint32_t len) {
            ss.write(reinterpret_cast<const char *>(buf), len);
        }

    private:
        std::stringstream ss;
};


template <typename T, typename M>
void serialize(long loop_count, M& msg) {
    boost::shared_ptr<T> transport(new T());
    TBinaryProtocol oprot(transport);
    transport->open();
 
    struct timeval start, end;

    gettimeofday(&start, NULL);

    for(long i = 0; i < loop_count; ++i) {
        transport->resetBuffer();
        msg.write(&oprot);
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
        " small messages with Thrift (stringstream)" << std::endl;
    serialize<TStringStream, SmallMessage>(loop_count, small_msg);

    std::cout << "Serializing " << loop_count <<
        " small messages with Thrift (TMemoryBuffer)" << std::endl;
    serialize<TMemoryBuffer, SmallMessage>(loop_count, small_msg);

    LargeMessage large_msg;
    std::ifstream ifs("image.bmp");
    large_msg.baz = std::string((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));

    std::cout << "Serializing " << loop_count <<
        " large messages with Thrift (stringstream)" << std::endl;
    serialize<TStringStream, LargeMessage>(loop_count, large_msg);

    std::cout << "Serializing " << loop_count <<
        " large messages with Thrift (TMemoryBuffer)" << std::endl;
    serialize<TMemoryBuffer, LargeMessage>(loop_count, large_msg);

    return 0;
}
