obj-m :=hello.o
KDIR=/lib/modules/5.10.52-v7l+/build/
PWD=/rpi4/device-drivers/cross_compile/hello_module/
all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
