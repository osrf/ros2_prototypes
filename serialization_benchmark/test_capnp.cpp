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
  explicit StringOutputStream(std::stringstream *ss_);
  KJ_DISALLOW_COPY(StringOutputStream);
  ~StringOutputStream() noexcept(false);

  void write(const void* buffer, size_t size) override;

private:
  std::stringstream *ss;
};

StringOutputStream::StringOutputStream(std::stringstream *ss_): ss(ss_) {}
StringOutputStream::~StringOutputStream() noexcept(false) {}

void StringOutputStream::write(const void* src, size_t size) {
    ss->write(static_cast<const char*>(src), size);
}


int main(void) {
    long loop_count = 1000000000;

    std::cout << "Loop count: " << loop_count << std::endl;

    ::capnp::MallocMessageBuilder message;

    SmallMessage::Builder msg = message.initRoot<SmallMessage>();

    msg.setFoo(42);
    msg.setBar(true);

    struct timeval start, end;

    gettimeofday(&start, NULL);

    unsigned char scratch[14096];
    std::stringstream ss;

    StringOutputStream sos(&ss);

    for(long i = 0; i < loop_count; ++i) {
        ss.str(std::string());
        ss.clear();
        writeMessage(sos, message);
    }

    gettimeofday(&end, NULL);

    uint64_t time = (end.tv_sec * (unsigned int)1e6 + end.tv_usec) -
        (start.tv_sec * (unsigned int)1e6 + start.tv_usec);

    std::cout << "Time (microseconds): " << time << std::endl;
    return 0;
}
