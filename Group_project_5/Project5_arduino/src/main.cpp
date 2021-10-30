#include <Arduino.h>

#define MY_ADDR 0x01
#define MOTOR_ADDR 0x03
/* Arduino Serial Command Processor */

int ledPin = 11;    // LED with PWM brightness control
size_t MSG_LEN = 8; // I always recieve 8 bytes.
int level = 0;
bool both = false;
int16_t speed = 0;

uint16_t modRTU_CRC(uint8_t buf[], int len);
void LED_blink(int led_pin, int intensity);
void val_write(uint16_t address, int16_t value);
uint16_t val_read(uint16_t address);

void setup()
{ // called once on start up
  // A baud rate of 115200 (8-bit with No parity and 1 stop bit)
  Serial.begin(115200, SERIAL_8N1);
  pinMode(ledPin, OUTPUT); // the LED is an output
  pinMode(13, OUTPUT); // the LED is an output
}

/*The message consist of: 1 byte for address, 1 byte for command, then depending on the command 2 byte for which (memory)address (what value to obtain)
Then 2 bytes for the value to be sent to the said (memory)address then two bytes for CRC */
void loop()
{ // loops forever
  unsigned char message[MSG_LEN];
  uint8_t buffer[MSG_LEN]; // stores the return buffer on each loop
  if (Serial.available() > 0)
  {                                     // bytes received
    Serial.readBytes(message, MSG_LEN); // Read a specific number of bytes
    if (message[0] == MY_ADDR ) // The message refers to me
    {
      //uint16_t CRC = ((uint16_t)message[MSG_LEN - 2] << 8) | message[MSG_LEN - 1]; // Combining the two bytes to a single 16 bit number.
      if (true) //(CRC == modRTU_CRC(message, MSG_LEN))
      {
        uint8_t function_code = message[1];
        uint16_t mem_address = ((uint16_t)message[2] << 8) | message[3]; // Combining the two bytes to a single 16 bit number.
        uint16_t msg_value = ((uint16_t)message[4] << 8) | message[5];   // Combining the two bytes to a single 16 bit number.
        switch (function_code)
        {
        case 0x06: // funcion code 6 is writing a value to a register
          
          buffer[0] = message[0];
          buffer[1] = message[1];
          buffer[2] = message[2];
          buffer[3] = message[3];
          buffer[4] = message[4];
          buffer[5] = message[5];
          buffer[6] = message[6];
          buffer[7] = message[7];
          Serial.print((char*)buffer);
          val_write(mem_address, msg_value);
          break;
        case 0x03:
          // Give values
          uint16_t val_send = val_read(mem_address);
          buffer[0] = message[0];
          buffer[1] = message[1];
          buffer[2] = message[2];
          buffer[3] = message[3];
          buffer[4] = (uint8_t)((val_send >> 8) & 0xFF);
          buffer[5] = (uint8_t)((val_send >> 0) & 0xFF);
          uint16_t CRC_send = 0x4545;//modRTU_CRC(buffer, MSG_LEN);
          buffer[6] = (uint8_t)((CRC_send >> 8) & 0xFF);
          buffer[7] = (uint8_t)((CRC_send >> 0) & 0xFF);
          Serial.print((char*)buffer);
          break;

        default:
          break;
        }
        // no, error message back
        // buffer[1] = 0xF0;
        // Serial.print(buffer); // send the buffer to the RPi
      } // otherwise, unknown cmd
      else
      {
        // The CRC did not match
        // Nothing to be done, maybe blink LED or sumthing.
        LED_blink(ledPin,level);
      }
    }
    else
    {
      // Here the command was not intended for me
      // But to notify that I recieved something, I will blink the LED
      LED_blink(ledPin,level);
    }
    both = false;
  }
}

void val_write(uint16_t address, int16_t value)
{

  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}


uint16_t val_read(uint16_t address)
{

return 0x45;
}

void LED_blink(int led_pin, int intensity)
{
  analogWrite(led_pin, 0);
  delay(300);
  analogWrite(led_pin, intensity);
}

uint16_t modRTU_CRC(uint8_t buf[], int len)
{
  uint16_t crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++)
  {
    crc ^= (uint16_t)buf[pos];

    for (int k = 8; k != 0; k--)
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
