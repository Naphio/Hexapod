
//CHANGE THETAS FOR SPECIFIC LEG
void StartCart(int leg, float x, float y, float z) {
    LegCoords[leg][0]=x;
    LegCoords[leg][1]=y;
    LegCoords[leg][2]=z;
}
void CurrentCart(int leg, float x, float y, float z) { //THIS FUNCTION BYPASSES STEP THROUGH // WILL CAUSE VERY SNAPPY MOVEMENT
    LegCoords[leg][3]=x;
    LegCoords[leg][4]=y;
    LegCoords[leg][5]=z;    
}
void EndCart(int leg, float x, float y, float z) { //THIS FUNCTION BYPASSES STEP THROUGH // WILL CAUSE VERY SNAPPY MOVEMENT
    LegCoords[leg][6]=x;
    LegCoords[leg][7]=y;
    LegCoords[leg][8]=z;    
}

//GENERATES INTERVAL BETWEEN START AND END CART POSITIONS //AMOUNT BY PARAMETER
void Interval_xy(int leg, int interval) {
    CoordIntervals[leg][0] = (LegCoords[leg][0] - LegCoords[leg][6])/(interval);
    CoordIntervals[leg][1] = (LegCoords[leg][1] - LegCoords[leg][7])/(interval);
    CoordIntervals[leg][2] = (LegCoords[leg][2] - LegCoords[leg][8])/(interval);
    //Serial.println("coordint3: "+ String(CoordIntervals[leg][2]));
    //Serial.println("coordint1: "+String(CoordIntervals[leg][0])); Serial.println("coordint2: "+String(CoordIntervals[leg][1])); Serial.println("coordint3: "+ String(CoordIntervals[leg][2]));
}
//MINUS ONE INTERVAL FROM CURRENT POSITION (TOWARD END POSITION)
void StandardIncrement(int leg) {

    LegCoords[leg][3] = LegCoords[leg][3]-CoordIntervals[leg][0];
    LegCoords[leg][4] = LegCoords[leg][4]-CoordIntervals[leg][1];
    LegCoords[leg][5] = LegCoords[leg][5]-CoordIntervals[leg][2];
}

void UseCart(int interval){
    for (int inv=1; inv<interval; inv++){
        //FIND ANGLES
        IK(1, LegCoords[1][3],LegCoords[1][4],LegCoords[1][5]);
        IK(2, LegCoords[2][3],LegCoords[2][4],LegCoords[2][5]);
        IK(3, LegCoords[3][3],LegCoords[3][4],LegCoords[3][5]);
        IK(4, LegCoords[4][3],LegCoords[4][4],LegCoords[4][5]);
        IK(5, LegCoords[5][3],LegCoords[5][4],LegCoords[5][5]); 
        IK(6, LegCoords[6][3],LegCoords[6][4],LegCoords[6][5]); 
        //USE ANGLES


        //Use_Theta();   
        //INCREMENT XYZ
        StandardIncrement(1);
        StandardIncrement(2);
        StandardIncrement(3);
        StandardIncrement(4);
        StandardIncrement(5);
        StandardIncrement(6); 
    }
}

//GET START AND END XY VALUES BASED ON INPUT ANGLE FROM PS3 CONTROLLER JOYSTICK
void Get_xy(int leg, float height){ // SHOULD ONLY BE CALLED WHEN DIRECTION INPUT CHANGES
    Serial.println("GETXY REACHED");//DEBUG
    //Serial.println(height);//DEBUG
    //direction[0][1] = 0.0; //-PI < PI
    float angle1;
    if (direction[0][1] < 0.0) {
        angle1 = 360.0 + direction[0][1];   //180<360
    }
    else {
        angle1 = direction[0][1];       //0<180
    }
    /*Serial.print("Angle1: "); Serial.println(angle1);
    Serial.print("Lower: "); Serial.println(-60.0+60.0*(leg-1));
    Serial.print("Higher: "); Serial.println(120.0+60.0*(leg-1));*/

    angle1 = direction[0][1]+30.0+60.0*(leg-1); // CONVERT GENERAL DIRECTION TO DIRECTION FOR EACH LEG    
    //CONVERT 0<360 GENERAL DIRECTION BACK TO GENERAL RANGE -PI < PI
    if (angle1>180.0){
        angle1=angle1-360.0;
    }

    //Determine if angle is between 180 degree arc of each leg
    //VALUES 0.31 and 0.1 are pulled from matlab calc as the max for height of -0.31
    //0.1 altered to 0.05 due to ugly calc
    float c1;//maybe make constant
    float c2;
    if ((angle1>=-90.0) && (angle1< 90.0)){
        c1 = 0.28;
        c2 = 0.02;
    }
    else {
        c1 = 0.02;
        c2 = 0.28;
    }
    //IF WITHIN -90<90, GIVE LARGER RADIUS //ELSE GIVE SMALLER

    float angle2;
    //Determine angle that is 180 from initial angle (END POINT)
    if (angle1>0) {
        angle2 = angle1-180.0;
    }
    else if (angle1<=0) {
        angle2 = angle1+180.0;
    }
    //Serial.print(angle1); Serial.println(angle2); //DEBUG
    

    //SWAP DIRECTION FOR EACH 2ND LEG
    float xp1;
    float yp1;
    float xp2;
    float yp2;
    if (leg % 2 == 0) { //SWAP START / FINISH xp1/xp2 FOR EVERY SECOND LEG
        xp1 = c1*cos(M_PI*(angle1)/180);
        yp1 = c1*sin(M_PI*(angle1)/180);
        xp2 = c2*cos(M_PI*(angle2)/180);
        yp2 = c2*sin(M_PI*(angle2)/180);
    }
    else { 
        xp1 = c2*cos(M_PI*(angle2)/180);
        yp1 = c2*sin(M_PI*(angle2)/180);
        xp2 = c1*cos(M_PI*(angle1)/180);
        yp2 = c1*sin(M_PI*(angle1)/180);    
    }

    //EXPORT COORDS TO COORD MATRIX
    LegCoords[leg][0]=xp1;
    LegCoords[leg][1]=yp1;
    LegCoords[leg][2]=height;
    LegCoords[leg][6]=xp2;
    LegCoords[leg][7]=yp2;
    LegCoords[leg][8]=height;

    /*Serial.print("xp1: "); Serial.println(xp1);
    Serial.print("yp1: "); Serial.println(yp1);
    Serial.print("zp1: "); Serial.println(LegCoords[leg][2]);
    Serial.print("xp2: "); Serial.println(xp2);
    Serial.print("yp2: "); Serial.println(yp2);    
    Serial.print("zp2: "); Serial.println(LegCoords[leg][8]);*/

    Interval_xy(leg, 10); //10 INTERVALS FOR STANDARD WALK LOOP (21 START TO END TO START)
}

//SPECIFIC TO WALKING //USES 21 STEP PROCESS
void Increment_Walk() {
    Serial.println("CURRENTXY REACHED");//DEBUG
    //THIS IS WITH HARDCODED 0->21 STEPS
    for (int leg = 1; leg<7; leg++){ //Loop through all legs
        if (step == 0) {
            LegCoords[leg][3] = LegCoords[leg][0]; //Current x = Initial x
            LegCoords[leg][4] = LegCoords[leg][1];
            LegCoords[leg][5] = LegCoords[leg][2];
        }
        else if (step == 10){ 
            LegCoords[leg][3] = LegCoords[leg][6]; //Current x = Final x
            LegCoords[leg][4] = LegCoords[leg][7];
            LegCoords[leg][5] = LegCoords[leg][8];
            Legdirection[leg][1] = !Legdirection[leg][1]; //Invert leg direction
        }
        else if (step == 11){ //STEP UP AND OVER FINAL POINT
            LegCoords[leg][3] = LegCoords[leg][6]; //Current x = Final x
            LegCoords[leg][4] = LegCoords[leg][7];
            LegCoords[leg][5] = stepheight*Legdirection[leg][1] + LegCoords[leg][8];
        }
        else if (step == 21){ //STEP UP AND OVER INITIAL POINT
            LegCoords[leg][3] = LegCoords[leg][0]; //Current x = Initial x
            LegCoords[leg][4] = LegCoords[leg][1];
            LegCoords[leg][5] = stepheight*Legdirection[leg][1] + LegCoords[leg][2];
            Legdirection[leg][1] = !Legdirection[leg][1]; //Invert leg direction
        }
        else if ((step>0) && (step<10)) { //Make current initial - interval * step to allow for changing input while maintaining step
            LegCoords[leg][3] = LegCoords[leg][0]-step*CoordIntervals[leg][0]; //Current x = Initial x - step*interval
            LegCoords[leg][4] = LegCoords[leg][1]-step*CoordIntervals[leg][1];
            LegCoords[leg][5] = stepheight*Legdirection[leg][1] + LegCoords[leg][2]-step*CoordIntervals[leg][2];
        }
        else if ((step>11) && (step<21)) { //Make current final + interval * step to allow for changing input while maintaining step
            LegCoords[leg][3] = LegCoords[leg][6]+(step-11)*CoordIntervals[leg][0]; //Current x = Initial x - step*interval
            LegCoords[leg][4] = LegCoords[leg][7]+(step-11)*CoordIntervals[leg][1];
            LegCoords[leg][5] = stepheight*Legdirection[leg][1] + LegCoords[leg][8]+(step-11)*CoordIntervals[leg][2];
        }
        //LegCoords[leg][5] = stepheight*Legdirection[leg][1] + LegCoords[leg][5]; //ADD height to z to leg heading backwards
        //STEP HEIGHT HANDLED WITHIN STEP 0<10 and 11<21 //STEPS 0,10,11,21 HAVE ALL LEGS LOWERED //SO THAT STEPPING BETWEEN ISNT AWKWARD
        //MIGHT BE BETTER TO INCLUDE STEP THAT WAITS FOR LEGS TO LOWER THEN RAISES ALTERNATING LEGS
    }
}

//TAKE CURRENT POSITIONS AND INVERSE KINEMATICS THEM AND OUTPUT TO JOINT ANGLES
void Use_xy() {
    Serial.println("USEXY REACHED");//DEBUG

    //UPDATE LEGANGLES MATRIX BY PASSING BELOW DESIRED XYZ THROUGH IK
    //Serial.println("xik: "+String(LegCoords[0][3])); Serial.println("y: "+String(LegCoords[0][4])); Serial.println("z: "+ String(LegCoords[0][5])); // DEBUG
    IK(1, LegCoords[1][3],LegCoords[1][4],LegCoords[1][5]);
    IK(2, LegCoords[2][3],LegCoords[2][4],LegCoords[2][5]);
    IK(3, LegCoords[3][3],LegCoords[3][4],LegCoords[3][5]);
    IK(4, LegCoords[4][3],LegCoords[4][4],LegCoords[4][5]);
    IK(5, LegCoords[5][3],LegCoords[5][4],LegCoords[5][5]); 
    IK(6, LegCoords[6][3],LegCoords[6][4],LegCoords[6][5]); 
    //Serial.println("xik: "+String(LegCoords[5][3])); Serial.println("y: "+String(LegCoords[5][4])); Serial.println("z: "+ String(LegCoords[5][5])); // DEBUG
    /*Serial.println("L1J1: "+ String(NextLegAngles[1][1])); 
    Serial.println("L1J2: "+ String(NextLegAngles[1][2])); 
    Serial.println("L1J3: "+ String(NextLegAngles[1][3])); 

    Serial.println("L2J1: "+ String(NextLegAngles[2][1])); 
    Serial.println("L2J2: "+ String(NextLegAngles[2][2])); 
    Serial.println("L2J3: "+ String(NextLegAngles[2][3])); 

    Serial.println("L3J1: "+ String(NextLegAngles[3][1])); 
    Serial.println("L3J2: "+ String(NextLegAngles[3][2])); 
    Serial.println("L3J3: "+ String(NextLegAngles[3][3])); 

    Serial.println("L4J1: "+ String(NextLegAngles[4][1])); 
    Serial.println("L4J2: "+ String(NextLegAngles[4][2])); 
    Serial.println("L4J3: "+ String(NextLegAngles[4][3])); 

    Serial.println("L5J1: "+ String(NextLegAngles[5][1])); 
    Serial.println("L5J2: "+ String(NextLegAngles[5][2])); 
    Serial.println("L5J3: "+ String(NextLegAngles[5][3])); 

    Serial.println("L6J1: "+ String(NextLegAngles[6][1]));
    Serial.println("L6J2: "+ String(NextLegAngles[6][2]));
    Serial.println("L6J3: "+ String(NextLegAngles[6][3]));*/
}

