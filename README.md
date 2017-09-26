# packet_mangling
This is a kernel module that leverage netfilter framework in Linux kernel to modify the incoming ICMP packets.

![image](https://github.com/a110605/packet_mangling/blob/master/pictures/1.gif) 
## Netfilter Framework


## Quick Start
Download and compile kernel module

```
# cd packet_mangling/
# make 
# [sudo] insmod dropicmp.ko
```

You can test this module by using **ping** command on other computer.

```
# ping [IP of this linux]
``` 
You can see the destination IP of ICMP packets is modified to 1.2.3.4 by this kernel module
(log in **/var/log/messages** or using **dmesg** command)

```
# dmesg -wH
```

Remove kernel module 

```
# [sudo] rmmod dropicmp
```

## Contact  
Please contact me via the mail [a1106052000@gmail.com](a1106052000@gmail.com)

Thanks.





