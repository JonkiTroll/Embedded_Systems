#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "../include/modbus.h"

uint16_t modRTU_CRC(uint8_t buf[], int len);
void print_string_hex(uint8_t array[], size_t len, bool send);
void make_message(uint8_t argv[], size_t len);
int read_slave_feedback(int fid, uint8_t receive[], int len);

uint16_t address;
uint16_t value;
uint16_t CRC;

//#define DEBUG

int modbus::send(uint8_t address, uint16_t reg, int16_t value) { 
    
    int count;
    
    uint8_t buffer[size] = {address, 
                            6, 
                            (uint8_t) (reg >> 8),
                            (uint8_t) (reg >> 0),
                            (uint8_t)(value >> 8),
                            (uint8_t) value, 
                            0, 
                            0};
    
    make_message(buffer, size);
    
    #ifdef DEBUG
    print_string_hex(buffer, size, true);
    #endif

    if ((count = write(file, &buffer, size) < 0))
    {
        perror("Failed to write to the output\n");
        return -1;
    }

    usleep(11'000);

    if (read_slave_feedback(file, receive_buf, size)) 
        perror("No message received");
    
    usleep(11'000);

    #ifdef DEBUG
    print_string_hex(receive_buf, size, true);
    #endif

    tcflush(file, TCIFLUSH);

    return 0;
}

int16_t modbus::receive(uint8_t address, uint16_t reg) { 

    int count;
    
    uint8_t buffer[size] = {address, 
                            3, 
                            (uint8_t) (reg >> 8),
                            (uint8_t) (reg >> 0),
                            0,
                            0,
                            0, 
                            0};

    make_message(buffer, size);

    #ifdef DEBUG
    print_string_hex(buffer, size, true);
    #endif

    if ((count = write(file, &buffer, size) < 0))
    {
        perror("Failed to write to the output\n");
        return -1;
    }

    usleep(11'000);

    if (read_slave_feedback(file, receive_buf, size)) 
        perror("No message received");
    
    usleep(11'000);
    
    #ifdef DEBUG
    print_string_hex(receive_buf, size, true);
    #endif

    tcflush(file, TCIFLUSH);

    int16_t val = ((((int16_t) receive_buf[4]) << 8) | (((int16_t) receive_buf[5]) << 0));

    return val;
}


int read_slave_feedback(int fid, uint8_t receive[], int len)
{
   int count;
   if ((count = read(fid, (void *)receive, len)) < 0)
    {
        perror("Failed to read from the input\n");
        return -1;
    }

    return 0;
}


int open_and_set_fid(size_t len, struct termios *old_options)
{
   int file;
   if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
   {
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;
   // struct termios old_options;

   tcgetattr(file, &options);
   tcgetattr(file, old_options);

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

void make_message(uint8_t argv[], size_t len)
{
   // argv[0] is simply the name of the process, remember that.
    
    CRC = modRTU_CRC(argv, len);
    argv[6]  = (uint8_t)((CRC >> 8) & 0xFF); // 8 MSB of the address
    argv[7]  = (uint8_t)((CRC >> 0) & 0xFF); // 8 MSB of the address
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

void print_string_hex(uint8_t array[], size_t len, bool send)
{
   //if (send) printf("Sent request:   ");
   //else printf("Recieved reply: ");

   for (int k = 0; k < len; k++)
   {
      if (array[k]<0x10) printf("0%x ", array[k]);
      else printf("%x ", array[k]);
   }
   printf("\n");
}
