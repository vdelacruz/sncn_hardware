#pragma once

#ifdef __XC__

void ioserver(chanend c);

#else

#include <channel.h>
void ioserver(chanend_t c);

#endif

enum ioserver_cmds {
	/* cmd      additional arguments */
	PORTINIT, /* port */
	SETBIT,   /* port, bit-offset */
	CLRBIT,   /* port */
	READBIT   /* port, bit-offset   out: bit value */
};
