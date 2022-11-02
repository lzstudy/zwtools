#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "pin.h"
#include "codestd.h"

/**************************************************************************************************
 * @brief  : 写入引脚文件
 * @param  : 文件路径
 * @param  : 值
 * @return : 0成功, 其他失败
 **************************************************************************************************/
static int _write_pin_file(const char *path, const char *val)
{
    int fd, ret;

    /* 打开引脚属性文件 */
    fd = open(path, O_WRONLY);
    CHECK_RET(fd < 0, fd, "write pin file open %s fail %d", path, fd);

    /* 写入数据 */
    ret = write(fd, val, strlen(val) + 1);
    close(fd);
    return ret;
}

/**************************************************************************************************
 * @brief  : 读引脚文件
 * @param  : 文件路径
 * @param  : 值
 * @return : 0成功, 其他失败
 **************************************************************************************************/
static inline int read_pin_file(const char *path, char *val)
{
    int fd, ret;

    /* 打开引脚属性文件 */
    fd = open(path, O_RDONLY);
    CHECK_RET(fd < 0, fd, "read pin file open %s fail %d", path, fd);

    /* 读取数据 */
    ret = read(fd, val, 16);
    close(fd);
    return ret;
}

/**************************************************************************************************
 * @brief  : 写入整形数据
 * @param  : 文件路径
 * @param  : 值
 * @return : 0成功, 其他失败
 **************************************************************************************************/
static inline int write_pin_file(const char *path, int val)
{
    char str[10];

    sprintf(str, "%d", val);
    return _write_pin_file(path, str);
}

/**************************************************************************************************
 * @brief  : 引脚初始化
 * @param  : 引脚ID
 * @param  : 引脚方向
 * @param  : 引脚状态
 * @return : 0成功, 其他失败
 **************************************************************************************************/
static int pin_init(int pin, pin_dir dir, pin_state state)
{
    int ret;
    char buf[100];

    /* 导出设备 */
    write_pin_file("/sys/class/gpio/export", pin);

    /* 设置方向 */
    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
    ret = _write_pin_file(buf, (dir ? "out" : "in"));
    _CHECK_RET(ret < 0, ret);

    /* 设置初始电平 */
    sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
    ret = write_pin_file(buf, state);
    _CHECK_RET(ret < 0, ret);

    return 0;
}

/**************************************************************************************************
 * @brief  : 引脚退出
 * @param  : 引脚ID
 * @return : 0成功, 其他失败
 **************************************************************************************************/
static inline int pin_exit(int pin)
{
    return write_pin_file("/sys/class/gpio/unexport", pin);
}

/**************************************************************************************************
 * @brief  : 设置引脚状态
 * @param  : 引脚ID
 * @param  : 引脚状态
 * @return : 0成功, 其他失败
 **************************************************************************************************/
static inline int pin_set(int pin, pin_state state)
{
    char buf[100];

    sprintf(buf, "sys/class/gpio/gpio%d/value", pin);
    return write_pin_file(buf, state);   
}

/**************************************************************************************************
 * @brief  : 获取引脚状态
 * @param  : 引脚ID
 * @return : 0成功, 其他失败
 **************************************************************************************************/
static inline int pin_get(int pin)
{
    int ret;
    char buf[100], val[16];

    /* 读取文件 */
    sprintf(buf, "sys/class/gpio/gpio%d/value", pin);
    ret = read_pin_file(buf, val);
    _CHECK_RET(ret < 0, ret);

    return atoi(val);
}

static pin_ops _pin_ops = {
    .init = pin_init,
    .exit = pin_exit,
    .set  = pin_set,
    .get  = pin_get,
};

/**************************************************************************************************
 * @brief  : 获取引脚操作函数
 * @param  : None
 * @return : 0成功, 其他失败
 **************************************************************************************************/
pin_ops *get_pin_ops(void)
{
    return &_pin_ops;
}

