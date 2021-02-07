#!/bin/bash

function check_blade() {
    blade --version 1>/dev/null 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "blade not found"
        return -1
    fi

    return 0
}

function install_blade() {
    check_blade
    if [ $? -eq 0 ]; then
        echo "blade had intalled"
        return
    fi

    echo "ready to install blade"
    blade-build/install 2>&1
    source ~/.profile

    ret=0
    check_blade
    if [ $? -eq 0 ]; then
        echo "blade install success"
    else
        echo "blade install fail"
        ret=-1
    fi

    return $ret
}

function check_ninja() {
    ninja --version 1>/dev/null 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "ninja not found"
        return -1
    fi

    return 0
}

function install_ninja() {
    check_ninja
    if [ $? -eq 0 ]; then
        echo "ninja had installed"
        return
    fi

    echo "ready to install ninja"
    cd ninja
    ./configure.py --bootstrap 2>&1
    cp ninja ~/bin
    cd ..

    ret=0
    check_ninja
    if [ $? -eq 0 ]; then
        echo "ninja install success"
    else
        echo "ninja install fail"
        ret=-1
    fi

    return $ret
}

function build_normal() {
    # 编译需要安装blade和ninja
    install_blade
    if [ $? -ne 0 ]; then
        return -1
    fi

    install_ninja
    if [ $? -ne 0 ]; then
        return -1
    fi

    blade build 2>&1
}

function blade_clean() {
    blade clean 2>&1
}

########### 主流程 ###########
case $1 in
    'build')
        build_normal
    ;;
    'clean')
        blade_clean
    ;;
    *)
        build_normal
    ;;
esac
