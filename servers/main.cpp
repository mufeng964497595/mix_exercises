/*
 * File Created: Tuesday, 30th March 2021 22:54:24
 * Author: huangwf (964497595@qq.com)
 * Desc: 服务入口
 * -----
 * Copyright (c) 2021 Inc.
 */

#include <fcntl.h>
#include <gflags/gflags.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "servers/http_server.h"

#include "butil/logging.h"
#include "brpc/restful.h"

DEFINE_int32(port, 8010, "TCP Port of this server");
DEFINE_int32(idle_timeout_s, -1, "Connection will be closed if there is no "
            "read/write operations during the last `idle_timeout_s'");
DEFINE_int32(logoff_ms, 2000, "Maximum duration of server's LOGOFF state "
            "(waiting for client to close connection before server stops)");

static int Daemon() {
    if (fork() != 0) {
        exit(0);
    }
    if (setsid() == -1) {
        return -1;
    }

    int fd = open("/dev/null", O_RDWR, 0);
    if (-1 != fd) {
        if (dup2(fd, STDIN_FILENO) < 0 ||
                dup2(fd, STDOUT_FILENO) < 0 ||
                dup2(fd, STDERR_FILENO) < 0) {
            return -1;
        }

        if (fd > STDERR_FILENO && close(fd) < 0) {
            return -1;
        }
    }

    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);

    return 0;
}

void InitServerLog() {
    std::string log_path("/export/servers/http_server/logs");
    if (access(log_path.c_str(), F_OK) != 0) {
    //     if (create_dir_recursion(log_path) != 0) {
    //         fprintf(stderr, "create directory: %s failed", log_path.c_str());
    //         exit(-1);
    //     }
    }

    // std::string info_file(log_path + "/info_");
    // google::SetLogDestination(google::INFO, info_file.c_str());

    // std::string warn_file(log_path + "/warn_");
    // google::SetLogDestination(google::WARNING, warn_file.c_str());

    // std::string error_file(log_path + "/error_");
    // google::SetLogDestination(google::ERROR, error_file.c_str());

    // FLAGS_max_log_size = 100;   // 单元M
    // // FLAGS_logbufsecs
    // std::string glog_level = "INFO";
    // FLAGS_stderrthreshold = google::INFO;   // INFO, ERROR, WARNING
}

int main(int argc, char* argv[]) {
    // Parse gflags. We recommend you to use gflags as well.
    google::ParseCommandLineFlags(&argc, &argv, true);
    if (Daemon() != 0) {
        fprintf(stderr, "daemon fail!!!");
        return -1;
    }
    InitServerLog();

    ::logging::LoggingSettings log_setting;
    log_setting.log_file = "/export/servers/http_server/logs/http_server.log";
    log_setting.logging_dest = logging::LOG_TO_FILE;
    ::logging::InitLogging(log_setting);

    std::srand(std::time(0));

    // Generally you only need one Server.
    brpc::Server server;
    gateway::HttpServiceImpl http_svc;
    if (server.AddService(&http_svc,
                        brpc::SERVER_DOESNT_OWN_SERVICE,
                        "/http/echo => Echo") != 0) {
        LOG(ERROR) << "Fail to add http_svc";
        return -1;
    }
    // 启动服务
    brpc::ServerOptions options;
    options.idle_timeout_sec = FLAGS_idle_timeout_s;
    if (server.Start(FLAGS_port, &options) != 0) {
        LOG(ERROR) << "Fail to start HttpServer";
        return -1;
    }
    server.RunUntilAskedToQuit();

    LOG(ERROR) << "server quit";
//    google::FlushLogFiles(google::GLOG_INFO);

    return 0;
}
