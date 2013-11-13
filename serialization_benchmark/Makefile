THRIFT_CXXFLAGS := $(shell pkg-config --cflags thrift) -O3
THRIFT_LDFLAGS := $(shell pkg-config --libs thrift)

PROTOBUF_CXXFLAGS := $(shell pkg-config --cflags protobuf) -O3
PROTOBUF_LDFLAGS := $(shell pkg-config --libs protobuf)

CAPNP_CXXFLAGS := -DNDEBUG -std=c++11 -O3
CAPNP_LDFLAGS := -lcapnp -lrt -lkj

benchmar: build
	./test_protobuf
	./test_thrift
	./test_capnp
	./test_rosmsg

build: test_protobuf test_thrift test_capnp test_rosmsg

thrift_compile: small_message.thrift
	thrift --gen cpp small_message.thrift 

capnp_compile: small_message.capnp
	mkdir -p capnpcpp
	capnp compile -oc++:capnpcpp small_message.capnp

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

test_capnp.o: test_capnp.cpp capnp_compile
	$(CXX) $(CAPNP_CXXFLAGS) -c test_capnp.cpp

small_message_capnp.o: capnp_compile
	$(CXX) $(CAPNP_CXXFLAGS) -o small_message_capnp.o -c capnpcpp/small_message.capnp.c++

test_capnp: test_capnp.o small_message_capnp.o
	$(CXX) test_capnp.o small_message_capnp.o -o test_capnp $(CAPNP_LDFLAGS)

test_rosmsg: src/rosmsg_benchmark/src/test_rosmsg.cpp
	catkin_make
	cp devel/lib/rosmsg_benchmark/test_rosmsg test_rosmsg

clean:
	rm -rf test_rosmsg test_thrift test_protobuf test_capnp gen-cpp protocpp capnpcpp build devel src/CMakeLists *.o
