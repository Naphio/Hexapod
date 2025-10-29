#ifndef FUNC_DEC_H
#define FUNC_DEC_H

//Kinematics.ino
bool IK(int legno, float x, float y, float z);

//Bluetooth.ino
void onConnect();
void Ps3setup();
void inputs();

//Dead.ino
void Dead_dead();
void Alive_to_dead();
void Dead_to_alive();

//Home.ino
void Home();
void Get_xy_turn(int leg, float height);
void Get_xy_circle(int leg, float height);

//ThetaToServo.ino
void New_Theta(int leg, float th1, float th2, float th3);
void Current_Theta(int leg, float th1, float th2, float th3);
void Use_Theta();
void Theta_to_Servo();
void Export_to_Servos();


//Cartesian.ino
void StartCart(int leg, float x, float y, float z);
void CurrentCart(int leg, float x, float y, float z);
void EndCart(int leg, float x, float y, float z);
void Interval_xy(int leg, int interval);
void StandardIncrement(int leg);
void UseCart(int interval);
void Get_xy(int leg, float height);
void Increment_Walk();
void Use_xy();

//Angles.ino
void New_Theta(int leg, float th1, float th2, float th3);
void Current_Theta(int leg, float th1, float th2, float th3);
void Use_Theta();
void Theta_to_Servo();
void Export_to_Servos();

//ArmedQuad.ino
void ArmUp();
void CheckArm();
extern float ArmInputs[7][8];
#endif 