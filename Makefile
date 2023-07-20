path = /home/$(shell whoami)/.firework
module_path = $(path)/modules
all:
	cargo build
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
clean:
	sudo rm -rf $(path)
	sudo rm -rf /usr/bin/frwk
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module clean
install:
	mkdir $(path) $(module_path)
	cp target/debug/Firework $(path)
	cp -r kernel_module $(path)
	sudo cp start.sh /usr/bin/frwk && sudo chmod o+x /usr/bin/frwk
	export FRWK_PATH=$(path)