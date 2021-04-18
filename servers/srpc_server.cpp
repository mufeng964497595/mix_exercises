/*
 * File Created: Sunday, 18th April 2021 02:17:29
 * Author: huangweifeng (964497595@qq.com)
 * Desc: srpc框架学习demo
 * -----
 * Copyright (c) 2021 huangweifeng Inc.
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "proto/srpc_http.srpc.h"

namespace gateway {
class SrpcHttpServiceImpl : public gateway::SrpcHttpService::Service {
 public:
    void Add(gateway::SrpcHttpRequest*, gateway::SrpcHttpResponse*, srpc::RPCContext*) override;
};  // end class SrpcHttpServiceImpl

void SrpcHttpServiceImpl::Add(gateway::SrpcHttpRequest* req, gateway::SrpcHttpResponse* resp
                                , srpc::RPCContext* ctx) {
    resp->set_result(req->number_a() + req->number_b());
    resp->set_err_code(0);
    resp->set_err_msg("success");

    printf("get_req:\n%s\nset_resp:\n%s\n", req->ShortDebugString().c_str(), resp->ShortDebugString().c_str());
}

}   // end namespace gateway

void sig_handler(int signo) {
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    srpc::SRPCHttpServer server_http;
    gateway::SrpcHttpServiceImpl impl;
    server_http.add_service(&impl);
    server_http.start(8010);
    pause();
    server_http.stop();

    return 0;
}
