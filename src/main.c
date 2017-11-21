#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include "usbcfg.h"
#include "lwipthread.h"

#include <lwip/netif.h>
#include <lwip/dhcp.h>

#include <stdarg.h>
#include <stdio.h>

void lwip_printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}


static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg)
{
    (void)arg;
    chRegSetThreadName("blinker");
    while (true) {
        palSetPad(GPIOD, GPIOD_LED3);   /* Orange.  */
        chThdSleepMilliseconds(500);
        palClearPad(GPIOD, GPIOD_LED3); /* Orange.  */
        chThdSleepMilliseconds(500);
    }
}


int main(void)
{
    halInit();
    chSysInit();

    /*
     * Activates the serial driver 2 using the driver default configuration.
     * PA2(TX) and PA3(RX) are routed to USART2.
     */
    static const SerialConfig serial_config =
    {
        115200,
        0,
        USART_CR2_STOP1_BITS,
        0
    };
    sdStart(&SD2, &serial_config);
    palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));

    chprintf((BaseSequentialStream *)&SD2, "\nboot\n");

    /*
     * Initializes a serial-over-USB CDC driver.
     */
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1500);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);


    chThdSleepMilliseconds(1000);
    /*
     * Start IP over SLIP
     */
    struct netif *netif;
    ip_thread_init();
    netif = netif_find("sl0");

    /*
     * Creates the blinker thread.
     */
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    while (true) {
        chThdSleepMilliseconds(1000);
    }
}
