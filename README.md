# packet_mangling
This is a kernel module that leverage netfilter framework in Linux kernel to modify the incoming ICMP packets.

![image](https://github.com/a110605/packet_mangling/blob/master/pictures/1.gif) 

## Netfilter Framework
Netfilter is a set of hooks inside Linux kernel.

It allows kernel modules to register callback functions with the network stack in order to intercept and manipulate the network packet.

Netfilter framework has 5 hooks point as picture shown below 
 
- NF_INET_PRE_ROUTING
- NF_INET_LOCAL_IN
- NF_INET_FORWARD
- NF_INET_LOCAL_OUT
- NF_INET_POST_ROUTING

![iamge](http://linux.vbird.org/linux_server/0250simple_firewall//iptables_04.gif)

When a registered function is called, it can intercept and modify the packet then return the corresponding value, as defined in **/include/uapi/linux/netfilter.h**,

- NF_ACCEPT: let the packet pass.
- NF_DROP: drop the packet.

- NF_STOLEN: take the packet and don’t let the packet pass.

- NF_QUEUE: queue the packet, usually for userspace handling.

- NF_REPEAT: call the hook again.


## Quick Start
Download and compile kernel module

```
# git clone https://github.com/a110605/packet_mangling.git
# cd packet_mangling/
# make 
# [sudo] insmod dropicmp.ko
```

You can test this module by using **ping** command on other computer.

```
# ping [IP of this linux]
``` 
You can see the destination IP of ICMP packets is modified to **1.2.3.4** by this kernel module.

(log in **/var/log/messages** or using **dmesg** command)

```
# dmesg -wH
```

Remove kernel module 

```
# [sudo] rmmod dropicmp
```

## References
- http://linux.vbird.org/linux_server/0250simple_firewall.php
- https://hn12303158.tian.yam.com/posts/41339037
- http://www.netfilter.org/
- http://www.roman10.net/2011/07/23/how-to-filter-network-packets-using-netfilterpart-2-implement-the-hook-function/



## Contact  
Please contact me via the mail [a1106052000@gmail.com](a1106052000@gmail.com)

Thanks.





