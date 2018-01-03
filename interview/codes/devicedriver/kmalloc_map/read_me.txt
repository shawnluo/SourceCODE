功能简介：在内存中声请一段内存，写入内容；在用户态用mmap把这段内存映射到用户空间，读出内容。

1.本驱动调试环境（其它环境还没调试）
    .硬件arm926
    .软件linux-2.6.24

2.在config.h中选择nopage或remap_pfn_range(默认remap_pfn_range)。

3.没有提供Makefile。

4.mmap_test.c是用户空间的测试程序。(编译命令：XXXXX-gcc -o mmap_test mmap_test)

5.装载kmalloc_map：
     .指定设备号：insmod kmalloc_map.ko kmalloc_map_major=XXXXX(0~255) kmalloc_map_minor=XXXXX(0~255) msg="XXXXX"
	 (目前没有对msg的长度做判断，strlen(msg) <= BUF_SIZE(config.h定义，默认一页))
     .自动获取设备号：insmod kmalloc_map.ko 
	 (默认msg="My name is WangXiaoLu. I love linux forever!\n");

6.装载之后执行 # mknod /dev/kmalloc_map c XXXXX(0~255) XXXXX(0~255)
               # ./a
			   在最后一行看到XXXXX
			   
			   
			   
/*=====			   
ioremap是将物理地址转换为虚拟地址

mmap是将设备内存线性地址映射到用户地址空间

linux的线程只能访问虚拟地址，不管是不是内核，ioremap应用，比如有个寄存器地址是0xe8000000
你要用ioremap映射后，才能访问地址0xe8000000。这两个地址是不同的，mmu会帮你搞定，对你是透明的

mmap在内核我用过ops中的mmap方法
我写过一个例程，见附件。里面还有用户态的测试程序。

有什么问题，可以加入我们群，问题会更快得到回复！
群号：163617970
============*/