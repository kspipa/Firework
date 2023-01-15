obj-m+=firemodule.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
	cd main_files/ && make
	cd modules/ && make
kernel_module:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
modules:
	cd modules/ && make
main_files:
	cd main_files/ && make
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module clean
	cd main_files/ && make clean
	cd modules/ && make clean
