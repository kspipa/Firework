#include <stdio.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>		
#include "../lib/tools.h"
#include "../lib/api.h"

int sock = 0;
static struct sockaddr_in serv_addr;
static struct send_from_module *init_kernel_module;
static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data)
{
    u_int32_t id;
	struct nfqnl_msg_packet_hw *hw = nfq_get_packet_hw(nfa);
    struct nfqnl_msg_packet_hdr *ph;
	if (send(sock, hw, sizeof(hw), 0) < 0){
        printf("Cant send\n");
    }
    else{
        printf("Can send!!\n");
    }
	ph = nfq_get_msg_packet_hdr(nfa);	
	id = ntohl(ph->packet_id);
	printf("entering callback\n");
	return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
}

int main(int argc, char **argv)
{
	struct nfq_handle *h;
	struct nfq_q_handle *qh;
	int fd;
	int rv;
	char buf[4096] __attribute__ ((aligned));
	sock = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        printf("Cant connect to server\n");
    else
        printf("Connect!\n");
	init_kernel_module->command = 1;
	init_kernel_module->module_name->name = "kernel_module";
	init_kernel_module->module_name->sock = sock;
	init_module(init_kernel_module);
	printf("opening library handle\n");
	h = nfq_open();
	nfq_unbind_pf(h, AF_INET);
	printf("binding nfnetlink_queue as nf_queue handler for AF_INET\n");
	nfq_bind_pf(h, AF_INET);
	printf("binding this socket to queue '0'\n");
	qh = nfq_create_queue(h,  0, &cb, NULL);
	printf("setting copy_packet mode\n");
	nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff);
	fd = nfq_fd(h);

	while ((rv = recv(fd, buf, sizeof(buf), 0)))
	{
		printf("pkt received\n");
		nfq_handle_packet(h, buf, rv);
	}

	printf("unbinding from queue 0\n");
	nfq_destroy_queue(qh);

#ifdef INSANE
	printf("unbinding from AF_INET\n");
	nfq_unbind_pf(h, AF_INET);
#endif

	printf("closing library handle\n");
	nfq_close(h);

	exit(0);
}