#include <sys/time.h>
#include <ctime>
#include <stdint.h>
#include "gen-cpp/small_message_types.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main(void) {
    long loop_count = 1000000000;
    std::cout << "Loops count: " << loop_count << std::endl; 
    boost::shared_ptr<TMemoryBuffer> transport(new TMemoryBuffer());
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

    return 0;
}
