obj-m :=q1.o
KDIR = /lib/modules/$(shell uname -r)/build/
PWD = $(shell pwd)

MAKE:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -o application application.c
	gcc -o application_2 application_2.c
CLEAN:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf application
	rm -rf application_2


