#include <Arduino.h>

/* Arduino Serial Command Processor */

int ledPin = 11; // LED with PWM brightness control
size_t MSG_LEN = 2; 
int level = 0;

void setup()
{ // called once on start up
  // A baud rate of 115200 (8-bit with No parity and 1 stop bit)
  Serial.begin(115200, SERIAL_8N1);
  pinMode(ledPin, OUTPUT); // the LED is an output
}

/*The message consist of: 1 byte for address, 1 byte for command, then depending on the command 1 byte for which address (what value to obtain) 
Then*/
void loop()
{ // loops forever
  unsigned char message[MSG_LEN];
  char buffer[MSG_LEN]; // stores the return buffer on each loop
  if (Serial.available() > 0)
  {                                     // bytes received
    Serial.readBytes(message, MSG_LEN); // C strings end with \0
    buffer[0] = message[0];
    if (message[0] == 0x03) 
    { 
      level = message[1]; // extract the int
      if (level >= 0 && level <= 255)
      {                             // is it in range?
        analogWrite(ledPin, level); // yes, write out
        buffer[1] = 0xAA;
      }
      else
      { // no, error message back
        buffer[1] = 0xF0;
      }
      Serial.print(buffer); // send the buffer to the RPi
    }                       // otherwise, unknown cmd
    else
    {
      // Here the command was not intended for me
      // But to notify that I recieved something, I will blink the LED
      analogWrite(ledPin, 0);
      delay(1000);
      analogWrite(ledPin, level);
    }
  }
}