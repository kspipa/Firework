all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module_in modules
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module_out modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module_in clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module_out clean