#include <xs1.h>
#include <print.h>
#include <xscope.h>
#include "platform.h"
#include "ioserver/ioserver.h"
#include "ioserver/ioclient.h"
#include "ioloop.h"
#include "sysled.h"

/* apparently, port alias names from platform.h are only visible for port declarations... */
#undef LED_BLUE
#undef LED_GREEN
#undef LED_RED
#define LED_BLUE XS1_PORT_1K
#define LED_GREEN XS1_PORT_1L
#define LED_RED XS1_PORT_1M

on stdcore[3]: in port p_ifm_25m = XS1_PORT_1E;
on stdcore[3]: in port p_dummy = XS1_PORT_16A;
on stdcore[3]: clock clk = XS1_CLKBLK_1;

void estimate_frequency(clock clk, in port p_clk, in port p_dummy)
{
	int count;
	unsigned t1, t2;
	timer t;

	configure_clock_src(clk, p_clk);
	configure_in_port(p_dummy, clk);
	start_clock(clk);

	p_dummy :> void @ count;	// timestamped input
	t :> t1;					// save start time

	count += 25000;				// 25MHz quartz => 25000cycles/1ms

	p_dummy @ count :> void;	// timed input
	t :> t2;					// save end time

	printstr("Received 25000 cycles in ");
	printint(t2-t1);
	printstrln("0 ns (expected 1000000ns)\n");
}

int main(void) {
	chan c_com;
	chan c_ifm;
	chan c_led;

	par {
		on stdcore[0]: {
			xscope_register(0);
			xscope_config_io(XSCOPE_IO_BASIC);
		}
		on stdcore[3]: estimate_frequency(clk, p_ifm_25m, p_dummy);
		on stdcore[0]: ioserver(c_com);
		on stdcore[3]: ioserver(c_ifm);
		on stdcore[2]: {
			timer t;
			unsigned time;
			t :> time;

			init_ports_ifm(c_ifm);
			init_ports_com(c_com);

			// make sure all ports are Hi-Z/input
			count_ones_ifm(c_ifm);
			count_ones_com(c_com);

			// wait until estimate_frequency() has finished
			t when timerafter(time + 100000000) :> void;

			// write to com, read on ifm (1 bit at a time)
			cmp_com_to_ifm(c_com, c_ifm);

			// make sure all ports are Hi-Z/input
			count_ones_ifm(c_ifm);
			count_ones_com(c_com);

			// write to ifm, read on com (1 bit at a time)
			cmp_ifm_to_com(c_com, c_ifm);
		}
		on stdcore[1]: do_led(LED_RED, LED_GREEN, LED_BLUE);
	}
}
