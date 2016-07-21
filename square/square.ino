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

short signal1[32]; short signal2[32];
int len = 32;

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

  signal1[0] = 369; signal2[0] = 821;
signal1[1] = 377; signal2[1] = 820;
signal1[2] = 387; signal2[2] = 819;
signal1[3] = 395; signal2[3] = 818;
signal1[4] = 404; signal2[4] = 815;
signal1[5] = 410; signal2[5] = 798;
signal1[6] = 416; signal2[6] = 781;
signal1[7] = 424; signal2[7] = 762;
signal1[8] = 432; signal2[8] = 743;
signal1[9] = 442; signal2[9] = 721;
signal1[10] = 451; signal2[10] = 697;
signal1[11] = 463; signal2[11] = 670;
signal1[12] = 477; signal2[12] = 638;
signal1[13] = 469; signal2[13] = 642;
signal1[14] = 461; signal2[14] = 645;
signal1[15] = 455; signal2[15] = 647;
signal1[16] = 449; signal2[16] = 647;
signal1[17] = 444; signal2[17] = 647;
signal1[18] = 438; signal2[18] = 645;
signal1[19] = 432; signal2[19] = 642;
signal1[20] = 428; signal2[20] = 638;
signal1[21] = 412; signal2[21] = 670;
signal1[22] = 399; signal2[22] = 697;
signal1[23] = 387; signal2[23] = 721;
signal1[24] = 377; signal2[24] = 743;
signal1[25] = 367; signal2[25] = 762;
signal1[26] = 358; signal2[26] = 781;
signal1[27] = 348; signal2[27] = 798;
signal1[28] = 340; signal2[28] = 815;
signal1[29] = 346; signal2[29] = 818;
signal1[30] = 354; signal2[30] = 819;
signal1[31] = 361; signal2[31] = 820;

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





