#include <string.h>
#include <lwip/api.h>

void message_transmit(uint8_t *input_buffer, size_t input_buffer_size, ip_addr_t *addr, uint16_t port)
{
    struct netconn *conn;
    struct netbuf *buf;

    conn = netconn_new(NETCONN_UDP);

    if (conn == NULL) {
        // TODO: Do something useful
        return;
    }

    buf = netbuf_new();

    if (buf == NULL) {
        // TODO: Do something useful
        return;
    }

    netbuf_ref(buf, input_buffer, input_buffer_size);

    netconn_sendto(conn, buf, addr, port);

    netbuf_delete(buf);
    netconn_delete(conn);
}


void send_hello_world(void)
{
    ip_addr_t server;
    // server.addr = (IP_ADDR_BROADCAST)->addr;
    LWIP_GATEWAY(&server);
    uint16_t port = 5555;
    char *msg = "hello world!\n";

    message_transmit((uint8_t *)msg, strlen(msg), &server, port);
}
