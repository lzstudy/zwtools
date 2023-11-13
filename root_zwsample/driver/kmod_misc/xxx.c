#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/of_platform.h>
#include <linux/of_device.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include "codestd.h"

typedef struct _xxx_priv {
	struct miscdevice dev;															/**@ misc设备. */
}xxx_priv;

/* IOC define */
#define	IOC_TEST				_IOR(0x21, 0, int)									/**< 等待事件. */

/* 上下文宏 */
#define to_xxx_priv(x)			container_of(x, xxx_priv, dev)				/**< 获取设备信息. */

/**************************************************************************************************
 * @brief  : 接口 - open
 * @param  : inode
 * @param  : 文件信息
 * @return : 0成功, 其他失败
**************************************************************************************************/
static int xxx_open(struct inode *inode, struct file *filp)
{
	xxx_priv *priv = to_xxx_priv(filp->private_data);
	LOG_I("priv addr = %p", priv);
	LOG_I("xxx open");
	return 0;
}

/**************************************************************************************************
 * @brief  : 接口 - release
 * @param  : inode
 * @param  : 文件信息
 * @return : 0成功, 其他失败
**************************************************************************************************/
static int xxx_release(struct inode *inode, struct file *filp)
{
	LOG_I("xxx release\n");
	return 0;
}

/**************************************************************************************************
 * @brief  : 接口 - ioctl
 * @param  : 文件信息
 * @param  : 命令码
 * @param  : 参数
 * @return : 0成功, -1失败
**************************************************************************************************/
static long xxx_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
	case IOC_TEST:
		break;

	default:
		return -ENOIOCTLCMD;
	}

	return 0;
}

static const struct file_operations xxx_fops = {
	.owner	 = THIS_MODULE,
	.open	 = xxx_open,
	.release = xxx_release,
	.unlocked_ioctl = xxx_ioctl,
};

/**************************************************************************************************
 * @brief  : 属性 - w - dgb1
 * @param  : None
 * @return : 0成功, -1失败
**************************************************************************************************/
static ssize_t xxx_dbg1_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int val;
	xxx_priv *priv = to_xxx_priv(dev->driver_data);

    if(kstrtoint(buf, 0, &val))
        return -EINVAL;
	
	LOG_I("priv addr = %p, val = %d", priv, val);
	return count;
}

/**************************************************************************************************
 * @brief  : 属性 - r - dgb2
 * @param  : None
 * @return : 0成功, -1失败
**************************************************************************************************/
static ssize_t xxx_dbg2_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int val = 0;
	xxx_priv *priv = to_xxx_priv(dev->driver_data);

	LOG_I("priv addr = %p, val = %d", priv, val);
	return sprintf(buf, "%d\n", val);
}

/**************************************************************************************************
 * @brief  : 属性 - r - dgb3
 * @param  : None
 * @return : 0成功, -1失败
**************************************************************************************************/
static ssize_t xxx_dbg3_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int val = 0;
	xxx_priv *priv = to_xxx_priv(dev->driver_data);

	LOG_I("priv addr = %p, val = %d", priv, val);
	return sprintf(buf, "%d\n", val);
}

/**************************************************************************************************
 * @brief  : 属性 - w - dgb3
 * @param  : None
 * @return : 0成功, -1失败
**************************************************************************************************/
static ssize_t xxx_dbg3_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int val;
	xxx_priv *priv = to_xxx_priv(dev->driver_data);

    if(kstrtoint(buf, 0, &val))
        return -EINVAL;
	
	LOG_I("priv addr = %p, val = %d", priv, val);
	return count;
}

static DEVICE_ATTR(dbg1, 0220, NULL, xxx_dbg1_store);
static DEVICE_ATTR(dbg2, 0440, xxx_dbg2_show, NULL);
static DEVICE_ATTR(dbg3, 0640, xxx_dbg3_show, xxx_dbg3_store);

static struct attribute *xxx_attr[] = {
	&dev_attr_dbg1.attr,
	&dev_attr_dbg2.attr,
	&dev_attr_dbg3.attr,
	NULL
};

static struct attribute_group xxx_attr_group = {
	.name = "attr",
	.attrs = xxx_attr,
};

/**************************************************************************************************
 * @brief  : 光电开关设备匹配
 * @param  : 设备
 * @return : 0成功, -1失败
**************************************************************************************************/
static int xxx_probe(struct platform_device *pdev)
{
	int ret;
	xxx_priv *priv;
	struct device *dev = &pdev->dev;

	/* 申请内存空间 */
	priv = devm_kzalloc(dev, sizeof(xxx_priv), GFP_KERNEL);
	CI_RET(!priv, -ENOMEM, "xxx alloc fail");

	/* 初始化MISC设备 */
	priv->dev.name  = "xxx";
	priv->dev.minor = MISC_DYNAMIC_MINOR;
	priv->dev.fops  = &xxx_fops;
	
	/* 注册MISC设备 */
	ret = misc_register(&priv->dev);
	CI_RET(ret < 0, ret, "xxx misc register fail %d", ret);

	/* 创建属性文件 */
	ret = sysfs_create_group(&priv->dev.this_device->kobj, &xxx_attr_group);
	CI_RET(ret < 0, ret, "create light switch attr group fail %d", ret);

	/* 保存私有数据 */
	platform_set_drvdata(pdev, priv);
	LOG_I("xxx init success\n");
	return 0;
}

/**************************************************************************************************
 * @brief  : 驱动删除
 * @param  : 设备
 * @return : 0成功, -1失败
**************************************************************************************************/
static int xxx_remove(struct platform_device *pdev)
{
	xxx_priv *priv = platform_get_drvdata(pdev);

	/* 移除属性 */
	sysfs_remove_group(&priv->dev.this_device->kobj, &xxx_attr_group);

	/* 注销MISC设备 */
	misc_deregister(&priv->dev);
	LOG_I("xxx remove\n");
	return 0;
}

static const struct of_device_id xxx_match[] = {
	{ .compatible = "xxx" },
	{},
};
MODULE_DEVICE_TABLE(of, xxx_match);

static struct platform_driver xxx_driver = {
    .probe  = xxx_probe,
    .remove = xxx_remove,
	.driver	= {
		.name = "xxx",
		.of_match_table = of_match_ptr(xxx_match),
	},
};

module_platform_driver(xxx_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZW");
MODULE_DESCRIPTION("dirver - xxx");
