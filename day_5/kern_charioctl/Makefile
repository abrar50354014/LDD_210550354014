obj-m := my_ioctl.o kern_add.o kern_sub.o kern_mul.o kern_div.o
KDIR= /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
MAKE:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o ioctlapp ioctlapp.c

CLEAN:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf  ioctlapp
	rm -rf /lib/modules/$(shell uname -r)/extra/*

INSTALL:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
	depmod -a

