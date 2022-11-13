#include <linux/module.h>
#include <linux/netfilter_ipv4.h> 
#include <linux/kernel.h>
#include <linux/init.h> 
#include <linux/netlink.h>
#include <net/netlink.h>
#include <net/net_namespace.h>

MODULE_AUTHOR("pipa"); 
MODULE_DESCRIPTION("easy firewall");
MODULE_LICENSE("GPL");

/* Protocol family, consistent in both kernel prog and user prog. */
#define MYPROTO NETLINK_USERSOCK
/* Multicast group, consistent in both kernel prog and user prog. */
#define MYGRP 21


static struct sock *nl_sk = NULL;

static void send_to_user(struct sk_buff *skbf)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlh;
    char *msg = "Hello from kernel";
    int msg_size = strlen(msg) + 1;
    int res;

    pr_info("Creating skb.\n");
    skb = nlmsg_new(NLMSG_ALIGN(msg_size + 1), GFP_KERNEL);
    if (!skb) {
        pr_err("Allocation failure.\n");
        return;
    }

    nlh = nlmsg_put(skb, 0, 1, NLMSG_DONE, msg_size + 1, 0);
    nlh->nlmsg_type = (__u16)skbf;

    pr_info("Sending skb.\n");
    res = nlmsg_multicast(nl_sk, skb, 0, MYGRP, GFP_KERNEL);
    if (res < 0)
        pr_info("nlmsg_multicast() error: %d\n", res);
    else
        pr_info("Success.\n");
}


static struct nf_hook_ops *nfho = NULL;

unsigned int hook_funcion(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    send_to_user(skb);
    return NF_DROP;
}

static int __init hook_init(void)
{
    nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
    nfho->hook = (nf_hookfn*)hook_funcion;
    nfho->pf = NFPROTO_IPV4;
    nfho->hooknum = NF_INET_LOCAL_IN;
    nfho->priority = NF_IP_PRI_MANGLE;
    nl_sk = netlink_kernel_create(&init_net, MYPROTO, NULL);
    nf_register_net_hook(&init_net, nfho);
    printk("xmurp-ua start\n");
    return 0;
}

static void __exit hook_exit(void)
{
    nf_unregister_net_hook(&init_net, nfho);
    netlink_kernel_release(nl_sk);
    printk("xmurp-ua stop\n");
}

module_init(hook_init);
module_exit(hook_exit);