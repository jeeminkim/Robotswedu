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

short signal1[50]; short signal2[50];
int len = 50;

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

  signal1[0] = 512; signal2[0] = 512;
signal1[1] = 467; signal2[1] = 602;
signal1[2] = 447; signal2[2] = 640;
signal1[3] = 434; signal2[3] = 669;
signal1[4] = 420; signal2[4] = 694;
signal1[5] = 406; signal2[5] = 716;
signal1[6] = 397; signal2[6] = 735;
signal1[7] = 385; signal2[7] = 754;
signal1[8] = 375; signal2[8] = 771;
signal1[9] = 365; signal2[9] = 787;
signal1[10] = 356; signal2[10] = 802;
signal1[11] = 365; signal2[11] = 794;
signal1[12] = 375; signal2[12] = 785;
signal1[13] = 385; signal2[13] = 775;
signal1[14] = 395; signal2[14] = 764;
signal1[15] = 406; signal2[15] = 753;
signal1[16] = 416; signal2[16] = 741;
signal1[17] = 428; signal2[17] = 728;
signal1[18] = 440; signal2[18] = 713;
signal1[19] = 451; signal2[19] = 698;
signal1[20] = 463; signal2[20] = 680;
signal1[21] = 455; signal2[21] = 684;
signal1[22] = 449; signal2[22] = 687;
signal1[23] = 442; signal2[23] = 689;
signal1[24] = 436; signal2[24] = 690;
signal1[25] = 428; signal2[25] = 690;
signal1[26] = 422; signal2[26] = 690;
signal1[27] = 418; signal2[27] = 689;
signal1[28] = 412; signal2[28] = 687;
signal1[29] = 406; signal2[29] = 684;
signal1[30] = 402; signal2[30] = 680;
signal1[31] = 399; signal2[31] = 698;
signal1[32] = 397; signal2[32] = 713;
signal1[33] = 395; signal2[33] = 728;
signal1[34] = 393; signal2[34] = 741;
signal1[35] = 393; signal2[35] = 753;
signal1[36] = 393; signal2[36] = 764;
signal1[37] = 395; signal2[37] = 775;
signal1[38] = 397; signal2[38] = 785;
signal1[39] = 399; signal2[39] = 794;
signal1[40] = 401; signal2[40] = 802;
signal1[41] = 404; signal2[41] = 787;
signal1[42] = 408; signal2[42] = 771;
signal1[43] = 414; signal2[43] = 754;
signal1[44] = 420; signal2[44] = 735;
signal1[45] = 426; signal2[45] = 716;
signal1[46] = 434; signal2[46] = 694;
signal1[47] = 444; signal2[47] = 669;
signal1[48] = 455; signal2[48] = 640;
signal1[49] = 471; signal2[49] = 602;


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





