#include <stdint.h>
#include <port.h>
#include <channel.h>
#include "ioserver.h"

void io_port_init(chanend_t c_server, port_t p)
{
	chan_out_int(c_server, PORTINIT);
	chan_out_int(c_server, p);
}

void io_setbit(chanend_t c_server, port_t p, int offs)
{
	chan_out_int(c_server, SETBIT);
	chan_out_int(c_server, p);
	chan_out_int(c_server, offs);
}

void io_clrbit(chanend_t c_server, port_t p)
{
	chan_out_int(c_server, CLRBIT);
	chan_out_int(c_server, p);
}

uint8_t io_readbit(chanend_t c_server, port_t p, int offs)
{
	uint8_t value;

	chan_out_int(c_server, READBIT);
	chan_out_int(c_server, p);
	chan_out_int(c_server, offs);
	chan_in_int(c_server, value);
	return value;
}
