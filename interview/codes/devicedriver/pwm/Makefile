
ifneq  ($(KERNELRELEASE),)
obj-m:=beep.o
$(info "2nd")
else
#KDIR := /lib/modules/$(shell uname -r)/build
KDIR := /home/fs/linux/linux-3.14-fs4412
PWD:=$(shell pwd)
all:
	$(info "1st")
	make -C $(KDIR) M=$(PWD) modules
	arm-none-linux-gnueabi-gcc test.c -o beeptest
	sudo cp beep.ko beeptest /tftpboot
clean:
	rm -f *.ko *.o *.symvers *.mod.c *.mod.o *.order
endif


