obj-m+=firemodule.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
	gcc getfromkernel.c -o getfromkernel -lnetfilter_queue -lmnl
ggmodule:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
checkrules:
	gcc getfromkernel.c -o getfromkernel -lnetfilter_queue -lmnl
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module clean
	rm -rf getfromkernel