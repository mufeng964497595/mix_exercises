/*
 * File Created: Monday, 19th April 2021 02:05:05
 * Author: huangweifeng (964497595@qq.com)
 * Desc: id生成器srpc
 * -----
 * Copyright (c) 2021 huangweifeng Inc.
 */

#include "servers/rpc/id_generator.h"

#include <signal.h>
#include <unistd.h>

#include <iostream>

#include "cpp_common/utils/facility.h"
#include "proto/id_generator.srpc.h"
#include "servers/includes/gflags_def.h"
#include "workflow/WFFacilities.h"

namespace mix_exer {
// 配置初始化
bool GeneratorIdImpl::Init() {
    // TODO(huangweifeng) 改为从配置文件读取
    if (FLAGS_mysql_user_name.empty() || FLAGS_mysql_password.empty() || FLAGS_mysql_host.empty()
            || FLAGS_mysql_port.empty() || FLAGS_mysql_db_name_.empty() || FLAGS_mysql_charset.empty()
            || FLAGS_id_generator_table.empty()) {
        std::cout << "miss mysql config, exit" << std::endl;
        return false;
    }

    mysql_config_.user_name_ = FLAGS_mysql_user_name;
    mysql_config_.password_ = FLAGS_mysql_password;
    mysql_config_.host_ = FLAGS_mysql_host;
    mysql_config_.port_ = FLAGS_mysql_port;
    mysql_config_.db_name_ = FLAGS_mysql_db_name_;
    mysql_config_.charset_ = FLAGS_mysql_charset;
    id_generator_table_ = FLAGS_id_generator_table;

    min_step_limit_ = FLAGS_min_step_limit;

    return true;
}

// 注册id生成器的业务来源
void GeneratorIdImpl::Regist(RegistSourceReq* req, RegistSourceResp* resp, srpc::RPCContext* ctx) {
    utils::Trim(req->mutable_source_id());  // 清除首尾空白字符
    auto err_code = CheckRegistReq(req);
    if (RegistSourceResp::SUCCESS != err_code) {
        SetRegistSourceResp(err_code, resp);
        return;
    }

    err_code = Regist(req);
    SetRegistSourceResp(err_code, resp);
}

RegistSourceResp::ErrCodeEnum GeneratorIdImpl::CheckRegistReq(const RegistSourceReq* const req) {
    if (req->source_id().empty()) {
        return RegistSourceResp::EMPTY_SOURCE_ID;
    }
    if (req->step() < min_step_limit_) {
        return RegistSourceResp::STEP_OUT_OF_LIMIT;
    }

    return RegistSourceResp::SUCCESS;
}

void GeneratorIdImpl::SetRegistSourceResp(RegistSourceResp::ErrCodeEnum err_code, RegistSourceResp* resp) {
    resp->set_err_code(err_code);
    resp->set_err_msg(RegistSourceResp_ErrCodeEnum_Name(err_code));
}

RegistSourceResp::ErrCodeEnum GeneratorIdImpl::Regist(const RegistSourceReq* const req) {
    // TODO(huangweifeng) 写db


    return RegistSourceResp::SUCCESS;
}

// 生成id序列
void GeneratorIdImpl::GeneId(GeneIdReq* req, GeneIdResp* resp, srpc::RPCContext*) {
//    if (!IsValidGeneIdReq(req, resp)) {
//        return;
//    }
//
//    GeneId(req, resp);
}

}   // end namespace mix_exer

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo) {
    wait_group.done();
}

int main(int argc, char* argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    srpc::SRPCHttpServer server_http;
    mix_exer::GeneratorIdImpl impl;
    if (impl.Init()) {
        std::cout << "server Init fail" << std::endl;
        exit(-1);
    }

    server_http.add_service(&impl);
    int ret = server_http.start(FLAGS_server_port);
    if (0 == ret) {
        std::cout << "server start success" << std::endl;
        wait_group.wait();
        server_http.stop();
    } else {
        std::cout << "server start fail, ret[" << ret << "], port[" << FLAGS_server_port << "]exit" << std::endl;
        google::protobuf::ShutdownProtobufLibrary();
        exit(-1);
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
