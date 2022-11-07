#include <linux/module.h>
#include <linux/netfilter_ipv4.h> 
#include <linux/kernel.h>
#include <linux/init.h> 

MODULE_AUTHOR("pipa"); 
MODULE_DESCRIPTION("easy firewall");
MODULE_LICENSE("GPL");
static struct nf_hook_ops *nfho = NULL;

unsigned int hook_funcion(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    return NF_DROP;
}

static int __init hook_init(void)
{
    nfho = (struct nf_hook_ops*)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
    nfho->hook = (nf_hookfn*)hook_funcion;
    nfho->pf = NFPROTO_IPV4;
    nfho->hooknum = NF_INET_LOCAL_IN;
    nfho->priority = NF_IP_PRI_MANGLE;
    nf_register_net_hook(&init_net, nfho);
    printk("xmurp-ua start\n");
    return 0;
}

static void __exit hook_exit(void)
{
    nf_unregister_net_hook(&init_net, nfho);
    printk("xmurp-ua stop\n");
}

module_init(hook_init);
module_exit(hook_exit);