#include <linux/module.h>
#include <linux/netfilter_ipv4.h> 
#include <linux/kernel.h>
#include <linux/init.h> 

MODULE_AUTHOR("pipa"); 
MODULE_DESCRIPTION("easy firewall");
MODULE_LICENSE("GPL"); 

static unsigned int accepted_num; 
static unsigned int dropped_num; 

// hook functions 
static struct nf_hook_ops nfho_forward; 
static struct nf_hook_ops nfho_out; 
static struct nf_hook_ops nfho_in; 
struct net *neger;
// hook out packets 
unsigned int hook_func_out(void *priv,struct sk_buff *skb, const struct nf_hook_state *state) {
 	printk("Get output packet, accept\n");
 	accepted_num++;
 	return NF_ACCEPT; 
} 

unsigned int hook_func_in(void *priv,struct sk_buff *skb, const struct nf_hook_state *state) {
 	printk("Get input packet, accept\n");
 	accepted_num++;
 	return NF_ACCEPT;
} 

// hook forward packets 
unsigned int hook_func_forward(void *priv,struct sk_buff *skb, const struct nf_hook_state *state) {
 	printk("Get forward packet, drop\n");
 	dropped_num++;
 	return NF_DROP;
} 

static int __init fw_module_init(void) {
 	printk("Starting FW module loading\n");
 	accepted_num = 0;
 	dropped_num = 0;
	nfho_in.hook = hook_func_in;
 	nfho_in.hooknum = NF_INET_LOCAL_IN;
 	nfho_in.pf = PF_INET;
 	nfho_in.priority = NF_IP_PRI_FIRST;
 	nf_register_net_hook(neger, &nfho_in); // Register the hook 
	nfho_out.hook = hook_func_out;
 	nfho_out.hooknum = NF_INET_LOCAL_OUT;
 	nfho_out.pf = PF_INET;
 	nfho_out.priority = NF_IP_PRI_FIRST;
 	nf_register_net_hook(neger, &nfho_out); // Register the hook 
	nfho_forward.hook = hook_func_forward;
 	nfho_forward.hooknum = NF_INET_FORWARD;
 	nfho_forward.pf = PF_INET;
 	nfho_forward.priority = NF_IP_PRI_FIRST;
 	nf_register_net_hook(neger, &nfho_forward);  // Register the hook 
	return 0; 
} 

static void __exit fw_module_exit(void) 
{
 	printk("Removing FW module\n"); 
	nf_unregister_net_hook(neger, &nfho_in);
 	nf_unregister_net_hook(neger, &nfho_out);
 	nf_unregister_net_hook(neger, &nfho_forward); 
} 

module_init( fw_module_init); 
module_exit( fw_module_exit); 