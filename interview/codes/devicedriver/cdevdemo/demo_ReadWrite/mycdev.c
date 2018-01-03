

/*
 *	
 *	echo 5 > /proc/sys/kernel/printk
 *	5   4   1   7
 *	Then, dmesg will show my_cdev_exit print when we excute "rmmod".
 *
 */



#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
//#include <asm/system.h>
#include <asm/errno.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>


#define BUFFERSIZE      200
#define DEVICE_MAJOR    199 //设置一个主设备号*/

static int device_major = DEVICE_MAJOR;
//定义一个与字符设备对应的结构体
struct my_cdev
{
    struct cdev  cdev; //cdev结构体，与字符设备对应*/
//下面可以定义一些与字符设备相关的数据*/
    unsigned char mem[BUFFERSIZE];
};
struct my_cdev *my_cdevp; //*设备结构体指针*/
int my_cdev_open(struct inode *node, struct file *filp)
{
//将设备结构体指针赋给文件私有数据指针*/
    filp->private_data = my_cdevp; //这样可以通过文件私有数据指针得到设备结构体
	return 0;
}
int my_cdev_release(struct inode *node, struct file *filp)
{
    return 0;
}
static size_t my_cdev_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long  p     = *ppos;              //文件当前位置*/
    unsigned int   count = size;               //要读取的长度*/
    int            ret   = 0;
    struct my_cdev *dev  = filp->private_data; //通过文件私有数据指针得到设备结构体，和前面的open对应*/

    if (p >= BUFFERSIZE)
    {
        return count ? -ENXIO : 0;
    }
    if (count > BUFFERSIZE - p)
    {
        count = BUFFERSIZE - p;
    }
//内核空间->用户空间*/
    if (copy_to_user(buf, (void *)(dev->mem + p), count))
    {
        ret = -EFAULT;
    }
    else
    {
        *ppos += count;
        ret    = count;
    }
    return ret;
}
static size_t my_cdev_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long  p     = *ppos;
    unsigned int   count = size;
    int            ret   = 0;
    struct my_cdev *dev  = filp->private_data;

    if (p >= BUFFERSIZE)
    {
        return count ? -ENXIO : 0;
    }
    if (count > BUFFERSIZE - p)
    {
        count = BUFFERSIZE - p;
    }
    if (copy_from_user(dev->mem + p, buf, count))
    {
        ret = -EFAULT;
    }
    else
    {
        *ppos += count;
        ret    = count;
    }
    return ret;
}
static loff_t my_cdev_llseek(struct file *filp, loff_t offset, int orig)
{
    loff_t ret = 0;

    switch (orig)
    {
    case 0:
        if (offset < 0)
        {
            ret = -EINVAL;
            break;
        }
        if (offset > BUFFERSIZE)
        {
            ret = -EINVAL;
            break;
        }
        filp->f_pos = (unsigned int)offset;
        ret         = filp->f_pos;
        break;

    default:
        ret = -EINVAL;
        break;
    }
    return ret;
}
//文件操作结构体*/
static const struct file_operations my_cdev_fops =
{
	.owner = THIS_MODULE,
    .open    = my_cdev_open,
    .release = my_cdev_release,
    .read    = my_cdev_read,
    .write   = my_cdev_write,
    .llseek  = my_cdev_llseek,
};
//初始化并注册cdev,就是注册我们自己的字符设备*/
static void my_cdev_setup(struct my_cdev *dev, int index)
{
    int   err;
    dev_t devno = MKDEV(DEVICE_MAJOR, index);

    cdev_init(&dev->cdev, &my_cdev_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops   = &my_cdev_fops; //我认为在cdev_init里应该做过赋值，应该可以不用写*/
    err             = cdev_add(&dev->cdev, devno, 1);
    if (err)
    {
        printk(KERN_NOTICE "Error %d adding LED%d", err, index);
    }
}
static int __init my_cdev_init(void)
{
	printk(KERN_NOTICE "my_cdev init!");
	
    int   result, index = 0;
    dev_t devno = MKDEV(DEVICE_MAJOR, index);

//*申请设备号*/
    if (device_major)
    {
        result = register_chrdev_region(devno, 1, "my_cdev");
    }
    else
    {
        result       = alloc_chrdev_region(&devno, 0, 1, "my_cdev");
        device_major = MAJOR(devno);
    }
    if (result < 0)
    {
        return result;
    }
    my_cdevp = kmalloc(sizeof(struct my_cdev), GFP_KERNEL);
    if (!my_cdevp)
    {
        result = -ENOMEM;
        goto fail_malloc;
    }
    memset(my_cdevp, 0, sizeof(struct my_cdev));
    my_cdev_setup(my_cdevp, 0);
    return 0;

 fail_malloc:
    unregister_chrdev_region(devno, 1);
    return result;
}

static void __exit my_cdev_exit(void)
{
	printk(KERN_NOTICE "my_cdev exit!");
    cdev_del(&my_cdevp->cdev);
    kfree(my_cdevp);
    unregister_chrdev_region(MKDEV(device_major, 0), 1);
}
MODULE_AUTHOR("Song Baohua");
MODULE_LICENSE("Dual BSD/GPL");
module_init(my_cdev_init);
module_exit(my_cdev_exit);
