# mix_exercises
* 各种小技能组合练习，形成一个大杂烩网站，主要将后端各种小零件混合在一起~

# blade & ninja安装
* 直接执行根目录的./build.sh即可，如果中途报错说缺少依赖，请自行安装
* [blade + ninja编译环境搭建博客记录](https://blog.csdn.net/feng964497595/article/details/113748398)

# srpc安装
* 拉完代码后直接进入srpc目录，执行make编译
* 编译完，将srpc lib文件cp到/usr/lib路径下：
```shell
    sudo cp srpc/_lib/libsrpc.* /usr/lib/
    sudo cp srpc/workflow/_lib/libworkflow.* /usr/lib/
```
* srpc比较轻量级，目前先使用srpc框架进行学习

# brpc安装
* brpc比较庞大，目前先使用srpc框架，学习完毕后再用brpc搞一套
* [brpc安装](https://github.com/apache/incubator-brpc/blob/master/docs/cn/getting_started.md)
* 编译完，将brpc lib文件cp到/usr/lib/路径下：
```shell
    sudo cp incubator-brpc/libbrpc.a /usr/lib/
    sudo cp incubator-brpc/libbrpc.so /usr/lib/
```

