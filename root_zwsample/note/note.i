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
    echo "root_index.rst   -    root index"
    echo "index.rst        -    caption index"
    echo "base.rst         -    base note"
    echo "hardware.rst     -    describe hardware note"
    echo "subsys.rst       -    describe subsys note"
    echo "driver.rst       -    driver note"
    exit 1
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
