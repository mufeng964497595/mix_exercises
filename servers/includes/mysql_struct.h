/*
 * File Created: Saturday, 24th April 2021 17:22:53
 * Author: huangweifeng (964497595@qq.com)
 * Desc: 定义mysql使用的结构体
 * -----
 * Copyright (c) 2021 Inc.
 */
#ifndef __SERVERS_INCLUDES_MYSQL_STRUCT_H__
#define __SERVERS_INCLUDES_MYSQL_STRUCT_H__

#include <string>

namespace mix_exer {
class MysqlConfig {
 public:
    MysqlConfig() {
    }
    MysqlConfig(const std::string& user, const std::string& passwd, const std::string& host, const std::string& port
                , const std::string& dbname, const std::string& charset)
            : user_name_(user), password_(passwd), host_(host), port_(port), db_name_(dbname), charset_(charset) {
    }

 public:
    std::string user_name_;
    std::string password_;
    std::string host_;
    std::string port_;
    std::string db_name_;
    std::string charset_;
};  // end class MysqlConfig

};  // end namespace mix_exer

#endif  // end #ifndef __SERVERS_INCLUDES_MYSQL_STRUCT_H__
