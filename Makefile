obj-m+=firemodule.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
	cd main_files/ && make
kernel_module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
main_files:
	cd main_files/ && make
start:
	sudo insmod kernel_module/firemodule.ko
	cd main_files/ && make start
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module clean
	cd main_files/ && make clean
