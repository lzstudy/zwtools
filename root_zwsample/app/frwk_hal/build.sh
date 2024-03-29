PATH_INSTALL=_install
PATH_INCLUDE=${PATH_INSTALL}/include
HAL_INC=${PATH_INCLUDE}/hal.h
INC_FILE=

########################################################################################################
# 程序入口
########################################################################################################
function make_hal_inc()
{
    # 写入内容
    for file in ${INC_FILE}
    do
        inc=${file##*/}
        code="#include \"${inc}\""
        sed -i "1i ${code}" ${HAL_INC}
    done

	# 删除_build目录
	rm _build -rf
}

########################################################################################################
# 初始化环境
########################################################################################################
function init_env()
{
    rm -rf _build ${PATH_INSTALL}
    mkdir -p _build ${PATH_INSTALL} ${PATH_INCLUDE}
}

########################################################################################################
# 编译代码
########################################################################################################
function build_code()
{
    cd _build
    cmake .. && make
    cd ..
}

########################################################################################################
# 整理相关文件
########################################################################################################
function output_file()
{
    # 拷贝相关头文件
    raw_file=$(find ./ -name *.h 2>/dev/null)
    for file in ${raw_file}
    do
        cp ${file} ${PATH_INCLUDE} 2>/dev/null
    done

    # 删除无关文件的文件
    rm ${PATH_INCLUDE}/hf_utils.h 2>/dev/null

    # 保存有用的文件
    INC_FILE=$(find ${PATH_INCLUDE} -name *.h 2>/dev/null)

    # 拷贝库和测试文件
    cp _build/libhal.so ${PATH_INSTALL}         # 拷贝生成的动态库
    cp scripts/install/* _install -rf           # 拷贝测试文件
}

########################################################################################################
# 程序入口
########################################################################################################
function build_entry()
{
    init_env           # 初始化环境
    build_code         # 编译代码
    output_file        # 拷贝相关文件
    make_hal_inc       # 制作hal头文件
}

build_entry
