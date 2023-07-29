path = /home/$(shell whoami)/.firework
module_path = $(path)/modules
all:
	cargo build
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module modules
uninstall:
	sudo rm -rf $(path)
	sudo rm -rf /usr/bin/frwk
install:
	sudo python3 src/tools/useradd.py
	mkdir $(path) $(module_path)
	cp target/debug/Firework $(path)
	cp -r kernel_module $(path)
	cp -r src/moduleManager $(path)
	sudo chown firework:firework $(path) -R
	sudo chmod a+x $(path) -R
	sudo cp start.sh /usr/bin/frwk && sudo chmod o+x /usr/bin/frwk
	export FRWK_PATH=$(path)
clean:
	rm -rf target
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/kernel_module clean
debug:
	cargo build
	sudo insmod kernel_module/firemodule.ko
	sudo target/debug/Firework