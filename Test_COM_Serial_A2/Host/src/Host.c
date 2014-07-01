/*
 ============================================================================
 Name        : Host.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // ignore break signal
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf("error %d setting term attributes", errno);
}


int main(void) {

    char rs485input[128]; //RS485 input buffer
    char rs485output[128]; //RS485 output message

    int c; //carachter input

    int velocityRight = 0;
    int velocityLeft = 0;

    int obtainedValues[2];

    int i,aux; //auxiliar integer
    char str[50],str1[50]; //auxiliar string

    char *velOutput = "v.";


    char *portname = "/dev/ttyUSB2";
       int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

       if (fd < 0)
           {
           printf("error %d opening %s: %s", errno, portname, strerror (errno));
           return 0;
           }
       set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
       set_blocking (fd, 0);                // set no blocking

       while(1){

        printf("************************************************************************************\n");
        printf("Host application for Yujin Robots SOMANET demo\n");
        printf("Communication was successfully set at 115200 bps 8n1\n");
        printf("Select one option (1-3) from the menu and push ENTER. To quit type Ctrl + C:\n");
        printf("1 - Set velocity\n");
        printf("2 - Get position and velocity feedback from wheels\n");
        printf("3 - Get information from the proximity sensor\n");
        printf("4 - Sensor-reactive behavior\n");
        printf("************************************************************************************\n");

       do{
           c = getchar();
       }while(c!=49 & c!=50 & c!= 51 & c!=52);

           while ( getchar() != '\n' );

        switch(c){
        case 49:

                sprintf(rs485output,"v ");

                //vel on Right wheel
                printf("Set velocity on RIGHT wheel: \n");
                scanf("%d", &velocityRight);
                aux = sprintf(str1,"%d",velocityRight);
                sprintf(str,"");

                if (aux<6){ //6 characters for each parameter
                    sprintf(str,"0");
                    int nOfZeros = 6-strlen(str1);
                    for(i=1;i<nOfZeros;i++){
                        strcat(str,"0");
                    }
                }

                strcat(str,str1); //format param
                strcat(rs485output,str); //add param to message
                strcat(rs485output," "); //add space

                //vel on Left wheel
                printf("Set velocity on LEFT wheel: \n");
                scanf("%d", &velocityLeft);
                aux = sprintf(str1,"%d",velocityLeft);
                sprintf(str,"");

                if (aux<6){ //6 characters for each parameter
                    sprintf(str,"0");
                    int nOfZeros = 6-strlen(str1);
                    for(i=1;i<nOfZeros;i++){
                        strcat(str,"0");
                    }
                }

                strcat(str,str1);
                strcat (rs485output,str);
                write (fd, rs485output, 15); //message size is always 1 (v command) + 2x6 (params) + 2 (spaces) = 15

                printf("Velocity was successfully set.\n");
                sleep(2);

            break;

        case 50:

            do{
                aux = read(fd, rs485input, sizeof rs485input);
            }while(aux>0);//clean buffer

              //first obtaining the position
               write (fd, "gp", 2); //write command to obtain position information
               usleep(5000);
               aux = read(fd, rs485input, 20);  // read up to 20 characters if ready to read

                                                           //same procdure for the velocity
               if(rs485input[0]=='f'){  //if it is a reply
                   obtainedValues[0] = 0;   //cleaning
                   obtainedValues[1] = 0;   //cleaning

                   sprintf(str,"%c", rs485input[2]);    //save the first char

                    for (i=3;i<aux;i++){                //lets see the whole reply
                        if(rs485input[i]!=' '){         //if it is part of the first number

                            sprintf (str1,"%c",rs485input[i]);     //keep saving the digits
                            strcat(str,str1);

                        }else{  //it it is part of the second number

                            sscanf(str,"%d", &obtainedValues[0]);    //save the received number as an integer
                            sprintf (str,"");       //cleaning to analyse the second number
                        }
                       }
                    sscanf(str,"%d", &obtainedValues[1]);       //once finished, save the second number as an integer


                 printf("Position received values - PosR:%d PosL:%d \n",obtainedValues[0],obtainedValues[1]); //show the results
                 memset(&rs485input[0], 0, sizeof(rs485input)); //cleaning
               }


               do{
                   aux = read(fd, rs485input, sizeof rs485input);
               }while(aux>0); //clean buffer
                                                               //same procedure for the velocity
               write (fd, "gv", 2);
               usleep(5000);
               aux = read(fd, rs485input, 20);  // read up to 20 characters if ready to read

               if(rs485input[0]=='f'){
                   obtainedValues[0] = 0;
                   obtainedValues[1] = 0;
                              sprintf(str,"%c", rs485input[2]);

                               for (i=3;i<aux;i++){
                                   if(rs485input[i]!=' '){

                                       sprintf (str1,"%c",rs485input[i]);
                                       strcat(str,str1);

                                   }else{

                                       sscanf(str,"%d", &obtainedValues[0]);
                                       sprintf (str,"");
                                   }
                                  }
                               sscanf(str,"%d", &obtainedValues[1]);


                            printf("Velocity received values - VelR:%d VelL:%d \n",obtainedValues[0],obtainedValues[1]);
                            memset(&rs485input[0], 0, sizeof(rs485input));
               }


            break;

        case 51:

            while(1){

                            }
            break;

        default:

            printf("Option not valid.\n");
            sleep(2);
            break;
        }


       }

	return EXIT_SUCCESS;
}
