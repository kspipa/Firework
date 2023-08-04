path = /home/$(shell whoami)/.firework
module_path = $(path)/modules
all:
	cargo build
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
clean:
	rm -rf target
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module clean
debug:
	cargo build
	sudo insmod kernel_module/firemodule.ko
	sudo target/debug/Firework