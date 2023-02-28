all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/src/kernel_module modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/src/kernel_module clean