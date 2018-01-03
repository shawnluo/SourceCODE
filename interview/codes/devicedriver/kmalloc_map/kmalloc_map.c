/***********************************
 Copyright(C), 2013 LDP
 FileName:  kmalloc_map.c
 Author:    
 Date:          
 Description:  
 History:       
 Author       Date            Desc
************************************/
#include <linux/module.h>//MODULE_*
#include <linux/fs.h>//fops
#include <linux/cdev.h>//struct cdev
#include <linux/init.h>//printk
#include <linux/slab.h>//kzalloc() kfree()
#include <linux/mm.h>//struct vm_area_struct
#include <linux/io.h>

#include <asm/semaphore.h>//struct semaphore

#include "config.h"

#define DEV_NAME "kmalloc_map"

/*****************************************************
              module description 
*****************************************************/

MODULE_LICENSE("GPL");//GPL, GPL v2, GPL and additional rights, Dual BSD/GPL, Dual MPL/GPL, Proprietary.
MODULE_AUTHOR("...");
MODULE_DESCRIPTION("...");
MODULE_VERSION("...");
MODULE_ALIAS("...");

struct LDP_kmalloc_map
{
    struct cdev kmalloc_map_cdev;
    struct semaphore kmalloc_map_sem;
    char *buffer;
};

static int kmalloc_map_major = 0;
module_param(kmalloc_map_major, int, S_IRUGO);

static int kmalloc_map_minor = 0;
module_param(kmalloc_map_minor, int, S_IRUGO);

static char *msg = "My name is WangXiaoLu. I love linux forever!\n";
module_param(msg, charp, S_IRUGO);

static int kmalloc_map_open(struct inode *inode, struct file *filp)
{
    filp->private_data = container_of(inode->i_cdev, struct LDP_kmalloc_map, kmalloc_map_cdev);

    return nonseekable_open(inode, filp);//no seek
}

static int kmalloc_map_close(struct inode *inode, struct file *filp)
{
    //struct LDP_kmalloc_map *kmalloc_map_devp = (struct LDP_kmalloc_map *)filp->private_data;

    filp->private_data = NULL;

    return 0;
}

void kmalloc_map_vma_open(struct vm_area_struct *vma) //vma打开函数
{
    //printk(KERN_NOTICE "virt %1x, phys %1x\n", vma->vm_start, vma->vm_pgoff << PAGE_SHIFT);
}
    
void kmalloc_map_vma_close(struct vm_area_struct *vma) //vma关闭函数
{
}

#ifdef USE_NOPAGE
struct page *kmalloc_map_vma_nopage(struct vm_area_struct *vma, unsigned long address, int *type)
{
    struct LDP_kmalloc_map *kmalloc_map_devp = vma->vm_private_data;
    struct page *pageptr = NOPAGE_SIGBUS;
    unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
    unsigned long phyaddr = address - vma->vm_start + offset;//物理地址
    unsigned long pageframe = phyaddr >> PAGE_SHIFT;//页帧号
       
#if 0
    if (!pfn_valid(pageframe))
    {
        goto out;//页帧号无效
    }
        
    pageptr = pfn_to_page(pageframe);
#endif
    if (pageframe >= PAGE_NUM)
    {
        goto out;
    }

    pageptr = virt_to_page(kmalloc_map_devp->buffer + phyaddr);

    get_page(pageptr);//获得页，实际是增加页的使用计数
    if (type)
    {
        *type = VM_FAULT_MINOR;
    }
    
out:
    printk("offset = %ld\n", offset);
        
    return pageptr;
    //返回一个页描述符，可用于扩大或缩小映射的内存区域。
}
#endif

static struct vm_operations_struct kmalloc_map_remap_vm_ops =
{
    .open = kmalloc_map_vma_open,
    .close = kmalloc_map_vma_close,
#ifdef USE_NOPAGE
    .nopage = kmalloc_map_vma_nopage,
#endif
};

static int kmalloc_map_mmap(struct file *filp, struct vm_area_struct *vma)
{
    struct LDP_kmalloc_map *kmalloc_map_devp = (struct LDP_kmalloc_map *)filp->private_data;
#ifdef USE_REMAP_PFN_RANGE
    unsigned long size = (unsigned long)(vma->vm_end - vma->vm_start);
#endif
    signed int ret = 0;

    printk("%ld, %ld\n%d, %d\n", vma->vm_end, vma->vm_start, PAGE_SHIFT,  BUF_SIZE);

    down(&kmalloc_map_devp->kmalloc_map_sem);
#ifdef USE_REMAP_PFN_RANGE
    if (size > BUF_SIZE)
    {
        ret = -EINVAL;
    
        goto fail;
    }

    vma->vm_pgoff = ((unsigned long)kmalloc_map_devp->buffer) >> PAGE_SHIFT;
    if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size, vma->vm_page_prot))
    {
        ret = -EAGAIN;
   
        goto fail;
    }
#endif

#ifdef USE_NOPAGE
    if ((vma->vm_pgoff << PAGE_SHIFT) >= __pa(high_memory) || (filp->f_flags & O_SYNC))
    {
        vma->vm_flags |= VM_IO;
    }

    vma->vm_flags |= VM_RESERVED;
    vma->vm_private_data = kmalloc_map_devp;
#endif 
    vma->vm_ops = &kmalloc_map_remap_vm_ops;
    kmalloc_map_vma_open(vma);

#ifdef USE_REMAP_PFN_RANGE
fail:
#endif 

    up(&kmalloc_map_devp->kmalloc_map_sem);

    return ret;
}

struct file_operations kmalloc_map_fops =
{
    .owner = THIS_MODULE,
    .open = kmalloc_map_open,
    .release = kmalloc_map_close,
    .mmap = kmalloc_map_mmap,
};

static struct LDP_kmalloc_map *kmalloc_map_dev;

static int __init kmalloc_map_init(void)
{
    int ret = 0;
    struct page *page = NOPAGE_SIGBUS;

    kmalloc_map_dev = kzalloc(sizeof(struct LDP_kmalloc_map), GFP_KERNEL);
    if (kmalloc_map_dev == NULL)
    {
        ret = -ENOMEM;

        goto fail3;
    }

    cdev_init(&kmalloc_map_dev->kmalloc_map_cdev, &kmalloc_map_fops);
    kmalloc_map_dev->kmalloc_map_cdev.owner = THIS_MODULE;
    kmalloc_map_dev->kmalloc_map_cdev.ops = &kmalloc_map_fops;

    init_MUTEX(&kmalloc_map_dev->kmalloc_map_sem);

    if (kmalloc_map_major && kmalloc_map_minor)
    {
        kmalloc_map_dev->kmalloc_map_cdev.dev = MKDEV(kmalloc_map_major, kmalloc_map_minor);
        ret = register_chrdev_region(kmalloc_map_dev->kmalloc_map_cdev.dev, 1, DEV_NAME);
    }
    else
    {
        ret = alloc_chrdev_region(&kmalloc_map_dev->kmalloc_map_cdev.dev, 0, 1, DEV_NAME);
    }
    if (ret < 0)
    {
        goto fail2;
    }

    printk(KERN_INFO "mknod /dev/%s %c %d %d\n", DEV_NAME, 'c', MAJOR(kmalloc_map_dev->kmalloc_map_cdev.dev), MINOR(kmalloc_map_dev->kmalloc_map_cdev.dev));

    ret = cdev_add(&kmalloc_map_dev->kmalloc_map_cdev, kmalloc_map_dev->kmalloc_map_cdev.dev, 1);
    if (ret < 0)
    {
        goto fail1;
    }

    kmalloc_map_dev->buffer = kmalloc(BUF_SIZE, GFP_KERNEL);

    if (kmalloc_map_dev->buffer == NULL)
    {
        goto fail0;
    }

    sprintf(kmalloc_map_dev->buffer, msg);

    for (page = virt_to_page(kmalloc_map_dev->buffer); page < virt_to_page(kmalloc_map_dev->buffer + BUF_SIZE); page++)
    {
        SetPageReserved(page);
    }

    return ret;

fail0:
    cdev_del(&kmalloc_map_dev->kmalloc_map_cdev);
fail1:
    unregister_chrdev_region(kmalloc_map_dev->kmalloc_map_cdev.dev, 1);
fail2:
    kfree(kmalloc_map_dev);
fail3:
    return ret;
}

static void __exit kmalloc_map_exit(void)
{
    struct page *page;
   
    for (page = virt_to_page(kmalloc_map_dev->buffer); page < virt_to_page(kmalloc_map_dev->buffer + BUF_SIZE); page++)
    {
        ClearPageReserved(page);
    }

    kfree(kmalloc_map_dev->buffer); 
    unregister_chrdev_region(kmalloc_map_dev->kmalloc_map_cdev.dev, 1);
    cdev_del(&kmalloc_map_dev->kmalloc_map_cdev);
    kfree(kmalloc_map_dev);
}

module_init(kmalloc_map_init);
module_exit(kmalloc_map_exit);


