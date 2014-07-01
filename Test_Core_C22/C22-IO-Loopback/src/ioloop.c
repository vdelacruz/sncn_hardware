#include <print.h>
#include <channel.h>
#include "ioserver/ioclient.h"
#include "ioloop.h"
#include "ioloopback.h"

void init_ports_ifm(chanend_t c_server)
{
	for (int i=0; i<lbcon_size; i++) {
		io_port_init(c_server, lbcon[i].p_ifm);
	}
}

void init_ports_com(chanend_t c_server)
{
	for (int i=0; i<lbcon_size; i++) {
		io_port_init(c_server, lbcon[i].p_com);
	}
}

int count_ones_ifm(chanend_t c_server)
{
	int count = 0;
	int val;

	for (int i=0; i<lbcon_size; i++) {
		val = io_readbit(c_server, lbcon[i].p_ifm, lbcon[i].bitoffs_ifm);
		count += val;
	}
	return count;
}

int count_ones_com(chanend_t c_server)
{
	int count = 0;
	int val;

	for (int i=0; i<lbcon_size; i++) {
		val = io_readbit(c_server, lbcon[i].p_com, lbcon[i].bitoffs_com);
		count += val;
	}
	return count;
}

static char * get_portname(port_t p)
{
	int i=0;

	while(ports_used[i].id) {
		if (ports_used[i].id == p) {
			return ports_used[i].name;
		}
		i++;
	}
	return ports_used[i].name;
}

static void com_out_all_low(chanend_t c_server)
{
	for (int i=0; i<lbcon_size; i++) {
		io_clrbit(c_server, lbcon[i].p_com);
	}
}

static void ifm_out_all_low(chanend_t c_server)
{
	for (int i=0; i<lbcon_size; i++) {
		io_clrbit(c_server, lbcon[i].p_ifm);
	}
}

void cmp_com_to_ifm(chanend_t c_com, chanend_t c_ifm)
{
	int value;
	int count;
	int not_zero;

	printstr("\nDriving all COM ports low - # of 1's received on IFM: ");
	com_out_all_low(c_com);
	not_zero = count_ones_ifm(c_ifm);
	printint(not_zero);
	printstrln(" (expected 0)");

	for (int i=0; i<lbcon_size; i++) {
		if (io_readbit(c_ifm, lbcon[i].p_ifm, lbcon[i].bitoffs_ifm) != 0) {
			printstr("\tError: \"0\" not received on IFM Port P");
			printstr(get_portname(lbcon[i].p_ifm));
			printintln(lbcon[i].bitoffs_ifm);
		} else {
			printstr("+");
		}
	}

	for (int i=0; i<lbcon_size; i++) {
		io_setbit(c_com, lbcon[i].p_com, lbcon[i].bitoffs_com);
		value = io_readbit(c_ifm, lbcon[i].p_ifm, lbcon[i].bitoffs_ifm);
		count = count_ones_ifm(c_ifm);
		if (value != 1) {
			printstr("\n\tError: \"1\" not received on IFM Port P");
			printstr(get_portname(lbcon[i].p_ifm));
			//printstr(", offset=");
			printintln(lbcon[i].bitoffs_ifm);
		//} else if (count != 1) {
		//	printstr("# of 1's expected: 1 -- received: ");
		//	printintln(count);
		} else {
			printstr("+");
		}
		io_clrbit(c_com, lbcon[i].p_com);
	}
	printstrln("");
}

void cmp_ifm_to_com(chanend_t c_com, chanend_t c_ifm)
{
	int value;
	int count;
	int not_zero;

	printstr("\nDriving all IFM ports low - # of 1's received on COM: ");
	ifm_out_all_low(c_ifm);
	not_zero = count_ones_com(c_com);
	printint(not_zero);
	printstrln(" (expected 0)");

	for (int i=0; i<lbcon_size; i++) {
		if (io_readbit(c_com, lbcon[i].p_com, lbcon[i].bitoffs_com) != 0) {
			printstr("\tError: \"0\" not received on COM Port P");
			printstr(get_portname(lbcon[i].p_com));
			printintln(lbcon[i].bitoffs_com);
		} else {
			printstr("+");
		}
	}

	for (int i=0; i<lbcon_size; i++) {
		io_setbit(c_ifm, lbcon[i].p_ifm, lbcon[i].bitoffs_ifm);
		value = io_readbit(c_com, lbcon[i].p_com, lbcon[i].bitoffs_com);
		count = count_ones_com(c_com);
		if (value != 1) {
			printstr("\n\tError: \"1\" not received on COM Port P");
			printstr(get_portname(lbcon[i].p_com));
			//printstr(", offset=");
			printintln(lbcon[i].bitoffs_com);
		//} else if (count != 1) {
			//printstr("# of 1's expected: 1 -- received: ");
			//printintln(count);
		} else {
			printstr("+");
		}
		io_clrbit(c_ifm, lbcon[i].p_ifm);
	}
	printstrln("");
}
