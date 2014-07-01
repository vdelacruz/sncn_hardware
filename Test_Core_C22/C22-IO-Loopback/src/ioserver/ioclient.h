#pragma once

#include <stdint.h>

#ifdef __XC__

void io_port_init(chanend c_server, unsigned p);
void io_setbit(chanend c_server, unsigned p, int offs);
void io_clrbit(chanend c_server, unsigned p);
uint8_t io_readbit(chanend c_server, unsigned p, int offs);

#else

#include <port.h>
#include <channel.h>

void io_port_init(chanend_t c_server, port_t p);
void io_setbit(chanend_t c_server, port_t p, int offs);
void io_clrbit(chanend_t c_server, port_t p);
uint8_t io_readbit(chanend_t c_server, port_t p, int offs);

#endif
