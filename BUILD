# generated by huangwf @ 2021.02.07

cc_binary (
    name = 'test_uniq_id',
    srcs = [
        'cpp_common/demo/test_uniq_id.cpp',
    ],
    deps = [
        '//cpp_common:cpp_common',
    ],
    extra_linkflags = [
        '-pthread',
    ],
)

cc_binary (
    name = 'http_server',
    srcs = [
        'servers/main.cpp',
    ],
    deps = [
        ':http_server_lib',
        '#gflags',
        '#brpc',
        '#protobuf',
    ],
)

cc_library (
    name = 'http_server_lib',
    srcs = [
        'servers/http_server.cpp',
    ],
    hdrs = [
        'incubator-brpc/src/butil/logging.h',
        'incubator-brpc/src/brpc/server.h',
        'incubator-brpc/src/brpc/restful.h',
        'servers/http_server.h',
    ],
    deps = [
        '//proto:gateway_proto',
    ],
)
