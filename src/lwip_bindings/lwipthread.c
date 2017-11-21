#include <hal.h>
#include <lwip/netif.h>
#include <lwip/ip4.h>
#include <netif/slipif.h>
#include "lwipthread.h"

void ip_thread_init(void)
{
    ip_addr_t ip, gateway, netmask;
    static struct netif thisif;

    chRegSetThreadName("lwip");

#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    thisif.hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

    thisif.hwaddr[0] = LWIP_ETHADDR_0;
    thisif.hwaddr[1] = LWIP_ETHADDR_1;
    thisif.hwaddr[2] = LWIP_ETHADDR_2;
    thisif.hwaddr[3] = LWIP_ETHADDR_3;
    thisif.hwaddr[4] = LWIP_ETHADDR_4;
    thisif.hwaddr[5] = LWIP_ETHADDR_5;

    thisif.name[0] = 's';
    thisif.name[1] = 'l';

    LWIP_IPADDR(&ip);
    LWIP_NETMASK(&netmask);
    LWIP_GATEWAY(&gateway);

    netif_add(&thisif, &ip, &netmask, &gateway, NULL, slipif_init, ip4_input);

    netif_set_default(&thisif);
    netif_set_up(&thisif);
}
