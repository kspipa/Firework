all:
	gcc getfromkernel.c -o getfromkernel -lnetfilter_queue -lmnl
start:
	sudo ./getfromkernel
clean:
	rm -rf getfromkernel