#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <libmnl/libmnl.h>
#include <linux/netfilter.h>
#include <linux/netfilter/nfnetlink.h>
#include <linux/types.h>
#include <linux/netfilter/nfnetlink_queue.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <linux/netfilter/nfnetlink_conntrack.h>
#include "checkrules.h"

static struct mnl_socket *nl;

static void nfq_send_verdict(int queue_num, uint32_t id)
{
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct nlattr *nest;
	nlh = nfq_nlmsg_put(buf, NFQNL_MSG_VERDICT, queue_num);
	nfq_nlmsg_verdict_put(nlh, id, NF_ACCEPT);
	nest = mnl_attr_nest_start(nlh, NFQA_CT);
	mnl_attr_put_u32(nlh, CTA_MARK, htonl(42));
	mnl_attr_nest_end(nlh, nest);
	mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);
}

static int queue_cb(const struct nlmsghdr *nlh, void *data)
{
	struct nlattr *attr[NFQA_MAX+1] = {};
	uint32_t id = 0;
	struct nfgenmsg *nfg;
	nfq_nlmsg_parse(nlh, attr);
	nfg = mnl_nlmsg_get_payload(nlh);
	struct nfqnl_msg_packet_hw *hw = mnl_attr_get_payload(attr[NFQA_HWADDR]);
	struct iphdr *ll;
	ll = (struct iphdr*) ( hw + ETH_HLEN );
	char* k = parse_ip(ll);
	printf("---------------------------------\n");
	printf("Source addr : %s\n", k);
	nfq_send_verdict(ntohs(nfg->res_id), id);
	return MNL_CB_OK;
}
static int start(char * argv[]){
	char *buf;
	size_t sizeof_buf = 0xffff + (MNL_SOCKET_BUFFER_SIZE/2);
	struct nlmsghdr *nlh;
	int ret;
	unsigned int portid, queue_num;
	queue_num = atoi(argv[1]);
	nl = mnl_socket_open(NETLINK_NETFILTER);
	mnl_socket_bind(nl, 0, MNL_SOCKET_AUTOPID);
	portid = mnl_socket_get_portid(nl);
	buf = malloc(sizeof_buf);
	nlh = nfq_nlmsg_put(buf, NFQNL_MSG_CONFIG, queue_num);
	nfq_nlmsg_cfg_put_cmd(nlh, AF_INET, NFQNL_CFG_CMD_BIND);
	mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);
	nlh = nfq_nlmsg_put(buf, NFQNL_MSG_CONFIG, queue_num);
	nfq_nlmsg_cfg_put_params(nlh, NFQNL_COPY_PACKET, 0xffff);
	mnl_attr_put_u32(nlh, NFQA_CFG_FLAGS, htonl(NFQA_CFG_F_GSO));
	mnl_attr_put_u32(nlh, NFQA_CFG_MASK, htonl(NFQA_CFG_F_GSO));
	mnl_socket_sendto(nl, nlh, nlh->nlmsg_len);
	ret = 1;
	mnl_socket_setsockopt(nl, NETLINK_NO_ENOBUFS, &ret, sizeof(int));

	for (;;) {
		ret = mnl_socket_recvfrom(nl, buf, sizeof_buf);
		ret = mnl_cb_run(buf, ret, 0, portid, queue_cb, NULL);
	}

	mnl_socket_close(nl);
	return 0;
}

int main(int argc, char *argv[])
{
	start(argv);
	return 0;
}