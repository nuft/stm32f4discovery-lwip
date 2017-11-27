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
    chThdSleepMilliseconds(10);
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


static void threads_profile(BaseSequentialStream *chp)
{
    static const char *states[] = {CH_STATE_NAMES};
    thread_t *tp;

    chprintf(chp,
             "stklimit    stack     addr refs prio     state       time         name\r\n");
    tp = chRegFirstThread();
    do {
#if (CH_DBG_ENABLE_STACK_CHECK == TRUE) || (CH_CFG_USE_DYNAMIC == TRUE)
        uint32_t stklimit = (uint32_t)tp->wabase;
#else
        uint32_t stklimit = 0U;
#endif
        chprintf(chp, "%08lx %08lx %08lx %4lu %4lu %9s %10lu %12s\r\n",
                 stklimit, (uint32_t)tp->ctx.sp, (uint32_t)tp,
                 (uint32_t)tp->refs - 1, (uint32_t)tp->prio, states[tp->state],
                 (uint32_t)tp->time, tp->name == NULL ? "" : tp->name);
        tp = chRegNextThread(tp);
    } while (tp != NULL);
}

void udp_rx_count_get(uint32_t *msg, uint32_t *bytes);
void udp_receive_start(void);

void profile_rx(BaseSequentialStream *chp)
{
    udp_receive_start();
    while (true) {
        uint32_t msg, byte;
        udp_rx_count_get(&msg, &byte); // reset
        chThdSleepMilliseconds(1000);
        udp_rx_count_get(&msg, &byte);
        chprintf(chp, "msg: %u, bytes: %u\n", msg, byte);
        threads_profile(chp);
    }
}

void udp_tx_count_get(uint32_t *msg, uint32_t *bytes);
void udp_transmit_thd(void *arg);
static THD_WORKING_AREA(udp_thd_wa, 2000);

void profile_tx(BaseSequentialStream *chp)
{
    chThdCreateStatic(udp_thd_wa, sizeof(udp_thd_wa), NORMALPRIO, udp_transmit_thd, NULL);

    while (true) {
        uint32_t msg, byte;
        udp_tx_count_get(&msg, &byte); // reset
        chThdSleepMilliseconds(1000);
        udp_tx_count_get(&msg, &byte);
        chprintf(chp, "msg: %u, bytes: %u\n", msg, byte);
        threads_profile(chp);
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
    ip_thread_init();

    /*
     * Creates the blinker thread.
     */
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    profile_tx((BaseSequentialStream *)&SD2);
    while (true) {
        chThdSleepMilliseconds(1000);
    }
}
