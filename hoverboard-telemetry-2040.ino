
#include "mavlink/common/mavlink.h"
#include "mavlink/common/mavlink_msg_servo_output_raw.h"

#include <SoftwareSerial.h>
SerialPIO HoverSerial1(2,3);
SerialPIO HoverSerial2(4,5);
SerialPIO HoverSerial3(6,7);
SerialPIO ser6(10,11);


int MAXRPM = 100;


const int board1power = 8;  
const int board2power = 9;    
const int board3power = 10;  

const int board1switch = 11;    
const int board2switch = 12; 
const int board3switch = 13;   



#define START_FRAME 0xABCD  // [-] Start frme definition for reliable serial communication
//#define DEBUG_RX            // [-] Debug received data. Prints all bytes to serial (comment-out to disable)

int leftoutput = 10;
int rightoutput = 10;
//low voltage 
//speed limit
//power control 

int boardson = 0;
int board1on = 0;
int board2on = 0;
int board3on = 0;

int board1error = 0;
int board2error = 0;
int board3error = 0;

int startupok = 0;
int startcycle = 0;
int stopcycle = 0;

unsigned long buttonMillis = 0; 
unsigned long checkMillis = 0; 

const long buttoninterval = 2000;  // time to hold power switch
const long boardinterval = 4000;  // time to hold power switch

unsigned long previousMillis = 0;  // will store last time LED was updated
const long telem = 1000; 

int THRR1;
int THRL1;
int THRR2;
int THRL2;
int THRR3;
int THRL3;

//wheel RPM
int RPMR1;
int RPML1;
int RPMR2;
int RPML2;
int RPMR3;
int RPML3;

//voltage and temperature
int VOLT1;
int TEMP1;
int VOLT2;
int TEMP2;
int VOLT3;
int TEMP3;



uint8_t idx = 0;         // Index for new data pointer
uint16_t bufStartFrame;  // Buffer Start Frame
byte *p;                 // Pointer declaration for the new received data
byte incomingByte;
byte incomingBytePrev;

typedef struct {
  uint16_t start;
  int16_t steer;
  int16_t speed;
  uint16_t checksum;
} SerialCommand;
SerialCommand Command;

typedef struct {
  uint16_t start;
  int16_t cmd1;
  int16_t cmd2;
  int16_t speedR_meas;
  int16_t speedL_meas;
  int16_t batVoltage;
  int16_t boardTemp;
  uint16_t cmdLed;
  uint16_t checksum;
} SerialFeedback;
SerialFeedback Feedback;
SerialFeedback NewFeedback;




void setup() {
  Serial.begin(115200);   // USB
  Serial1.begin(115200);  // 0,1
  Serial2.begin(115200);  // 8,9


  HoverSerial1.begin(115200);
  HoverSerial2.begin(115200);
  request_Mavlink();



  pinMode(board1power,  INPUT);
  pinMode(board2power,  INPUT);
  pinMode(board3power,  INPUT);

  pinMode(board1switch, OUTPUT);
  pinMode(board2switch, OUTPUT);
  pinMode(board3switch, OUTPUT);

}






void loop() {

  MavLink_RC();
  //Send(10, 10);
  //delay(10);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= telem) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

  Mavlink_Telemetry1();  

  }
  Receive1();
  //Receive2();
  //Receive3();

  //powercycleon();
  //powercycleoff();


}
