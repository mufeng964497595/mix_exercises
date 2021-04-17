/*
 * File Created: Sunday, 28th March 2021 03:30:21
 * Author: huangweifeng (964497595@qq.com)
 * Desc: brpc http入口gateway层
 * -----
 * Copyright (c) 2021 huangweifeng Inc.
 */

#include "servers/http_server.h"

#include <gflags/gflags.h>

#include <string>

#include "butil/logging.h"
#include "brpc/server.h"
#include "brpc/restful.h"
#include "proto/http.pb.h"

void gateway::HttpServiceImpl::Echo(google::protobuf::RpcController* cntl_base,
                            const gateway::HttpRequest* /* http_request */,
                            gateway::HttpResponse* /* http_response */,
                            google::protobuf::Closure* done) {
    // This object helps you to call done->Run() in RAII style. If you need
    // to process the request asynchronously, pass done_guard.release().
    brpc::ClosureGuard done_guard(done);

    brpc::Controller* cntl =
        static_cast<brpc::Controller*>(cntl_base);
    // Fill response.
    cntl->http_response().set_content_type("text/plain");
    std::string resp_str("queries: ");

    // butil::IOBufBuilder os;
    // os << "queries:";
    for (brpc::URI::QueryIterator it = cntl->http_request().uri().QueryBegin();
            it != cntl->http_request().uri().QueryEnd(); ++it) {
        // os << ' ' << it->first << '=' << it->second;
        resp_str.append(" ").append(it->first).append("=").append(it->second);
    }
    resp_str.append("\nbody: ").append(cntl->request_attachment().to_string()).append("\n");
    // os << "\nbody: " << cntl->request_attachment() << '\n';
    // os.move_to(cntl->response_attachment());
    cntl->response_attachment().append(resp_str);
    LOG(INFO) << "echo: " << resp_str;
}
