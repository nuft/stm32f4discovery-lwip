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

#define LWIP_DEBUG

#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_ALL
#define LWIP_DBG_TYPES_ON               LWIP_DBG_ON
#define ETHARP_DEBUG                    LWIP_DBG_ON
#define NETIF_DEBUG                     LWIP_DBG_ON
#define PBUF_DEBUG                      LWIP_DBG_ON
#define API_LIB_DEBUG                   LWIP_DBG_ON
#define API_MSG_DEBUG                   LWIP_DBG_ON
#define SOCKETS_DEBUG                   LWIP_DBG_ON
#define ICMP_DEBUG                      LWIP_DBG_ON
#define IGMP_DEBUG                      LWIP_DBG_ON
#define INET_DEBUG                      LWIP_DBG_ON
#define IP_DEBUG                        LWIP_DBG_ON
#define IP_REASS_DEBUG                  LWIP_DBG_ON
#define RAW_DEBUG                       LWIP_DBG_ON
#define MEM_DEBUG                       LWIP_DBG_ON
#define MEMP_DEBUG                      LWIP_DBG_ON
#define SYS_DEBUG                       LWIP_DBG_ON
#define TIMERS_DEBUG                    LWIP_DBG_ON
#define TCP_DEBUG                       LWIP_DBG_ON
#define TCP_INPUT_DEBUG                 LWIP_DBG_ON
#define TCP_FR_DEBUG                    LWIP_DBG_ON
#define TCP_RTO_DEBUG                   LWIP_DBG_ON
#define TCP_CWND_DEBUG                  LWIP_DBG_ON
#define TCP_WND_DEBUG                   LWIP_DBG_ON
#define TCP_OUTPUT_DEBUG                LWIP_DBG_ON
#define TCP_RST_DEBUG                   LWIP_DBG_ON
#define TCP_QLEN_DEBUG                  LWIP_DBG_ON
#define UDP_DEBUG                       LWIP_DBG_ON
#define TCPIP_DEBUG                     LWIP_DBG_ON
#define PPP_DEBUG                       LWIP_DBG_ON
#define SLIP_DEBUG                      LWIP_DBG_ON
#define DHCP_DEBUG                      LWIP_DBG_ON
#define AUTOIP_DEBUG                    LWIP_DBG_ON
#define SNMP_MSG_DEBUG                  LWIP_DBG_ON
#define SNMP_MIB_DEBUG                  LWIP_DBG_ON
#define DNS_DEBUG                       LWIP_DBG_ON


#endif /* __LWIPOPT_H__ */
