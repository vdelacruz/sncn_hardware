#pragma once

#ifdef __XC__

void init_ports_ifm(chanend c_server);
void init_ports_com(chanend c_server);
int count_ones_ifm(chanend c_server);
int count_ones_com(chanend c_server);
void cmp_com_to_ifm(chanend c_com, chanend c_ifm);
void cmp_ifm_to_com(chanend c_com, chanend c_ifm);

#else

#include <stdint.h>
#include <port.h>
#include <channel.h>

typedef struct {
	port_t p_com;
	port_t p_ifm;
	uint8_t bitoffs_com;
	uint8_t bitoffs_ifm;
} ioloop_t;

typedef struct {
	port_t id;
	char name[2];
} portmap_t;

void init_ports_ifm(chanend_t c_server);
void init_ports_com(chanend_t c_server);
int count_ones_ifm(chanend_t c_server);
int count_ones_com(chanend_t c_server);
void cmp_com_to_ifm(chanend_t c_com, chanend_t c_ifm);
void cmp_ifm_to_com(chanend_t c_com, chanend_t c_ifm);

#endif
