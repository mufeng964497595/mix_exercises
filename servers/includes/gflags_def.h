/*
 * File Created: Saturday, 24th April 2021 17:37:45
 * Author: huangweifeng (964497595@qq.com)
 * Desc: gflags定义文件
 * -----
 * Copyright (c) 2021 Inc.
 */

#ifndef __SERVERS_INCLUDES_GFLAGS_DEF_H__
#define __SERVERS_INCLUDES_GFLAGS_DEF_H__

#include <gflags/gflags.h>

DEFINE_int32(server_port, 0, "tcp port of id_generator server, by huangweifeng@2021.04.24");
DEFINE_string(mysql_user_name, "", "mysql user_name, by huangweifeng@2021.04.24");
DEFINE_string(mysql_password, "", "mysql password, by huangweifeng@2021.04.24");
DEFINE_string(mysql_host, "", "mysql host, by huangweifeng@2021.04.24");
DEFINE_string(mysql_port, "3306", "mysql port, by huangweifeng@2021.04.24");
DEFINE_string(mysql_db_name_, "", "mysql database name, by huangweifeng@2021.04.24");
DEFINE_string(mysql_charset, "utf8", "mysql charset, by huangweifeng@2021.04.24");

// id generator特有的参数
DEFINE_string(id_generator_table, "IdGenerator", "mysql table_name of id generator server"
                                                ", by huangweifeng@2021.04.24");
DEFINE_int32(min_step_limit, 100, "the min step of the id generator, by huangweifeng@2021.04.24");

#endif  // #ifndef __SERVERS_INCLUDES_GFLAGS_DEF_H__
