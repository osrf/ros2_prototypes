cmake_minimum_required(VERSION 2.8)
project(test)

include_directories(src)

add_executable(produce_consume_struct src/main_produce_consume_struct.cpp)
target_link_libraries(produce_consume_struct rt)

add_executable(produce_copy_consume_struct src/main_produce_copy_consume_struct.cpp)
target_link_libraries(produce_copy_consume_struct rt)

add_executable(produce_consume_method src/main_produce_consume_method.cpp)
target_link_libraries(produce_consume_method rt)

add_executable(produce_consume_backend_plain src/main_produce_consume_backend_plain.cpp)
target_link_libraries(produce_consume_backend_plain rt)

add_executable(produce_consume_backend_proto src/main_produce_consume_backend_proto.cpp src/proto/small_message.pb.cc)
target_link_libraries(produce_consume_backend_proto rt protobuf)

add_executable(large_produce_consume_struct src/main_large_produce_consume_struct.cpp)
target_link_libraries(large_produce_consume_struct rt)

add_executable(large_produce_copy_consume_struct src/main_large_produce_copy_consume_struct.cpp)
target_link_libraries(large_produce_copy_consume_struct rt)

add_executable(large_boost_produce_consume_method src/main_large_boost_produce_consume_method.cpp)
target_link_libraries(large_boost_produce_consume_method rt)

add_executable(large_boost_produce_copy_consume_method src/main_large_boost_produce_copy_consume_method.cpp)
target_link_libraries(large_boost_produce_copy_consume_method rt)

add_executable(large_boost_produce_consume_backend_plain src/main_large_boost_produce_consume_backend_plain.cpp)
target_link_libraries(large_boost_produce_consume_backend_plain rt)

#add_executable(large_boost_produce_consume_backend_proto src/main_large_boost_produce_consume_backend_proto.cpp src/proto/large_message.pb.cc)
#target_link_libraries(large_boost_produce_consume_backend_proto rt protobuf)
