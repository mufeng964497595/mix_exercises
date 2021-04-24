load('//build_rules/srpc_proto.bld', 'srpc_proto_library')

proto_library(
    name = 'gateway_proto',
    srcs = [
        'http.proto',
    ],
)

srpc_proto_library(
    name = 'srpc_proto',
    srcs = [
        'srpc_http.proto',
    ],
    dir = 'proto'
)

srpc_proto_library(
    name = 'id_generator_proto',
    srcs = [
        'id_generator.proto',
    ],
    dir = 'proto'
)
