/*
 * File Created: Sunday, 28th March 2021 22:07:04
 * Author: huangweifeng (964497595@qq.com)
 * Desc: brpc http入口gateway层
 * -----
 * Copyright (c) 2021 huangweifeng Inc.
 */
#ifndef __SERVERS_HTTP_SERVER_H__
#define __SERVERS_HTTP_SERVER_H__

#include "proto/http.pb.h"

namespace gateway {
class HttpServiceImpl : public HttpService {
 public:
    HttpServiceImpl() {}
    virtual ~HttpServiceImpl() {}
    void Echo(google::protobuf::RpcController*, const HttpRequest*, HttpResponse*, google::protobuf::Closure*);
};  // end class HttpServiceImpl

}   // end namespace gateway
#endif  // #endif #ifndef __SERVERS_HTTP_SERVER_H__
