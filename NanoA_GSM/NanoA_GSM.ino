#define TINY_GSM_MODEM_SIM800

#include <avr/wdt.h>
#include <Wire.h>
#include <avr/wdt.h>
#include <TinyGsmClient.h>
#include <SoftwareSerial.h>

//#define DUMP_AT_COMMANDS
#define SerialMon Serial

uint16_t modbusData[35];
/* length 34 */
char cmdByte[64]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8',};
int dataIdx;

/* modem parameter */
SoftwareSerial SerialAT(10, 11); // RX, TX
const char apn[]  = "3data";
const char user[] = "3data";
const char pass[] = "3data";
const char userID[] = "BT01";
const char devID[] = "EMON";

char dataBuff[128]; /* maximum allowed packet */

const char server[] = "35.185.186.79";
const int  port = 5555;

#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);

void setup() {
  delay(10);
  
  /* Debug Port */
  SerialMon.begin(9600);
  while(!SerialMon) {;}

  /* GSM Modem */
  SerialAT.begin(9600);
  while(!SerialAT) {;}
  modem.restart();
  String modemInfo = modem.getModemInfo();
  SerialMon.print(F("Modem: "));
  SerialMon.println(modemInfo);

  /* I2C */
  Wire.begin();
  SerialMon.println("BTGate!");

  /* I2C LED on 13 */
  pinMode(13, OUTPUT);
}

byte x = 0;

void loop() {
  /* GPRS-GSM Parameter */
  SerialMon.print(F("Waiting for Network..."));
  if (!modem.waitForNetwork()) {
    SerialMon.println(" GSM Fail");
    delay(5000);
    return;
  } else {
    SerialMon.println(" GSM OK ");  
  }

  SerialMon.print(F("Dial-Up GPRS..."));
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println(" GPRS Fail ");
    delay(5000);
    return;
  } else {
    SerialMon.println(" GPRS Connected ");
  }

  /* I2C Slave Handler */
  dataIdx = 0;
  for (dataIdx=0; dataIdx<=34; dataIdx++) {
     digitalWrite(13, HIGH);
     Wire.beginTransmission(2);
     Wire.write(cmdByte[dataIdx]);
     Wire.endTransmission();
     Wire.requestFrom(2, 2);
  
     byte response[8];
     int index = 0;

    while (Wire.available()) {
        byte b = Wire.read();
        response[index] = b;
        index++;
        digitalWrite(13, LOW);
    }
                     
    modbusData[dataIdx] = (response[1] << 8)| response[0];
    SerialMon.print("Index : ");
    SerialMon.print(dataIdx);
    SerialMon.print(" Value : ");
    SerialMon.println(modbusData[dataIdx]);
   }
    
   delay(1000);

   /* Connect to BTServer */
   int rv = client.connect(server, port);
   if (rv) {
    SerialMon.println("Connected to Server");
   } else {
    SerialMon.println("Connecting to Server Fail");
   }
   delay(1000);
   /* Sending Data to Server */
   sprintf(dataBuff, "%s#%s#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#%x#", userID, devID,  modbusData[0], modbusData[1], modbusData[2], modbusData[3], modbusData[4], modbusData[5], modbusData[6], modbusData[7], modbusData[8], modbusData[9], modbusData[10], modbusData[11], modbusData[12], modbusData[13], modbusData[14], modbusData[15], modbusData[16], modbusData[17], modbusData[18], modbusData[19], modbusData[20], modbusData[21], modbusData[22], modbusData[23], modbusData[24], modbusData[25], modbusData[26], modbusData[27], modbusData[28], modbusData[29], modbusData[30], modbusData[31], modbusData[32], modbusData[33]);
   rv = 0;
   long x = millis();
   long to = x + 1000;
   while(rv == 0){
    rv = client.write((uint8_t *)dataBuff, strlen(dataBuff));
    if (millis() > to)
      break;
   }
   if (rv != 0) {
    SerialMon.print("Data Sent to Server | Written : ");
    SerialMon.println(rv, DEC); 
   } else {
    SerialMon.println("Data Not Send to Server"); 
   }
   
   client.stop();
   delay(1000);
   
   /* Close Connection */
   modem.gprsDisconnect();
   SerialMon.println(F("GPRS disconnected"));
   delay(1000);
}
