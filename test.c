#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netlink.h>
#include <net/netlink.h>
#include <net/net_namespace.h>

/* Protocol family, consistent in both kernel prog and user prog. */
#define MYPROTO NETLINK_USERSOCK
/* Multicast group, consistent in both kernel prog and user prog. */
#define MYGRP 21

static struct sock *nl_sk = NULL;

static void send_to_user(struct sk_buff *negr)
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
    nlh->nlmsg_type = (__u16)skb;

    pr_info("Sending skb.\n");
    res = nlmsg_multicast(nl_sk, skb, 0, MYGRP, GFP_KERNEL);
    if (res < 0)
        pr_info("nlmsg_multicast() error: %d\n", res);
    else
        pr_info("Success.\n");
}

static int __init hello_init(void)
{
    pr_info("Inserting hello module.\n");

    nl_sk = netlink_kernel_create(&init_net, MYPROTO, NULL);
    if (!nl_sk) {
        pr_err("Error creating socket.\n");
        return -10;
    }

    send_to_user();

    netlink_kernel_release(nl_sk);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Exiting hello module.\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");