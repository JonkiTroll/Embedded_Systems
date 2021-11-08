/* Simple send and receive C example (line-mode terminal program with local echo)
 * for communicating with the Arduino using /dev/ttyS0. */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint16_t modRTU_CRC(uint8_t buf[], int len);
void print_string_hex(uint8_t array[], int len, bool send);
void make_message(uint8_t msg[], char *argv[], size_t len);
int open_and_set_fid(size_t len);

uint16_t address;
uint16_t value;
uint16_t CRC;

int main(int argc, char *argv[])
{
    int file, count;
    if (argc != 5)
    { // 5 arguments should be recieved, 0:name, 1:slave number, 2:function, 3:address, 4: value 
        printf("Invalid number of arguments, exiting!\n");
        return -2;
    }

    size_t MSG_BASE = 8; // Base number of bytes to send, might recieve more, but not for out application
    uint8_t msg[MSG_BASE]; // initalization of the msg array, the message to be sent.
    
    make_message(msg, argv, MSG_BASE); // Function that maps the main inputs to a sent message, including the CRC.

    print_string_hex(msg, MSG_BASE, true); // function that prints out a hex message.

    // file = open_and_set_fid(MSG_BASE);  // Function that opens the file, and sets the options for raw mode and the desired speed.
    if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
    {
      perror("UART: Failed to open the file.\n");
      return -1;
    }

    struct termios options;
    struct termios old_options;

    tcgetattr(file, &options);
    tcgetattr(file, &old_options);

    // options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    // options.c_iflag = IGNPAR | ICRNL;
    cfmakeraw(&options);
    if (cfsetispeed(&options, B115200) < 0 || cfsetospeed(&options, B115200) < 0)
    { // ... speed could not be set ...
    }
    options.c_cflag &= ~(PARENB | CSTOPB);
    //options.c_cc[VTIME]=2; /* no timer */
    options.c_cc[VMIN] = MSG_BASE; /* minimum number of characters */
    tcflush(file, TCIFLUSH);
    tcsetattr(file, TCSANOW, &options);

   
    if ((count = write(file, &msg, MSG_BASE) < 0))
    {
        perror("Failed to write to the output\n");
        return -1;
    }

    usleep(90000);

    unsigned char receive[MSG_BASE];

    if ((count = read(file, (void *)receive, MSG_BASE)) < 0)
    {
        perror("Failed to read from the input\n");
        return -1;
    }

    if (count == 0)
        printf("There was no data available to read!\n");
    else
    {
        if (receive[0] == msg[0])
        {
            print_string_hex(receive, MSG_BASE, false); 
        }
        else
        {
            printf("The sent command was not received back\n");
        }
    }

    tcflush(file, TCIFLUSH);
    tcsetattr(file, TCSANOW, &old_options);
    close(file);
    return 0;
}

int open_and_set_fid(size_t len)
{
   int file;
   if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
   {
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;
   struct termios old_options;

   tcgetattr(file, &options);
   tcgetattr(file, &old_options);

   // options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   // options.c_iflag = IGNPAR | ICRNL;
   cfmakeraw(&options);
   if (cfsetispeed(&options, B115200) < 0 || cfsetospeed(&options, B115200) < 0)
   { // ... speed could not be set ...
   }
   options.c_cflag &= ~(PARENB | CSTOPB);
   //options.c_cc[VTIME]=2; /* no timer */
   options.c_cc[VMIN] = len; /* minimum number of characters */
   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);
   
   return file;
}

void make_message(uint8_t msg[], char *argv[], size_t len)
{
   // argv[0] is simply the name of the process, remember that.
    msg[0]  = atoi(argv[1]);           // slave number (address)
    msg[1]  = atoi(argv[2]);           // function code (3 for reading and 6 for writing)
    address = atoi(argv[3]); // the address to send
    msg[2]  = (uint8_t)((address >> 8) & 0xFF); // 8 MSB of the address
    msg[3]  = (uint8_t)((address >> 0) & 0xFF); // 8 LSB of the address
    value   = atoi(argv[4]);
    msg[4]  = (uint8_t)((value >> 8) & 0xFF); // 8 MSB of the address
    msg[5]  = (uint8_t)((value >> 0) & 0xFF); // 8 MSB of the address
    CRC = modRTU_CRC(msg, len);
    msg[6]  = (uint8_t)((CRC >> 8) & 0xFF); // 8 MSB of the address
    msg[7]  = (uint8_t)((CRC >> 0) & 0xFF); // 8 MSB of the address
}


uint16_t modRTU_CRC(uint8_t buf[], int len)
{
    uint16_t crc = 0xFFFF;
    for (int pos = 0; pos < len-2; pos++)
    {
        crc ^= (uint16_t)buf[pos];

        for (int k = len; k != 0; k--)
        {
            if ((crc & 0x0001) != 0)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
                crc >>= 1;
        }
    }
    return crc;
}

void print_string_hex(uint8_t array[], int len, bool send)
{
   if (send) printf("Sent request:   ");
   else printf("Recieved reply: ");

   for (int k = 0; k < len; k++)
   {
      if (array[k]<0x10) printf("0%x ", array[k]);
      else printf("%x ", array[k]);
   }
   printf("\n");
}