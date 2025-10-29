#ifndef LIMB_CONSTANT_H
#define LIMB_CONSTANT_H

float BH=.100; //BODY HEIGHT

float L0 = .12256;
float L1 = .1020;
float L2 = .1420;
float L3 = .2420;

float J1MIN = -90;
float J1MAX = 90;

float J2MIN = -90;
float J2MAX = 90;

float J3MIN = -90;
float J3MAX = 90;


//PWM CHANNEL PER LEG
//int Servos[7][3]; //Legs 1<6 //Servos 0<2
int Servos[7][4] = { //FORM IS: Servos[0][0]); Serial.print(Servos[0][1]); Serial.println(Servos[0][2])
  {0, 0, 0, 0},
  {0, 12, 13, 15}, //L1 J123
  {0, 6, 7, 8}, //L2 J123
  {0, 0, 1, 2}, //L3 J123
  {0, 13, 14, 15}, //L4 J123
  {0, 6, 7, 8}, //L5 J123
  {0, 0, 1, 2}  //L6 J123
};
//Extra column/row due to weird information loss on edge of matrix

#endif