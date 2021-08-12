obj-m :=kern_calperm.o kern_add.o kern_sub.o kern_mul.o kern_div.o
KDIR=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/*

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
	depmod -a

