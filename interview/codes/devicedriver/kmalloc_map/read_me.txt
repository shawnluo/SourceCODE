���ܼ�飺���ڴ�������һ���ڴ棬д�����ݣ����û�̬��mmap������ڴ�ӳ�䵽�û��ռ䣬�������ݡ�

1.���������Ի���������������û���ԣ�
    .Ӳ��arm926
    .���linux-2.6.24

2.��config.h��ѡ��nopage��remap_pfn_range(Ĭ��remap_pfn_range)��

3.û���ṩMakefile��

4.mmap_test.c���û��ռ�Ĳ��Գ���(�������XXXXX-gcc -o mmap_test mmap_test)

5.װ��kmalloc_map��
     .ָ���豸�ţ�insmod kmalloc_map.ko kmalloc_map_major=XXXXX(0~255) kmalloc_map_minor=XXXXX(0~255) msg="XXXXX"
	 (Ŀǰû�ж�msg�ĳ������жϣ�strlen(msg) <= BUF_SIZE(config.h���壬Ĭ��һҳ))
     .�Զ���ȡ�豸�ţ�insmod kmalloc_map.ko 
	 (Ĭ��msg="My name is WangXiaoLu. I love linux forever!\n");

6.װ��֮��ִ�� # mknod /dev/kmalloc_map c XXXXX(0~255) XXXXX(0~255)
               # ./a
			   �����һ�п���XXXXX
			   
			   
			   
/*=====			   
ioremap�ǽ������ַת��Ϊ�����ַ

mmap�ǽ��豸�ڴ����Ե�ַӳ�䵽�û���ַ�ռ�

linux���߳�ֻ�ܷ��������ַ�������ǲ����ںˣ�ioremapӦ�ã������и��Ĵ�����ַ��0xe8000000
��Ҫ��ioremapӳ��󣬲��ܷ��ʵ�ַ0xe8000000����������ַ�ǲ�ͬ�ģ�mmu�����㶨��������͸����

mmap���ں����ù�ops�е�mmap����
��д��һ�����̣������������滹���û�̬�Ĳ��Գ���

��ʲô���⣬���Լ�������Ⱥ����������õ��ظ���
Ⱥ�ţ�163617970
============*/