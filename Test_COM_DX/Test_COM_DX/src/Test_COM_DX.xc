/*
 * ///////////////////////////////////////////////////////////////////////////////////////////////////////
 *
 * Test for COM_DX_B1.
 * For running the test is necessary to connect two nodes in a Chain.
 * Test the connector according to the platformfile.
 * The platform file can be find in the folder ...XMOS/targets/SOMANET-Dual-C22-IfmBLDC-DX-via-IFM
 * LINK A -> PORT A
 * LINK B -> PORT B
 * The test will succeed if all the nodes are printed in all the combinations.
 *
 * ///////////////////////////////////////////////////////////////////////////////////////////////////////
 */


#include <platform.h>
#include <xs1.h>
#include "print.h"



int main(void)
{
    par {

        on stdcore[0]:
        {
            printstr (" Printing in Core 0 ");
        }
        on stdcore[1]:
           {
            printstr (" Printing in Core 0 ");
           }
        on stdcore[2]:
           {
            printstr (" Printing in Core 2 ");
           }
        on stdcore[3]:
           {
            printstr (" Printing in Core 3 ");
           }
        on stdcore[4]:
           {
            printstr (" Printing in Core 4 ");
           }
        on stdcore[5]:
           {
             printstr (" Printing in Core 5 ");
           }
        on stdcore[6]:
           {
             printstr (" Printing in Core 6 ");
           }
        on stdcore[7]:
           {
             printstr (" Printing in Core 7 ");
           }


    }

}
