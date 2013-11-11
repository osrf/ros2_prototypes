THRIFT_CXXFLAGS := $(shell pkg-config --cflags thrift) -O3
THRIFT_LDFLAGS := $(shell pkg-config --libs thrift)

PROTOBUF_CXXFLAGS := $(shell pkg-config --cflags protobuf) -O3
PROTOBUF_LDFLAGS := $(shell pkg-config --libs protobuf)

all: test_protobuf test_thrift

thrift_compile: small_message.thrift
	thrift --gen cpp small_message.thrift 

protobuf_compile: small_message.proto
	mkdir -p protocpp
	protoc --cpp_out=protocpp small_message.proto 

test_thrift: test_thrift.o small_message_types.o
	$(CXX) test_thrift.o small_message_types.o -o test_thrift $(THRIFT_LDFLAGS)

test_thrift.o: test_thrift.cpp thrift_compile
	$(CXX) $(THRIFT_CXXFLAGS) -c test_thrift.cpp

small_message_types.o: thrift_compile
	$(CXX) $(THRIFT_CXXFLAGS) -c gen-cpp/small_message_types.cpp

test_protobuf: test_protobuf.o small_message.pb.o
	$(CXX) test_protobuf.o small_message.pb.o -o test_protobuf $(PROTOBUF_LDFLAGS)

test_protobuf.o: test_protobuf.cpp protobuf_compile
	$(CXX) $(PROTOBUF_CXXFLAGS) -c test_protobuf.cpp

small_message.pb.o: protobuf_compile
	$(CXX) $(PROTOBUF_CXXFLAGS) -c protocpp/small_message.pb.cc

clean:
	rm -rf test_thrift test_protobuf gen-cpp protocpp *.o
