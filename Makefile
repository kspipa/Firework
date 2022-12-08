obj-m+=gg.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=/home/pipa/Documents/Code/C/Firework/ggmodule modules
	gcc checkrules.c -o checkrules -lnetfilter_queue -lmnl
ggmodule:
	make -C /lib/modules/$(shell uname -r)/build M=/home/pipa/Documents/Code/C/Firework/ggmodule modules
checkrules:
	gcc checkrules.c -o checkrules -lnetfilter_queue -lmnl
clean:
	make -C /lib/modules/$(shell uname -r)/build M=/home/pipa/Documents/Code/C/Firework/ggmodule clean
	rm -rf checkrules