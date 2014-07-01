#pragma once

#ifdef __XC__

void do_led(unsigned p_red, unsigned p_green, unsigned p_blue);

#else

#include <port.h>
void do_led(port_t p_red, port_t p_green, port_t p_blue);

#endif
