

//GO FROM WALK TO ARMED QUADRUPED
void ArmUp() {
    move =3; //CHANGE MOVE STATUS

//SHIFT WEIGHT BACK 
    //PUSH FRONT LEGS DOWN (LEGS 1/6)     //X=0.10, Z=-0.35     //MINRAD = 0.0  //MAXRAD = 0.25
    CurrentCart(1, 0.1, 0.0, -0.35);
    IK(1, 0.1, 0.0, -0.35);
    CurrentCart(6, 0.1, 0.0, -0.35); //BECAUSE LEGS 1/6 ARE USED FOR ARMS THEY NEED THEIR CART MATRIX UPDATED
    IK(6, 0.1, 0.0, -0.35);

    //NEUTRAL MIDDLE LEGS (LEGS 2/5)
    New_Theta(2, 15.0, -15.0, -85.0);
    New_Theta(5, -15.0, -15.0, -85.0);

    //LIFT BACK LEGS UP (LEGS 3/4)        //X=0.39, Z=-0.25     //MINRAD = 0.24 //MAXRAD = 0.38
    IK(3, 0.35, 0.0, -0.25);
    IK(4, 0.35, 0.0, -0.25);
    
    //EXECUTE MOVE
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

//PULL FRONT LEGS UP TO NEUTRAL
    //LIFT FRONT LEGS (LEGS 1/6) //X=0.45, Z=-0.0766 // (0.0, 16.5140, -45.4164) 
    CurrentCart(1, 0.45, 0.0, -0.0766);
    IK(1, 0.45, 0.0, -0.0766);
    CurrentCart(6, 0.45, 0.0, -0.0766); //BECAUSE LEGS 1/6 ARE USED FOR ARMS THEY NEED THEIR CART MATRIX UPDATED
    IK(6, 0.45, 0.0, -0.0766);
    //EXECUTE MOVE 
    Use_Theta();
}
float ArmInputs[7][8]={0}; //[1][] AND [6][] //[][1] +X //[][2] -X //[][3] +Y //[][4] -Y //[][5] +Z //[][6] -Z
float inc = 0.01;        //HOW MUCH TO INCREMENT COORDS BY
void CheckArm() {
    Serial.println("LOOKING AT ARM COORDS");
    //Serial.print(LegCoords[1][3]);Serial.print("  ");Serial.print(LegCoords[1][4]);Serial.print("  ");Serial.println(LegCoords[1][5]);
    //Serial.print(LegCoords[6][3]);Serial.print("  ");Serial.print(LegCoords[6][4]);Serial.print("  ");Serial.println(LegCoords[6][5]);

    //WAS HANDLED WITH FOR LOOP BUT IMPLENTATION OF ANGLES EASIER WITHOUT//for (int leg=1; leg<7; leg+=5) { //LEG 1/6
    
    //leg 1
    if (ArmInputs[1][1] == 1){ //FORWARD
        //Serial.print(LegCoords[leg][3]);Serial.print("  ");Serial.print(LegCoords[leg][4]);Serial.print("  ");Serial.print(LegCoords[leg][5]);
        if (IK(1, LegCoords[1][3]+inc*cos(30), LegCoords[1][4]+inc*sin(30), LegCoords[1][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[1][3]=LegCoords[1][3]+inc*cos(30); //CONFIRM COORD CHANGE
            LegCoords[1][4]=LegCoords[1][4]+inc*sin(30);
        }
    }
    if (ArmInputs[1][2] == 1){ //BACK
        if (IK(1, LegCoords[1][3]+inc*cos(-150), LegCoords[1][4]+inc*sin(-150), LegCoords[1][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[1][3]=LegCoords[1][3]+inc*cos(-150); //CONFIRM COORD CHANGE
            LegCoords[1][3]=LegCoords[1][3]+inc*sin(-150); //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[1][3] == 1){ //LEFT
        if (IK(1, LegCoords[1][3]+inc*cos(120), LegCoords[1][4]+inc*sin(120), LegCoords[1][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[1][4]=LegCoords[1][4]+inc*cos(120); //CONFIRM COORD CHANGE
            LegCoords[1][4]=LegCoords[1][4]+inc*sin(120); //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[1][4] == 1){ //RIGHT
        if (IK(1, LegCoords[1][3]+inc*cos(-60), LegCoords[1][4]+inc*sin(-60), LegCoords[1][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[1][4]=LegCoords[1][4]+inc*cos(-60); //CONFIRM COORD CHANGE
            LegCoords[1][4]=LegCoords[1][4]+inc*sin(-60); //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[1][5] == 1){
        if (IK(1, LegCoords[1][3], LegCoords[1][4], LegCoords[1][5]+inc)) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[1][5]=LegCoords[1][5]+inc; //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[1][6] == 1){
        if (IK(1, LegCoords[1][3], LegCoords[1][4], LegCoords[1][5]-inc)) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[1][5]=LegCoords[1][5]-inc; //CONFIRM COORD CHANGE
        }
    }

    //leg 6
    if (ArmInputs[6][1] == 1){ //FORWARD
        //Serial.print(LegCoords[leg][3]);Serial.print("  ");Serial.print(LegCoords[leg][4]);Serial.print("  ");Serial.print(LegCoords[leg][5]);
        if (IK(6, LegCoords[6][3]+inc*cos(-30), LegCoords[6][4]+inc*sin(-30), LegCoords[6][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[6][3]=LegCoords[6][3]+inc*cos(-30); //CONFIRM COORD CHANGE
            LegCoords[6][4]=LegCoords[6][4]+inc*sin(-30);
        }
    }
    if (ArmInputs[6][2] == 1){ //BACK
        if (IK(6, LegCoords[6][3]+inc*cos(150), LegCoords[6][4]+inc*sin(150), LegCoords[6][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[6][3]=LegCoords[6][3]+inc*cos(150); //CONFIRM COORD CHANGE
            LegCoords[6][3]=LegCoords[6][3]+inc*sin(150); //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[6][3] == 1){ //LEFT
        if (IK(6, LegCoords[6][3]+inc*cos(60), LegCoords[6][4]+inc*sin(60), LegCoords[6][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[6][4]=LegCoords[6][4]+inc*cos(60); //CONFIRM COORD CHANGE
            LegCoords[6][4]=LegCoords[6][4]+inc*sin(60); //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[6][4] == 1){ //RIGHT
        if (IK(6, LegCoords[6][3]+inc*cos(-120), LegCoords[6][4]+inc*sin(-120), LegCoords[6][5])) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[6][4]=LegCoords[6][4]+inc*cos(-120); //CONFIRM COORD CHANGE
            LegCoords[6][4]=LegCoords[6][4]+inc*sin(-120); //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[6][5] == 1){
        if (IK(6, LegCoords[6][3], LegCoords[6][4], LegCoords[6][5]+inc)) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[6][5]=LegCoords[6][5]+inc; //CONFIRM COORD CHANGE
        }
    }
    if (ArmInputs[6][6] == 1){
        if (IK(6, LegCoords[6][3], LegCoords[6][4], LegCoords[6][5]-inc)) { //IF THETAS VALID -- IK AUTO UPDATES NEW THETA
            LegCoords[6][5]=LegCoords[6][5]-inc; //CONFIRM COORD CHANGE
        }
    }

    //RESET ALL INCREMENT INPUTS TO 0
    for (int leg=1; leg<7; leg+=5) {    //LEG 1/6
        for (int i=1; i<7; i++){        //1<6
            ArmInputs[leg][i] = 0;
        }
    }
}












