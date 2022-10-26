#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/ip.h>
#include <linux/inet.h>
#include <linux/version.h>

#define DIP "1.2.3.4"


static struct nf_hook_ops nfho;     // net filter hook option struct
struct sk_buff* sock_buff;          // socket buffer used in linux kernel
struct udphdr* udp_header;          // udp header struct (not used)
struct iphdr* ip_header;            // ip header struct
struct ethhdr* mac_header;          // mac header struct
struct net* n;						// net struct



MODULE_DESCRIPTION("Redirect_Packet");
MODULE_AUTHOR("Andy Lee <a1106052000 AT gmail.com>");
MODULE_LICENSE("GPL");

unsigned int hook_func(void* priv, struct sk_buff* skb, const struct nf_hook_state* state)

{

	sock_buff = skb;
	ip_header = (struct iphdr*)skb_network_header(sock_buff); //grab network header using accessor
	mac_header = (struct ethhdr*)skb_mac_header(sock_buff);

	if (!sock_buff) { return NF_DROP; }

	if (ip_header->protocol == IPPROTO_ICMP) { //icmp=1 udp=17 tcp=6
		printk(KERN_INFO "Got ICMP Reply packet and dropped it. \n");     //log we’ve got udp packet to /var/log/messages
		printk(KERN_INFO "src_ip: %pI4 \n", &ip_header->saddr);
		printk(KERN_INFO "dst_ip: %pI4\n", &ip_header->daddr);
		ip_header->daddr = in_aton(DIP);
		printk(KERN_INFO "modified_dst_ip: %pI4\n", &ip_header->daddr);
	
	}
	return NF_ACCEPT;
}

int init_module()
{
	nfho.hook = hook_func;
	nfho.hooknum = 4; //NF_IP_PRE_ROUTING=0(capture ICMP Request.)  NF_IP_POST_ROUTING=4(capture ICMP reply.)
	nfho.pf = PF_INET;//IPV4 packets
	nfho.priority = NF_IP_PRI_FIRST;//set to highest priority over all other hook functions
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,13,0)
	for_each_net(n) { nf_register_net_hook(&init_net, &nfho); } //register hook depending on version
#else
	nf_register_hook(&nfho);
#endif
	printk(KERN_INFO "---------------------------------------\n");
	printk(KERN_INFO "Loading dropicmp kernel module...\n");
	return 0;
}



void cleanup_module()
{
	printk(KERN_INFO "Cleaning up dropicmp module.\n");
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,13,0)
	for_each_net(n) { nf_unregister_net_hook(&init_net, &nfho); } //unregister hook depending on version
#else
	nf_register_hook(&nfho);
#endif
}