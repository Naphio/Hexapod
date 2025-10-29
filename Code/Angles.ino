
//        6----1
//       /      \
//      5        2
//       \      /
//        4----3


//New_Theta() - Update the next position for individual legs

//Use_Theta() - Iterate all legs from their current position to their next position
//Function above repeats until end positions are met


//Theta_to_Servo() - Convert thetas to servo values //CALLED IN Use_Theta()

//Export_to_Servos() - Send the servo values to the servos //CALLED IN Use_Theta()


//CHANGE THETAS FOR SPECIFIC LEG
void New_Theta(int leg, float th1, float th2, float th3) {
    NextLegAngles[leg][1]=th1;
    NextLegAngles[leg][2]=th2;
    NextLegAngles[leg][3]=th3;
}
//BELOW IS CURRENTLY ONLY INTENDED FOR USE IN SETUP (Dead_dead() function)
void Current_Theta(int leg, float th1, float th2, float th3) { //THIS FUNCTION BYPASSES STEP THROUGH // WILL CAUSE VERY SNAPPY MOVEMENT
    LegAngles[leg][1]=th1;
    LegAngles[leg][2]=th2;
    LegAngles[leg][3]=th3;    
}

//GO TO NEW THETAS IN INCREMENTS
//float allowance = 10.0; //How many degrees the servo can move at once
float allowance[7][4]={0.0};         //INITIAL ALLOWANCES

//ITS POSSIBLE THAT EXACT INCREMENTS MAY CAUSE ISSUES
//MIGHT NEED TO SCALE BASED ON DIFFERENCE BETWEEN CURRENT AND TARGET
float IncrementCount = 4;

void Use_Theta() {
    for (int leg=1; leg<7; leg++) { //Iterate through all legs
        //DYNAMIC INCREMENT
        allowance[leg][1] = abs(NextLegAngles[leg][1]-LegAngles[leg][1])/IncrementCount;
        allowance[leg][2] = abs(NextLegAngles[leg][2]-LegAngles[leg][2])/IncrementCount;
        allowance[leg][3] = abs(NextLegAngles[leg][3]-LegAngles[leg][3])/IncrementCount;
    }
    do {
        rerun = 0;
        for (int leg=1; leg<7; leg++) { //Iterate through all legs
            float th1 = NextLegAngles[leg][1];
            float th2 = NextLegAngles[leg][2];
            float th3 = NextLegAngles[leg][3];

            //Serial.print(leg);Serial.print(th1);Serial.print(th2);Serial.println(th3);
            if((th1>=J1MIN) && (th1<=J1MAX) && (th2>=J2MIN) && (th2<=J2MAX) && (th3>=J3MIN) && (th3<=J3MAX)){ //CHECK THETAS IN BOUNDS
                //THETA 1
                if ((th1 - LegAngles[leg][1]) > allowance[leg][1]){ //Check current leg1 Angle1 against requested position
                    LegAngles[leg][1] = LegAngles[leg][1] + allowance[leg][1];//if change in value outside allowance then alter to current +allowance
                    rerun = 1;
                }
                else if ((th1 - LegAngles[leg][1]) < -allowance[leg][1]){ //Check current leg1 Angle1 against requested position
                    LegAngles[leg][1] = LegAngles[leg][1] - allowance[leg][1];//if change in value outside allowance then alter to current -allowance
                    rerun = 1;
                }
                else {
                    LegAngles[leg][1] = th1;
                }

                //THETA 2
                if ((th2 - LegAngles[leg][2]) > allowance[leg][2]){ //Check current leg1 Angle1 against requested position
                    LegAngles[leg][2] = LegAngles[leg][2] + allowance[leg][2];//if change in value outside allowance then alter to current +allowance
                    rerun = 1;
                }
                else if ((th2 - LegAngles[leg][2]) < -allowance[leg][2]){ //Check current leg1 Angle1 against requested position
                    LegAngles[leg][2] = LegAngles[leg][2] - allowance[leg][2];//if change in value outside allowance then alter to current -allowance
                    rerun = 1;
                }
                else {
                    LegAngles[leg][2] = th2;
                }

                //THETA 3
                if ((th3 - LegAngles[leg][3]) > allowance[leg][3]){ //Check current leg1 Angle1 against requested position
                    LegAngles[leg][3] = LegAngles[leg][3] + allowance[leg][3];//if change in value outside allowance then alter to current +allowance
                    rerun = 1;
                }
                else if ((th3 - LegAngles[leg][3]) < -allowance[leg][3]){ //Check current leg1 Angle1 against requested position
                    LegAngles[leg][3] = LegAngles[leg][3] - allowance[leg][3];//if change in value outside allowance then alter to current -allowance
                    rerun = 1;
                }
                else {
                    LegAngles[leg][3] = th3;
                }
            }
            else{
                Serial.print("INVALID THETAS LEG: ");Serial.println(leg);
            }
        }
        Theta_to_Servo(); //Convert incremented thetas to servo values
        //CHANGE TO LEG SPECIFIC

        Export_to_Servos(); //Send incremented servo values to servos
        //KEEP AS ALL LEGS

        //delay(20); //HOW LONG BETWEEN ALLOWANCE ANGLE ADJUSTMENTS
    }while (rerun != 0);
}

//RECHECK THETAS ARE WITHIN BOUNDS AND CONVERT TO SERVO VALUES AS BELOW
//ServoMIN + (theta+90)*(ServoMAX-ServoMIN)/(DegreeMAX-DegreeMIN)
//100      + (Theta+90)*(480     -  100   )/(90       - (-90)   )
void Theta_to_Servo() {
    for (int leg = 1; leg<7; leg++){ //Loop through all legs
        float th1 = LegAngles[leg][1];
        float th2 = LegAngles[leg][2];
        float th3 = LegAngles[leg][3];
        //Serial.println(th1);Serial.println(th2);Serial.println(th3);

        //BELOW BOUNDS CHECK IS CARRIED OUT IN NEW_THETA -- PARANOID CHECK HERE
        if((th1>=J1MIN) && (th1<=J1MAX) && (th2>=J2MIN) && (th2<=J2MAX) && (th3>=J3MIN) && (th3<=J3MAX)) { //limit values to +- 90 degrees
            //Serial.println("Thetas acceptable");
            float servoval1 = 100 + (th1+90)*380/180; // Converts 0<180 to 0<380 and start it from lower limit of 100
            Servovals[leg][1]=servoval1;
            //Serial.print("Leg: "); Serial.print(leg); Serial.print("    Value into servo1: "); Serial.println(servoval1);  


            float servoval2 = 100 + (th2+90)*380/180; // Converts 0<180 to 0<380 and start it from lower limit of 100
            Servovals[leg][2]=servoval2;
            //Serial.print("Value into servo2: "); Serial.println(servoval2);  


            float servoval3 = 100 + (th3+90)*380/180; // Converts 0<180 to 0<380 and start it from lower limit of 100
            Servovals[leg][3]=servoval3;
            //Serial.print("Value into servo3: "); Serial.println(servoval3);  
            //Serial.println(servoval1);Serial.println(servoval2);Serial.println(servoval3);
        }
        else {
            Serial.println("INVALID THETAS");
        }
    }    
}



//CHECK ALL SERVO VALS ARE WITHIN BOUNDS AND EXPORT TO PCA PWMS
void Export_to_Servos() { 

    //SERVOS ON PCA 123
    for (int leg = 1; leg<4; leg++){ //Iterate through legs 123
        for (int servo = 1; servo<4; servo++){ //Iterate through each servo in the leg
            if ((Servovals[leg][servo]>=servmin) && (Servovals[leg][servo]<=servmax)) { //CHECK BOUNDS
                //delay(10);
                pwm123.setPWM(Servos[leg][servo], 0, Servovals[leg][servo]);
                delay(10);//5ms delay for I2C comms
                //Serial.print("Servo"); Serial.print(Servos[leg][servo]);Serial.print("   SetPWM: ");Serial.println(Servovals[leg][servo]); //DEBUG
            }
        }
    }
    //DIFFERENT LOOPS AS PWM123 AND PWM456 ARE DIFFERENT

    //SERVOS ON PCA 456
    for (int leg = 4; leg<7; leg++){ //Iterate through legs 456
        for (int servo = 1; servo<4; servo++){ //Iterate through each servo in the leg
            if ((Servovals[leg][servo]>=servmin) && (Servovals[leg][servo]<=servmax)) { //CHECK BOUNDS
                //delay(10);
                pwm456.setPWM(Servos[leg][servo], 0, Servovals[leg][servo]);
                delay(10);//5ms delay for I2C comms
                //Serial.print("SetPWM: ");Serial.println(Servovals[leg][servo]); //DEBUG
            }
        }
    }

    //delay(1000);Serial.println("500 delay");
}