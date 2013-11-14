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
#include <kj/io.h>
#include <kj/common.h>
#include <kj/array.h>
#include <kj/debug.h>
#include <fstream>
#include <string>


using namespace kj;

class StringOutputStream: public OutputStream {
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


class MemoryOutputStream: public BufferedOutputStream {
  public:
    explicit MemoryOutputStream() {
        // Allocate a huge memory buffer (3MB), needed for the large message test
        buffer = new byte[3145728];
        array = ArrayPtr<byte>(buffer, 3145728);
        fillPos = array.begin();
    }

    KJ_DISALLOW_COPY(MemoryOutputStream);
    ~MemoryOutputStream() noexcept(false) {
        delete[] buffer;
    }
 
    ArrayPtr<byte> getArray() {
      // Get the portion of the array which has been filled in.
      return arrayPtr(array.begin(), fillPos);
    }
 
    // implements BufferedInputStream ----------------------------------
    ArrayPtr<byte> getWriteBuffer() override {
      return arrayPtr(fillPos, array.end());
    }
 
    void write(const void* src, size_t size) override {
      if (src == fillPos) {
        fillPos += size;
      } else {
        KJ_REQUIRE(size <= (size_t)(array.end() - fillPos),
              "MemoryOutputStream's backing array was not large enough for the data written.");
        memcpy(fillPos, src, size);
        fillPos += size;
      }
    }

    void reset() {
        fillPos = array.begin();
    }

  private:
    ArrayPtr<byte> array;
    byte* fillPos;
    byte* buffer;
};

template <typename T, typename M>
void serialize(long loop_count, M& msg, ::capnp::MallocMessageBuilder& message) {
    struct timeval start, end;

    gettimeofday(&start, NULL);

    T sos;

    for(long i = 0; i < loop_count; ++i) {
        sos.reset();
        writeMessage(sos, message);
    }

    gettimeofday(&end, NULL);

    uint64_t time = (end.tv_sec * (unsigned int)1e6 + end.tv_usec) -
        (start.tv_sec * (unsigned int)1e6 + start.tv_usec);

    std::cout << "Time (microseconds): " << time << std::endl;
}

int main(void) {
    long loop_count = 1000000000;

    ::capnp::MallocMessageBuilder message1;

    SmallMessage::Builder small_msg = message1.initRoot<SmallMessage>();

    small_msg.setFoo(42);
    small_msg.setBar(true);

    std::cout << "Serializing " << loop_count <<
        " small messages with Cap'n'proto (stringstream)" << std::endl;
    serialize<StringOutputStream, SmallMessage::Builder>(loop_count, small_msg, message1);

    std::cout << "Serializing " << loop_count <<
        " small messages with Cap'n'proto (MemoryStream)" << std::endl;
    serialize<MemoryOutputStream, SmallMessage::Builder>(loop_count, small_msg, message1);

    ::capnp::MallocMessageBuilder message2;

    LargeMessage::Builder large_msg = message2.initRoot<LargeMessage>();
    std::ifstream ifs("image.bmp");
    std::string content((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));
    const byte *data = reinterpret_cast<const byte *>(content.c_str());
    large_msg.setBaz(::capnp::Data::Reader(data, content.length()));

    std::cout << "Serializing " << loop_count <<
        " large messages with Cap'n'proto (stringstream)" << std::endl;
    serialize<StringOutputStream, LargeMessage::Builder>(loop_count, large_msg, message2);

    std::cout << "Serializing " << loop_count <<
        " large messages with Cap'n'proto (MemoryStream)" << std::endl;
    serialize<MemoryOutputStream, LargeMessage::Builder>(loop_count, large_msg, message2);


    return 0;
}
