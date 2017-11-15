/**
 * @file
 *
 * lwIP Options Configuration
 */

#ifndef __LWIPOPT_H__
#define __LWIPOPT_H__

#define LWIP_DBG_TYPES_ON   LWIP_DBG_ON
#define LWIP_COMPAT_MUTEX_ALLOWED

/* See lwip/src/include/lwip/opt.h for reference. */
#define MEM_ALIGNMENT                   4

#define NO_SYS                          0
#define LWIP_ETHERNET                   0
#define LWIP_ARP                        0
#define PPPOE_SUPPORT                   0

#define LWIP_IPV4                       1
#define LWIP_IPV6                       0

#define LWIP_UDP                        1
#define LWIP_TCP                        0
#define LWIP_SOCKET                     0
#define LWIP_ICMP                       1
#define LWIP_DHCP                       0

#define DEFAULT_THREAD_STACK_SIZE       4096
#define DEFAULT_RAW_RECVMBOX_SIZE       4
#define DEFAULT_UDP_RECVMBOX_SIZE       4
#define DEFAULT_ACCEPTMBOX_SIZE         4

#define LWIP_IPADDR(p)  IP4_ADDR(p, 192, 168, 3, 20)
#define LWIP_GATEWAY(p) IP4_ADDR(p, 192, 168, 3, 1)
#define LWIP_NETMASK(p) IP4_ADDR(p, 255, 255, 255, 0)

#define LWIP_HAVE_SLIPIF                1
#define SLIP_USE_RX_THREAD              1

#define SLIPIF_THREAD_NAME              "slipif_loop"
#define SLIPIF_THREAD_PRIO              (LOWPRIO + 1)
#define SLIPIF_THREAD_STACKSIZE         1024

/** Use newlib malloc() instead of memory pools. */
#include <stdlib.h>
#define MEM_LIBC_MALLOC 1
#define MEMP_MEM_MALLOC 1

#endif /* __LWIPOPT_H__ */
