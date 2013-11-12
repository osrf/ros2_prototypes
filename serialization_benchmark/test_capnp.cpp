#include "capnpcpp/small_message.capnp.h"
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>


class StringOutputStream: public kj::OutputStream {
public:
  explicit StringOutputStream() {}
  KJ_DISALLOW_COPY(StringOutputStream);
  ~StringOutputStream() noexcept(false) {}

  void write(const void* buffer, size_t size) override {
    ss.write(reinterpret_cast<const char*>(buffer), size);
  }

  void reset() {
      ss.str("");
      ss.clear();
  }

private:
  std::stringstream ss;
};


int main(void) {
    long loop_count = 1000000000;

    std::cout << "Serializing " << loop_count <<
        " messages with Cap'n'proto (stringstream)" << std::endl;

    ::capnp::MallocMessageBuilder message;

    SmallMessage::Builder msg = message.initRoot<SmallMessage>();

    msg.setFoo(42);
    msg.setBar(true);

    struct timeval start, end;

    gettimeofday(&start, NULL);

    StringOutputStream sos;

    for(long i = 0; i < loop_count; ++i) {
        sos.reset();
        writeMessage(sos, message);
    }

    gettimeofday(&end, NULL);

    uint64_t time = (end.tv_sec * (unsigned int)1e6 + end.tv_usec) -
        (start.tv_sec * (unsigned int)1e6 + start.tv_usec);

    std::cout << "Time (microseconds): " << time << std::endl;
    return 0;
}
