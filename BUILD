# generated by huangwf @ 2021.02.07

cc_binary (
    name = 'id_generator',
    srcs = [
        'servers/rpc/id_generator.cpp',
    ],
    deps = [
        ':id_generator_lib',
        '#gflags',
        '#protobuf',
        '#srpc',
    ],
)

cc_library (
    name = 'id_generator_lib',
    hdrs = [
        'cpp_common/utils/facility.h',
        'servers/includes/gflags_def.h',
        'servers/rpc/id_generator.h',
        'srpc/workflow/_include/workflow/WFFacilities.h',
    ],
    deps = [
        '//cpp_common:cpp_common',
        '//proto:id_generator_proto',
    ],
)
