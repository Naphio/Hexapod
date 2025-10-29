


//Inverse Kinematics - Coordinates to Angles
bool IK(int legno, float x, float y, float z){ // MIGHT NOT NEED XYZ INPUT AS THEYRE HELD IN GLOBAL MATRIX
    Serial.println("REACHED_IK");
    Serial.println("legno: "+String(legno));
    Serial.print("x: "+String(x)); Serial.print("    y: "+String(y)); Serial.println(    "z: "+ String(z)); // DEBUG

    //TH1 CALC
    float th1;
    th1 = atan2(y,x);

    //TH2 CALC
    float L1x = (L1)*cos(th1);
    float L1y = (L1)*sin(th1);

    //Serial.println("L1x: "+String(L1x)); Serial.println("L1y: "+String(L1y));

    //Origin to End of L1 limb in xy plane
    float L1xy = sqrt(L1x*L1x+L1y*L1y);

    //Origin to end of leg in xy plane
    float xy = sqrt(x*x+y*y);

    //Serial.print("L1xy: ");Serial.println(L1xy);            //DEBUG
    //Serial.print("xy: ");Serial.println(xy);                //DEBUG

    //End of L1 limb to end of leg in xy plane
    float CE = sqrt((L1x-x)*(L1x-x)+(L1y-y)*(L1y-y));

    //End of L1 Limb to end of leg in xyz
    float L = sqrt(CE*CE+z*z);

    //Serial.print("CE: ");Serial.println(CE);            //DEBUG
    //Serial.print("z: ");Serial.println(z);            //DEBUG

    float q1=0.0;
    //Check if end effector is out further than end of L1 limb or not
    if (xy<L1xy){
        q1 = atan2(z,-CE);
    }
    else if (xy>=L1xy){
        q1 = atan2(z,CE);
    }

    Serial.print("L2: ");Serial.println(L2);          //DEBUG
    Serial.print("L3: ");Serial.println(L3);          //DEBUG
    Serial.print("L: ");Serial.println(L);          //DEBUG

    float q2 = acos((L2*L2+L*L-L3*L3)/(2*L2*L));

    //FOR FRINGE CASE AT 45,0,0 or -45,0,0 where q2 is imaginary 
    if (q2){ //meant to be a real check but no such function in basic math.h for arduino
        q2=q2;
    }
    else{
        q2=0;
    }
    Serial.print("q1: ");Serial.println(q1);          //DEBUG
    Serial.print("q2: ");Serial.println(q2);          //DEBUG

    //Determining how to add and subtract q1 and q2
    float th2=0.0;
    /*if (abs(q1)>M_PI/2){

        if (z>=0){
            th2=q1+q2;
        }
        else if (z<0) {
            th2=q1+q2;
        }
    }
    else if (abs(q1)<=M_PI/2){
        if (z<0){
            th2=q1+q2;
        }
        else if (z>=0){
            th2=q1+q2;
        }
    }*/

    if (z>0) {
        th2=q1-q2;
    }
    else if (z<=0) {
        th2=q1+q2;
    }


    //TH3 CALC
    float phi = acos((L2*L2+L3*L3-L*L)/(2*L2*L3));
    //Serial.println("phi: "+String(phi)); //DEBUG
    //X and Z values for end of Limb 2
    float L2z = L2*sin(th2);
    float L2x = cos(th1)*L2*cos(th2);
    float L2y = sin(th1)*L2*cos(th2);
    float L2xy = sqrt(L2x*L2x+L2y*L2y);

    //Serial.println("L2x: "+String(L2x)); Serial.println("L2z: "+String(L2z)); //DEBUG
    //Find the z value for the end effector x position along the line of Limb 2
    float zi = (L2z/(L2xy))*(x-L1x); //Line of Limb 2 used for th3 calc. Determines if end effector is above or below
    //Serial.println("zi: "+String(zi)); //DEBUG

    float th3=0.0;
    if (z>zi){
        th3=M_PI-phi;
    }
    else if (z<zi){
        th3=phi-M_PI;        
    }
    else if (z==zi){
        th3=0.0;
    }

    //CONVERT TO DEGREES
    th1=th1*180/M_PI;
    th2=th2*180/M_PI;
    th3=th3*180/M_PI;

    //RETURN 1 = VALID THETAS //RETURN 0 = INVALID THETAS 
    if ((th1>J1MIN) && (th1<J1MAX) && (th2>J2MIN) && (th2<J2MAX) && (th3>J3MIN) && (th3<J3MAX)){
        New_Theta(legno, th1, th2, th3);
        return 1;
    }
    else {
        return 0;
    }

    //Serial.println("th1: "+String(th1)); Serial.println("th2: "+String(th2)); Serial.println("th3: "+ String(th3)); // DEBUG
}