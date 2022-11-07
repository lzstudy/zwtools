#ifndef __CODESTD_H__
#define __CODESTD_H__
#include <stdio.h>
#include <stdint.h>

/* 判断参数 */
#define CHECK_PARAM(cond, val, fmt, ...) \
    do {if(cond) {printf(fmt"\n", ##__VA_ARGS__); return val;}} while(0)

#define CHECK_P(cond) \
    do {if(cond) {return -1;}} while(0)

#define CHECK_PARAM_EX(cond, fmt, ...) \
     do {if(cond) {printf(fmt"\n", ##__VA_ARGS__); return;}} while(0)

/* 判断并退出 */
#define CHECK_EXIST(cond, fmt, ...) \
    do {if(cond) {printf(fmt"\n", ##__VA_ARGS__); exit(1);}} while(0)

/* 判断并返回 */
#define CHECK_RET(cond, val, fmt, ...) \
    do {if(cond) {printf(fmt"\n", ##__VA_ARGS__); return val;}} while(0)

#define _CHECK_RET(cond, val) \
    do {if(cond) {return val;}} while(0)

#define CHECK_RET_EX(cond, fmt, ...) \
    do {if(cond) {printf(fmt"\n", ##__VA_ARGS__); return;}} while(0)

#define _CHECK_RET_EX(cond) \
    do {if(cond) {return;}} while(0)

#define CHECK_R(cond, fmt) \
    do {if(cond < 0) {printf(fmt" fail(%d)\n", -cond); return -cond;}} while(0)

/* 判断并GOTO */
#define CHECK_GOTO(cond, val, fmt, ...) \
    do {if(cond) {printf(fmt"\n", ##__VA_ARGS__); goto val;}} while(0)

#define CHECK_GOTO_EX(cond, val) \
    do {if(cond) {goto val;}} while(0)

/* 打印信息 */
#define LOG_I(fmt, ...)          printf(fmt"\n", ##__VA_ARGS__);

/* 32位大小端转换 */
#define BLC32(x)                ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) \
                                    | (((x) & 0xff0000) >> 8) | (((x) >> 24) & 0xff))

/* 16位大小端转换 */
#define BLC16(x)                ((((x) & 0xff) << 8) | (((x) >> 8) & 0xff))

/* 计算数组程成员数量 */
#define ARRAY_SIZE(arr)         (sizeof(arr) / sizeof((arr)[0]))

/* 常用接口 */
void print_hex_value(const char *prompt, void *data, int datalen);              /**# 按16进制打印. */

/* 调试接口 */
void *break_line(const char *promt);                                            /**# 断点. */
void *break_line_stop(void);                                                    /**# 停止. */


#endif
