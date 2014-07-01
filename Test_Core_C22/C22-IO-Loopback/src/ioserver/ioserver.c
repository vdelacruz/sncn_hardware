#include <stdint.h>
#include <channel.h>
#include <port.h>
#include <print.h>
#include "ioserver.h"

static uint8_t in_bit(port_t p_in, uint8_t offs)
{
	uint8_t data;

	port_in(p_in, data);
	data >>= offs;
	data &= 0x01;

	return data;
}

static void set_bit(port_t p_out, uint8_t offs)
{
	port_out(p_out, (0x01 << offs))
}

static void clr_bit(port_t p_out)
{
	port_out(p_out, 0x00);
}

void ioserver(chanend_t c)
{
	int cmd;
	int port, offs;
	int data;

	while(1) {
		chan_in_int(c, cmd);
		switch (cmd) {
		case PORTINIT:
			chan_in_int(c, port);
			port_init(port, port);
			break;
		case SETBIT:
			chan_in_int(c, port);
			chan_in_int(c, offs);
			set_bit(port, offs);
			break;
		case CLRBIT:
			chan_in_int(c, port);
			clr_bit(port);
			break;
		case READBIT:
			chan_in_int(c, port);
			chan_in_int(c, offs);
			data = in_bit(port, offs);
			chan_out_int(c, data);
			break;
		}
	}
}
