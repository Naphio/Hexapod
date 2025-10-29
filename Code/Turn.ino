void Get_xy_turn(int leg, float height) { //NOT CURRENTLY FUNCTIONAL

    float c1;
    float angle1;
    float angle2;

    c1 = 0.28;

    //direction[1][0] IS PURELY X COMPONENT OF JOYSTICK

    if (direction[1][0]>12.0){
        //right turn
        angle1 = -30.0;
        angle2 = 30.0;
    }
    else if (direction[1][0]<-12.0){
        //left turn
        angle1 = 30.0;
        angle2 = -30.0;
    }

    //SWAP DIRECTION FOR EACH 2ND LEG
    float xp1;
    float yp1;
    float xp2;
    float yp2;
    if (leg % 2 == 0) { //SWAP START / FINISH xp1/xp2 FOR EVERY SECOND LEG
        xp1 = c1*cos(M_PI*(angle1)/180);
        yp1 = c1*sin(M_PI*(angle1)/180);
        xp2 = c1*cos(M_PI*(angle2)/180);
        yp2 = c1*sin(M_PI*(angle2)/180);
    }
    else { 
        xp1 = c1*cos(M_PI*(angle2)/180);
        yp1 = c1*sin(M_PI*(angle2)/180);
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

    Serial.print("xp1: "); Serial.println(xp1);
    Serial.print("yp1: "); Serial.println(yp1);
    Serial.print("zp1: "); Serial.println(LegCoords[leg][2]);
    Serial.print("xp2: "); Serial.println(xp2);
    Serial.print("yp2: "); Serial.println(yp2);    
    Serial.print("zp2: "); Serial.println(LegCoords[leg][8]);

    Interval_xy(leg, 10); //10 INTERVALS FOR STANDARD WALK LOOP (21 START TO END TO START)
}

void Get_xy_circle(int leg, float height) {
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
    float c1 = 0.1;//maybe make constant

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
        xp1 = c1*cos(M_PI*(angle1)/180)+0.15;
        yp1 = c1*sin(M_PI*(angle1)/180);
        xp2 = c1*cos(M_PI*(angle2)/180)+0.15;
        yp2 = c1*sin(M_PI*(angle2)/180);
    }
    else { 
        xp1 = c1*cos(M_PI*(angle2)/180)+0.15;
        yp1 = c1*sin(M_PI*(angle2)/180);
        xp2 = c1*cos(M_PI*(angle1)/180)+0.15;
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
