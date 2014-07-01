#include <port.h>
#include <timer.h>
#include <print.h>

#define INC(X) (X) <<= 1 // brighter
#define DEC(X) (X) |= 0x8000000000000000; (X) >>= 1 // darker

#define HW(X) (int)((X) >> 32) // get high word
#define LW(X) (int)((X) & 0xffffffff) // get low word

#define DOSTEP do { \
			port_out(p_red, HW(val_r)); \
			port_out(p_green, HW(val_g)); \
			port_out(p_blue, HW(val_b)); \
			port_out(p_red, LW(val_r)); \
			port_out(p_green, LW(val_g)); \
			port_out(p_blue, LW(val_b)); \
			timer_in(t, t2); \
		} while((t2 - t1) < delay); \
		t1 = t2

void do_led(port_t p_red, port_t p_green, port_t p_blue)
{
	timer_t t;
	int t1, t2;
	int delay = 1500000;
	long long val_r = 0xffffffffffffffff;
	long long val_g = 0xffffffffffffffff;
	long long val_b = 0xffffffffffffffff;

	//port_t rgb[] = {p_red, p_green, p_blue};

	timer_init(t);

	port_init_buffered(p_red, p_red, 32);
	port_init_buffered(p_green, p_green, 32);
	port_init_buffered(p_blue, p_blue, 32);

	timer_in(t, t1);
	timer_in_when_timerafter(t, t1, t1+150000000);
	while(1) {
		
		for (int i=0; i<32; i++) {
			DOSTEP;
			INC(val_r); INC(val_g); INC(val_b);
		}

		delay = 1500000;

		for (int i=0; i<32; i++) {
			DOSTEP;
			DEC(val_r); DEC(val_g);
		}

		delay = 1500000;

		while(1) {
			for (int i=0; i<32; i++) {
				DOSTEP;
				DEC(val_b);
			}
			for (int i=0; i<32; i++) {
				DOSTEP;
				INC(val_r);
			}
			for (int i=0; i<32; i++) {
				DOSTEP;
				DEC(val_r);
			}
			for (int i=0; i<32; i++) {
				DOSTEP;
				INC(val_g);
			}
			for (int i=0; i<32; i++) {
				DOSTEP;
				DEC(val_g);
			}
			for (int i=0; i<32; i++) {
				DOSTEP;
				INC(val_b);
			}
		}
	}
}
