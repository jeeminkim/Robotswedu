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
#define FIRST_ID 1
#define SECOND_ID 2
/* Control table defines */
#define GOAL_POSITION 30
#define PRESENT_POSITION 36
#define GOAL_SPEED 32
#define CW_POSITION 6
#define CCW_POSITION 8
#define CW_COMPLIANCE_SLOPE 28
#define CCW_COMPLIANCE_SLOPE 29
#define UPPER_LIMIT 820
#define LOWER_LIMIT 200
#define MOTOR_SPEED 54

Dynamixel Dxl(DXL_BUS_SERIAL3);

int i = 0;
int delay1;
int delay2;
int delay_time;
short current_position1;
short current_position2;

short signal1[24]; short signal2[24];
int len = 24;

void setup() {

  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  Dxl.jointMode(FIRST_ID); //jointMode() is to use position mode
  Dxl.jointMode(SECOND_ID); //jointMode() is to use position mode
  Dxl.writeWord(FIRST_ID, CW_POSITION, LOWER_LIMIT);
  Dxl.writeWord(SECOND_ID, CW_POSITION, LOWER_LIMIT);
  Dxl.writeWord(FIRST_ID, CCW_POSITION, UPPER_LIMIT);
  Dxl.writeWord(SECOND_ID, CCW_POSITION, UPPER_LIMIT);
  Dxl.writeWord(FIRST_ID, GOAL_SPEED, MOTOR_SPEED);
  Dxl.writeWord(SECOND_ID, GOAL_SPEED, MOTOR_SPEED);

  Dxl.writeByte(FIRST_ID, CW_COMPLIANCE_SLOPE, 128);
  Dxl.writeByte(FIRST_ID, CCW_COMPLIANCE_SLOPE, 128);
  Dxl.writeByte(SECOND_ID, CW_COMPLIANCE_SLOPE, 128);
  Dxl.writeByte(SECOND_ID, CCW_COMPLIANCE_SLOPE, 128);

  signal1[0] = 381; signal2[0] = 796;
signal1[1] = 391; signal2[1] = 784;
signal1[2] = 401; signal2[2] = 775;
signal1[3] = 410; signal2[3] = 763;
signal1[4] = 422; signal2[4] = 747;
signal1[5] = 438; signal2[5] = 722;
signal1[6] = 461; signal2[6] = 673;
signal1[7] = 483; signal2[7] = 620;
signal1[8] = 490; signal2[8] = 595;
signal1[9] = 490; signal2[9] = 586;
signal1[10] = 485; signal2[10] = 588;
signal1[11] = 475; signal2[11] = 601;
signal1[12] = 457; signal2[12] = 628;
signal1[13] = 467; signal2[13] = 601;
signal1[14] = 467; signal2[14] = 588;
signal1[15] = 465; signal2[15] = 586;
signal1[16] = 457; signal2[16] = 595;
signal1[17] = 440; signal2[17] = 620;
signal1[18] = 412; signal2[18] = 673;
signal1[19] = 391; signal2[19] = 722;
signal1[20] = 383; signal2[20] = 747;
signal1[21] = 379; signal2[21] = 763;
signal1[22] = 379; signal2[22] = 775;
signal1[23] = 381; signal2[23] = 784;



}

void loop() {  

  current_position1 = Dxl.readWord(FIRST_ID, PRESENT_POSITION);
  current_position2 = Dxl.readWord(SECOND_ID, PRESENT_POSITION);

  Dxl.writeWord(FIRST_ID, GOAL_POSITION, signal1[i]);
  Dxl.writeWord(SECOND_ID, GOAL_POSITION, signal2[i]);

  delay1 = 1000 * abs(signal1[i] - current_position1) * (150.0 / 512) * (PI / 180) / (MOTOR_SPEED * 0.111 * 2 * PI / 60);
  delay2 = 1000 * abs(signal2[i] - current_position2) * (150.0 / 512) * (PI / 180) / (MOTOR_SPEED * 0.111 * 2 * PI / 60);

  delay_time = delay1 > delay2 ? delay1 : delay2;

  delay(delay_time);

  i++; 

  if ( i >= len ){
     i = 0;
  }

}





