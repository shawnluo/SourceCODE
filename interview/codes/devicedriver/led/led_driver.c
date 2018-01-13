#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/module.h>
#include <linux/device.h> 	//class_create

static struct class *firstdrv_class;
static struct device *firstdrv_device;

volatile unsigned long *gpbcon = NULL;
volatile unsigned long *gpbdat = NULL;

int major;
static int first_drv_open(struct inode * inode, struct file * filp)
{
	printk("first_drv_open\n");

	/*  LED1,LED2,LED3,LED4: GPB5,GPB6,GPB7,GPB8
	 *	set up GPB5,6,7,8 to output
	 */
	*gpbcon &= ~((0x3<<(5*2)) | (0x3<<(6*2)) | (0x3<<(7*2)) | (0x3<<(8*2)));
	*gpbcon |= ((0x1<<(5*2)) | (0x1<<(6*2)) | (0x1<<(7*2)) | (0x1<<(8*2)));
	return 0;
}
static int first_drv_write(struct file * file, const char __user * buffer, size_t count, loff_t * ppos)
{
	int val;
	printk("first_drv_write\n");

	copy_from_user(&val, buffer, count);

	if (val == 1)
	{
		// turn on
		*gpbdat &= ~((1<<5) | (1<<6) | (1<<7) | (1<<8));
	}
	else
	{
		// turn off
		*gpbdat |= (1<<5) | (1<<6) | (1<<7) | (1<<8);
	}
	return 0;
}

/* File operations struct for character device */
static const struct file_operations first_drv_fops = {
	.owner		= THIS_MODULE,
	.open		= first_drv_open,
	.write      = first_drv_write,
};

/* ?????? */
static int first_drv_init(void)
{
	major = register_chrdev(0, "first_drv", &first_drv_fops);

	firstdrv_class = class_create(THIS_MODULE, "firstdrv");

	firstdrv_device = device_create(firstdrv_class, NULL, MKDEV(major, 0), NULL, "xxx");

	gpbcon = (volatile unsigned long *)ioremap(0x56000010, 16);
	gpbdat = gpbcon + 1;
	
	return 0;
}

static void first_drv_exit(void)
{
	unregister_chrdev(major, "first_drv");
	device_unregister(firstdrv_device);  //???????
	class_destroy(firstdrv_class);		//???
	iounmap(gpbcon);					//????
}

module_init(first_drv_init);  //????????
module_exit(first_drv_exit);  //????????	

MODULE_AUTHOR("LWJ");
MODULE_DESCRIPTION("Just for Demon");
MODULE_LICENSE("GPL");  //??GPL??

