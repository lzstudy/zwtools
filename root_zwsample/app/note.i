#!/bin/bash

PATH_SAMPLE_ROOT=$(cd `dirname $0`; pwd)


########################################################################################################
# 模板业务
########################################################################################################
function sample_work()
{
    case $1 in
        -a)
        echo "hello"
        ;;
 
        *)
        cp ${PATH_SAMPLE_ROOT}/$1 .
        ;;
    esac
}

########################################################################################################
# 帮助信息
########################################################################################################
function sample_help()
{
    echo "CMakeLists.txt   -    CmakeLists sample"
    echo "index.rst        -    note caption index"
    echo "test.rst         -    note text"
}

########################################################################################################
# 模板入口
########################################################################################################
function sample_entry()
{
    if [ $1 = '-h' ];then
        sample_help
    fi

    sample_work $1
}

sample_entry $@
