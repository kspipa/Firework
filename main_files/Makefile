all:
	gcc getfromkernel.c -o getfromkernel -lnetfilter_queue -lmnl
	gcc distribution_center.c -o distribution_center
start:
	./distribution_center | ./getfromkernel
clean:
	rm -rf distribution_center
	rm -rf getfromkernel