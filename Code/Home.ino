int homestep = 5; //step that provides the home position (middle position)

//Hard coded return to home commands - preserves leg direction 
void Home() {
    int del = 2000;
    step = 5;
    //MOVE RAISED LEGS TO ABOVE HOME
    for (int leg=1; leg<7; leg++) {
        if (Legdirection[leg][1] == 1) { //if already raised then go to home (step 5) + step height
            LegCoords[leg][3] = LegCoords[leg][0]-homestep*CoordIntervals[leg][0]; //Current x = Initial x - step*interval
            LegCoords[leg][4] = LegCoords[leg][1]-homestep*CoordIntervals[leg][1];
            LegCoords[leg][5] = stepheight + LegCoords[leg][2]-homestep*CoordIntervals[leg][2];
        }
    }
    Use_xy(); // PERFORM IK ON XYZ //Export to NextThetaAngles
    Use_Theta(); //Thetas to servo values //export to servos

    //Now plant first feet down
    for (int leg=1; leg<7; leg++) {
        if (Legdirection[leg][1] == 1) { //if already raised go down to home
            LegCoords[leg][3] = LegCoords[leg][0]-homestep*CoordIntervals[leg][0]; //Current x = Initial x - step*interval
            LegCoords[leg][4] = LegCoords[leg][1]-homestep*CoordIntervals[leg][1];
            LegCoords[leg][5] = LegCoords[leg][2]-homestep*CoordIntervals[leg][2];
        }
    }    
    Use_xy(); // PERFORM IK ON XYZ //Export to NextThetaAngles
    Use_Theta(); //Thetas to servo values //export to servos


    //Now bring second feet above their current 
    for (int leg=1; leg<7; leg++) {
        if (Legdirection[leg][1] == 0) { //if already down then raise
            LegCoords[leg][3] = LegCoords[leg][3]; //Current x = Initial x - step*interval
            LegCoords[leg][4] = LegCoords[leg][4];
            LegCoords[leg][5] = stepheight + LegCoords[leg][5];
        }
    }    
    Use_xy(); // PERFORM IK ON XYZ //Export to NextThetaAngles
    Use_Theta(); //Thetas to servo values //export to servos


    //Now bring second feet above their home
    for (int leg=1; leg<7; leg++) {
        if (Legdirection[leg][1] == 0) { //if already down raised home
            LegCoords[leg][3] = LegCoords[leg][0]-homestep*CoordIntervals[leg][0]; //Current x = Initial x - step*interval
            LegCoords[leg][4] = LegCoords[leg][1]-homestep*CoordIntervals[leg][1];
            LegCoords[leg][5] = stepheight + LegCoords[leg][2]-homestep*CoordIntervals[leg][2];
        }
    }
    Use_xy(); // PERFORM IK ON XYZ //Export to NextThetaAngles
    Use_Theta(); //Thetas to servo values //export to servos


    //Now bring second feet down to home
    for (int leg=1; leg<7; leg++) {
        if (Legdirection[leg][1] == 0) { //if already down then go down to home
            LegCoords[leg][3] = LegCoords[leg][0]-homestep*CoordIntervals[leg][0]; //Current x = Initial x - step*interval
            LegCoords[leg][4] = LegCoords[leg][1]-homestep*CoordIntervals[leg][1];
            LegCoords[leg][5] = LegCoords[leg][2]-homestep*CoordIntervals[leg][2];
        }
    }
    Use_xy(); // PERFORM IK ON XYZ //Export to NextThetaAngles
    Use_Theta(); //Thetas to servo values //export to servos

}