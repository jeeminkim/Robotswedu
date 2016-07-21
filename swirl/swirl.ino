/* Dynamixel Basic Position Control Example
 
 Turns left the dynamixel , then turn right for one second,
 repeatedly.
 
                   Compatibility
 CM900                  O
 OpenCM9.04             O
 
                  Dynamixel Compatibility
               AX    MX      RX    XL-320    Pro
 CM900          O      O      O        O      X
 OpenCM9.04     O      O      O        O      X
 **** OpenCM 485 EXP board is needed to use 4 pin Dynamixel and Pro Series ****
 
 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */
/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define ID_NUM 1
/* Control table defines */
#define GOAL_POSITION 30
#define CW_POSITION 6
#define CCW_POSITION 8

Dynamixel Dxl(DXL_BUS_SERIAL3);

void setup() {
  
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  Dxl.jointMode(ID_NUM); //jointMode() is to use position mode
  Dxl.jointMode(2); //jointMode() is to use position mode
  Dxl.writeWord(ID_NUM, CW_POSITION, 205);
  Dxl.writeWord(2, CW_POSITION, 205);
  Dxl.writeWord(ID_NUM, CCW_POSITION, 819);
  Dxl.writeWord(2, CCW_POSITION, 819);
}

int i = 512;
int j = 512;
boolean CCW_i = true;
boolean CCW_j = true;
int i_change = 5;
int j_change = 7;

void loop() {  
  //Turn dynamixel ID 1 to position 0
  
  if (CCW_i) {
    i += i_change;
  }
  else {
    i -= i_change;
  }
  
  if (CCW_j) {
    j += j_change;
  }
  else {
    j -= j_change;
  }
  
  if (i > 819) {
    i = 819;
    CCW_i = false;
  }
  
  if (i < 205) {
    i = 205;
    CCW_i = true; 
  }
  
   if (j > 819) {
    j = 819;
    CCW_j = false;
  }
  
  if (j < 205) {
    j = 205;
    CCW_j = true; 
  }
    
  
  Dxl.writeWord(ID_NUM, GOAL_POSITION, i); //Compatible with all dynamixel serise
  Dxl.writeWord(2, GOAL_POSITION, j); //Compatible with all dynamixel serise
  // Wait for 1 second (1000 milliseconds)
  delay(50);                  
}


