#ifndef __XXX_H__
#define __XXX_H__
__BEGIN_DECLS

typedef struct _xxx_ops {
    int (*init)(void);                                                          /**@ 初始化. */
}xxx_ops;

xxx_ops *get_xxx_ops(void);                                                     /**# 获取xxx操作接口. */

__END_DECLS
#endif
