#include <hal.h>
#include "usbcfg.h"
#include "lwip/sio.h"

/*
 * Implementation platform specific serial IO module needed for SLIP
 */

sio_fd_t sio_open(u8_t devnum)
{
    (void)devnum;
    return (void *)&SDU1;
}

void sio_send(u8_t c, sio_fd_t fd)
{
    streamPut((BaseChannel *)fd, c);
}

u8_t sio_recv(sio_fd_t fd)
{
    return streamGet((BaseChannel *)fd);
}

u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len)
{
    if (len > 0) {
        return chnRead((BaseChannel *)fd, data, len);
    }
    return 0;
}

u32_t sio_tryread(sio_fd_t fd, u8_t *data, u32_t len)
{
    if (len > 0) {
        return chnReadTimeout((BaseChannel *)fd, data, len, TIME_IMMEDIATE);
    }
    return 0;
}

u32_t sio_write(sio_fd_t fd, u8_t *data, u32_t len)
{
    if (len > 0) {
        return chnWrite((BaseChannel *)fd, data, len);
    }
    return 0;
}

void sio_read_abort(sio_fd_t fd)
{
    (void)fd;
    return;
}
