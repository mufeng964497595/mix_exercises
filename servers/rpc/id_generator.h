/*
 * File Created: Monday, 19th April 2021 02:05:10
 * Author: huangweifeng (964497595@qq.com)
 * Desc: id生成器srpc
 * -----
 * Copyright (c) 2021 huangweifeng Inc.
 */

#ifndef __SERVERS_RPC_ID_GENERATOR_H__
#define __SERVERS_RPC_ID_GENERATOR_H__

#include <string>

#include "proto/id_generator.srpc.h"
#include "servers/includes/gflags_def.h"
#include "servers/includes/mysql_struct.h"

namespace mix_exer {
class GeneratorIdImpl : public GeneratorId::Service {
 public:
    GeneratorIdImpl() : Service(), min_step_limit_(FLAGS_min_step_limit) {
    }

    // 配置初始化
    bool Init();

    // 注册id生成器的业务来源
    void Regist(RegistSourceReq*, RegistSourceResp*, srpc::RPCContext*) override;
    // 生成id序列
    void GeneId(GeneIdReq*, GeneIdResp*, srpc::RPCContext*) override;

 private:
    RegistSourceResp::ErrCodeEnum CheckRegistReq(const RegistSourceReq* const);
    void SetRegistSourceResp(RegistSourceResp::ErrCodeEnum, RegistSourceResp*);
    RegistSourceResp::ErrCodeEnum Regist(const RegistSourceReq* const);
    // int GeneId();

 private:
    int min_step_limit_;    // 最小步长限制，请求入参的step不能低于该值
    MysqlConfig mysql_config_;  // mysql配置
    std::string id_generator_table_;    // id生成器mysql表名
};  // end class GeneratorIdImpl

}   // end namespace mix_exer

#endif  // end #ifndef __SERVERS_RPC_ID_GENERATOR_H__
