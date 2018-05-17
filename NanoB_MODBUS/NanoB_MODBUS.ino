/* 
 * Bogor Technologies
 * Modbus Master
 * I2C Slave
 * BT-Gateway
*/

#include <ModbusMaster.h>
#include <Wire.h>
#include <avr/wdt.h>

#define TXEN  9 

/* Type ID */
char c;
int dataIdx;

/* Modbus Master Cons */
ModbusMaster node;
uint16_t data[64];
int j;

void preTransmission()
{
  digitalWrite(TXEN, 1);
}

void postTransmission()
{
  digitalWrite(TXEN, 0);
}

void setup() {
  /* IO */
  pinMode(2, OUTPUT);
  pinMode(TXEN, OUTPUT);  
  pinMode(13, OUTPUT);
  postTransmission();
  
  /* i2c slave */
  Wire.begin(2);
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // data request to slave z

  /* modbus */
  Serial.begin(9600);
  /* node ID 2 */
  node.begin(2, Serial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() 
{
  uint8_t result;
  digitalWrite(2, HIGH);
  result = node.readHoldingRegisters(0, 34);
  if (result == node.ku8MBSuccess)
  {
    /* read all modbus response*/
    for (j = 0; j <= 34; j++)
    {
      data[j] = node.getResponseBuffer(j);
    }
    digitalWrite(2, LOW);
  }
  delay(500);
}

void receiveEvent(int howMany) 
{
    digitalWrite(13, HIGH);
    while (0 < Wire.available()) {  // loop through all but the last
      byte x = Wire.read();         // receive byte as a character
      c = x;
    } 
}

void requestEvent() 
{
    digitalWrite(13, LOW);
    byte response[2];
  
    switch(c) {

      case 'A' :
          response[0] = data[0] & 0x00FF; //LSB
          response[1] = (data[0] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'B' :
          response[0] = data[1] & 0x00FF; //LSB
          response[1] = (data[1] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'C' :
          response[0] = data[2] & 0x00FF; //LSB
          response[1] = (data[2] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'D' :
          response[0] = data[3] & 0x00FF; //LSB
          response[1] = (data[3] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'E' :
          response[0] = data[4] & 0x00FF; //LSB
          response[1] = (data[4] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'F' :
          response[0] = data[5] & 0x00FF; //LSB
          response[1] = (data[5] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'G' :
          response[0] = data[6] & 0x00FF; //LSB
          response[1] = (data[6] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'H' :
          response[0] = data[7] & 0x00FF; //LSB
          response[1] = (data[7] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'I' :
          response[0] = data[8] & 0x00FF; //LSB
          response[1] = (data[8] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'J' :
          response[0] = data[9] & 0x00FF; //LSB
          response[1] = (data[9] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'K' :
          response[0] = data[10] & 0x00FF; //LSB
          response[1] = (data[10] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'L' :
          response[0] = data[11] & 0x00FF; //LSB
          response[1] = (data[11] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'M' :
          response[0] = data[12] & 0x00FF; //LSB
          response[1] = (data[12] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'N' :
          response[0] = data[13] & 0x00FF; //LSB
          response[1] = (data[13] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'O' :
          response[0] = data[14] & 0x00FF; //LSB
          response[1] = (data[14] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'P' :
          response[0] = data[15] & 0x00FF; //LSB
          response[1] = (data[15] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'Q' :
          response[0] = data[16] & 0x00FF; //LSB
          response[1] = (data[16] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'R' :
          response[0] = data[17] & 0x00FF; //LSB
          response[1] = (data[17] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'S' :
          response[0] = data[18] & 0x00FF; //LSB
          response[1] = (data[18] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'T' :
          response[0] = data[19] & 0x00FF; //LSB
          response[1] = (data[19] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'U' :
          response[0] = data[20] & 0x00FF; //LSB
          response[1] = (data[20] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'V' :
          response[0] = data[21] & 0x00FF; //LSB
          response[1] = (data[21] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'W' :
          response[0] = data[22] & 0x00FF; //LSB
          response[1] = (data[22] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'X' :
          response[0] = data[23] & 0x00FF; //LSB
          response[1] = (data[23] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'Y' :
          response[0] = data[24] & 0x00FF; //LSB
          response[1] = (data[24] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case 'Z' :
          response[0] = data[25] & 0x00FF; //LSB
          response[1] = (data[25] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '1' :
          response[0] = data[26] & 0x00FF; //LSB
          response[1] = (data[26] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '2' :
          response[0] = data[27] & 0x00FF; //LSB
          response[1] = (data[27] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '3' :
          response[0] = data[28] & 0x00FF; //LSB
          response[1] = (data[28] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '4' :
          response[0] = data[29] & 0x00FF; //LSB
          response[1] = (data[29] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '5' :
          response[0] = data[30] & 0x00FF; //LSB
          response[1] = (data[30] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '6' :
          response[0] = data[31] & 0x00FF; //LSB
          response[1] = (data[31] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '7' :
          response[0] = data[32] & 0x00FF; //LSB
          response[1] = (data[32] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;

      case '8' :
          response[0] = data[33] & 0x00FF; //LSB
          response[1] = (data[33] & 0xFF00) >> 8; //LSB
          Wire.write(response,2);
          break;


      }
}

