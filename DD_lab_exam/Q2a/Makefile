obj-m :=q2.o
KDIR = /lib/modules/$(shell uname -r)/build/
PWD = $(shell pwd)

MAKE:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o application application.c
	gcc -o ioctlapp ioctlapp.c 
CLEAN:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf application
	rm -rf ioctlapp
