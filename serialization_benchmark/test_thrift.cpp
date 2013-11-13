#include <sys/time.h>
#include <ctime>
#include <stdint.h>
#include "gen-cpp/small_message_types.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <sstream>

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


template <typename T>
void serialize(long loop_count) {
    boost::shared_ptr<T> transport(new T());
    TBinaryProtocol oprot(transport);
    transport->open();
    SmallMessage msg;
    msg.foo = 42;
    msg.bar = true;
 
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
    std::cout << "Serializing " << loop_count <<
        " messages with Thrift (stringstream)" << std::endl;
    serialize<TStringStream>(loop_count);

    std::cout << "Serializing " << loop_count <<
        " messages with Thrift (TMemoryBuffer)" << std::endl;
    serialize<TMemoryBuffer>(loop_count);

    return 0;
}
