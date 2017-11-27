#include <string.h>
#include <lwip/udp.h>
#include <lwip/ip.h>

uint32_t udp_rx_msg_count = 0;
uint32_t udp_rx_byte_count = 0;

void udp_rx_count_get(uint32_t *msg, uint32_t *bytes)
{
    chSysLock();
    *msg = udp_rx_msg_count;
    *bytes = udp_rx_byte_count;
    udp_rx_msg_count = 0;
    udp_rx_byte_count = 0;
    chSysUnlock();
}

void msg_cb(void *arg,
            struct udp_pcb *pcb,
            struct pbuf *p,
            const ip_addr_t *addr,
            uint16_t port)
{
    (void)arg;
    (void)pcb;
    (void)addr;
    (void)port;
    chSysLock();
    udp_rx_byte_count += p->tot_len;
    udp_rx_msg_count += 1;
    chSysUnlock();
}

void udp_receive_start(void)
{
    chRegSetThreadName(__FUNCTION__);

    struct udp_pcb *pcb;
    pcb =  udp_new();

    udp_bind(pcb, IP_ADDR_ANY, 5555);

    udp_recv(pcb, msg_cb, NULL);
}


uint32_t udp_tx_msg_count = 0;
uint32_t udp_tx_byte_count = 0;

void udp_tx_count_get(uint32_t *msg, uint32_t *bytes)
{
    chSysLock();
    *msg = udp_tx_msg_count;
    *bytes = udp_tx_byte_count;
    udp_tx_msg_count = 0;
    udp_tx_byte_count = 0;
    chSysUnlock();
}

void udp_transmit_thd(void *arg)
{
    (void) arg;

    chRegSetThreadName(__FUNCTION__);

    struct udp_pcb *pcb;
    pcb =  udp_new();

    ip_addr_t server;
    LWIP_GATEWAY(&server);

    udp_connect(pcb, &server, 5555);

    const char *msg = "123456789\n";
    struct pbuf *p;
    const size_t length = strlen(msg);
    p = pbuf_alloc(PBUF_TRANSPORT, length, PBUF_REF);
    ((struct pbuf_rom*)p)->payload = msg;

    while (1) {
        udp_send(pcb, p);
        chSysLock();
        udp_tx_msg_count += 1;
        udp_tx_byte_count += length;
        chSysUnlock();
    }
}
