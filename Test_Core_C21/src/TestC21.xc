/*
 * ///////////////////////////////////////////////////////////////////////////////////////////////////////
 *
 * Beta version of C21 Software Test
 * DX Communication must be tested by hand.
 * The test will check the LED and GPIO port status
 *
 * ///////////////////////////////////////////////////////////////////////////////////////////////////////
 */

# define FLASH_PERIOD 20000000



#include <platform.h>
#include <xs1.h>
//#include <xscope.h>
#include "print.h"
#include "sysled.h"

on stdcore[0]: out port led_blue = XS1_PORT_1K;
on stdcore[0]: out port led_green = XS1_PORT_1L;
on stdcore[0]: out port led_red = XS1_PORT_1M;

on stdcore[1]:  out port GPIOA = XS1_PORT_8A;
on stdcore[1]:  port GPIOB = XS1_PORT_8B;
on stdcore[1]:  port GPIOC = XS1_PORT_8C;



void led (void) {
while (1)
    {
    timer tmr ;
    unsigned On = 1, a=0;
    unsigned t;
    tmr :> t ;
        while (a<11)
        {
            led_green <: On ;
            t += FLASH_PERIOD ;
            tmr when timerafter (t) :> void ;
            On = ! On ;
            a++;
        }

        while (a<23)
        {
            led_blue <: On ;
            t += FLASH_PERIOD ;
            tmr when timerafter (t) :> void ;
            On = ! On ;
            a++;
        }

        while (a<40)
        {
            led_red <: !On ;
            t += FLASH_PERIOD ;
            tmr when timerafter (t) :> void ;
            On = ! On ;
            a++;


        }
    }

}



void GPIO (void)
{

    unsigned i, var, j , var2;
    printstr("Checking GPIO ports... \n");

        while (1)
        {

            for (i=0;i<0xFF;i++)
            {
                GPIOA <: i;

                printstr ("Checking port A and B \n");


                GPIOB :> var;

                if (i != var)
                {
                    printintln (i);
                    printintln (var);
                }
                else
                {
                    if (i=0xFF)
                    {
                    printstr ("Port A and B working \n");
                    }
                }
                return;
            }

            for (j=0;j<0xFF;j++)
            {
                    GPIOB <: j;

                    printstr ("Checking port B and C \n");


                    GPIOC :> var2;

                    if (j != var2)
                    {
                        printintln (j);
                        printintln (var2);
                    }
                    else
                    {
                        if (j=0xFF)
                        {
                        printstr ("Port B and C working \n");
                        }
                    }
                    return;
                }
            }
        }

///////////////////////****************     DX COMMUNICATION   *********************////////////////////////////
/////////* For DX Communication, it is necessary to have two C21-DX-LVDS board connected in a Chain *///////////


int main(void)
{
    par {

        on stdcore[0]:
        {
          led();
        }
        on stdcore[1]:
           {
             GPIO();
           }


    }
}


///////////////////////****************     XSCOPE PART   *********************////////////////////////////

//void xscope_user_init(void) {
//   xscope_register(2, XSCOPE_CONTINUOUS, "Test data1", XSCOPE_INT, "n",
//           XSCOPE_CONTINUOUS, "Test data2", XSCOPE_INT, "n");
//   xscope_config_io(XSCOPE_IO_TIMED);
//}
//
//void generate_data(void)
//{
//    int incr1 = 0, incr2 = 0;
//    timer tmr;
//    unsigned time;
//    tmr :> time;
//
//    xscope_user_init();
//
//    printstrln("starting");
//
//    while(1)
//    {
//        incr1++;
//        incr2--;
//        if (incr1 > 10000) incr1 = 0;
//        if (incr2 < -10000) incr2 = 0;
//        xscope_int(0,incr1);
//        xscope_int(1,incr2);
////      tmr when timerafter(time+100000) :> void;
//    }
//}


///////////////////////****************     XSCOPE PART   *********************////////////////////////////
