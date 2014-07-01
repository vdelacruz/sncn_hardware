#include <xs1.h>
#include "platform.h"
#include "ioloop.h"

portmap_t ports_used[] = {
		{XS1_PORT_8A, "8A"},
		{XS1_PORT_8B, "8B"},
		{XS1_PORT_8C, "8C"},
		{XS1_PORT_8D, "8D"},
		{XS1_PORT_1A, "1A"},
		{XS1_PORT_1B, "1B"},
		{XS1_PORT_1C, "1C"},
		{XS1_PORT_1D, "1D"},
		{XS1_PORT_1E, "1E"},
		{XS1_PORT_1F, "1F"},
		{XS1_PORT_1G, "1G"},
		{XS1_PORT_1H, "1H"},
		{XS1_PORT_1I, "1I"},
		{XS1_PORT_1J, "1J"},
		{XS1_PORT_1K, "1K"},
		{XS1_PORT_1L, "1L"},
		{XS1_PORT_1M, "1M"},
		{XS1_PORT_1N, "1N"},
		{XS1_PORT_1O, "1O"},
		{XS1_PORT_1P, "1P"},
		{0, "??"}
};

ioloop_t lbcon[] = {
		{ XS1_PORT_8A, XS1_PORT_8A, 0, 0 },
		{ XS1_PORT_8A, XS1_PORT_8A, 1, 1 },
		{ XS1_PORT_8A, XS1_PORT_8A, 2, 2 },
		{ XS1_PORT_8A, XS1_PORT_8A, 3, 3 },
		{ XS1_PORT_8A, XS1_PORT_8A, 4, 4 },
		{ XS1_PORT_8A, XS1_PORT_8A, 5, 5 },
		{ XS1_PORT_8A, XS1_PORT_8A, 6, 6 },
		{ XS1_PORT_8A, XS1_PORT_8A, 7, 7 },

		{ XS1_PORT_8B, XS1_PORT_8B, 0, 0 },
		{ XS1_PORT_8B, XS1_PORT_8B, 1, 1 },
		{ XS1_PORT_8B, XS1_PORT_8B, 2, 2 },
		{ XS1_PORT_8B, XS1_PORT_8B, 3, 3 },
		{ XS1_PORT_8B, XS1_PORT_8B, 4, 4 },
		{ XS1_PORT_8B, XS1_PORT_8B, 5, 5 },
		{ XS1_PORT_8B, XS1_PORT_8B, 6, 6 },
		{ XS1_PORT_8B, XS1_PORT_8B, 7, 7 },

		{ XS1_PORT_8C, XS1_PORT_8C, 0, 0 },
		{ XS1_PORT_8C, XS1_PORT_8C, 1, 1 },
		{ XS1_PORT_8C, XS1_PORT_8C, 2, 2 },
		{ XS1_PORT_8C, XS1_PORT_8C, 3, 3 },
		{ XS1_PORT_8C, XS1_PORT_8C, 4, 4 },
		{ XS1_PORT_8C, XS1_PORT_8C, 5, 5 },
		{ XS1_PORT_8C, XS1_PORT_8C, 6, 6 },
		{ XS1_PORT_8C, XS1_PORT_8C, 7, 7 },

		{ XS1_PORT_8D, XS1_PORT_1A, 4, 0 },
		{ XS1_PORT_8D, XS1_PORT_1B, 5, 0 },
		{ XS1_PORT_8D, XS1_PORT_1C, 6, 0 },
		{ XS1_PORT_8D, XS1_PORT_1D, 7, 0 },
		/* { XS1_PORT_1E, XS1_PORT_1E, 0, 0 }, */ /* 25MHz clock in COM P1E */
		{ XS1_PORT_1F, XS1_PORT_1F, 0, 0 },
		{ XS1_PORT_1G, XS1_PORT_1G, 0, 0 },
		{ XS1_PORT_1H, XS1_PORT_1H, 0, 0 },
		{ XS1_PORT_1I, XS1_PORT_1I, 0, 0 },
		{ XS1_PORT_1J, XS1_PORT_1J, 0, 0 },
		{ XS1_PORT_1K, XS1_PORT_1K, 0, 0 },
		{ XS1_PORT_1L, XS1_PORT_1L, 0, 0 },
		{ XS1_PORT_1M, XS1_PORT_1M, 0, 0 },
		{ XS1_PORT_1N, XS1_PORT_1N, 0, 0 },
		{ XS1_PORT_1O, XS1_PORT_1O, 0, 0 },
		{ XS1_PORT_1P, XS1_PORT_1P, 0, 0 }
};

int lbcon_size = sizeof(lbcon)/sizeof(ioloop_t);
