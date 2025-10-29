
//Stowed position - legs above body, folded up

//POTENTIALL DONT DO SET.PWM COMMAND - CHANGE JOINT VARIABLES AND USE XY
//WILL PROBABLY IMPLEMENT SLOW MOVING IN USE XY
//ALWAYS USE CURRENT VS EXPECTED AS IF DEPOWERED IT MAY RUN THROUGH IT ALL


//SNAPS LEGS TO FOLDED UP POSITION
void Dead_dead() { // To be called on setup / reset button
    //START FOLDED UP
    for (int leg = 1; leg<7; leg++){ //ALL LEGS
        New_Theta(leg, 0.0, 75.0, 90.0);
        Current_Theta(leg, 0.0, 75.0, 90.0);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES
}




void Alive_to_dead() { //Fold bot up

    //LIFT LEGS 135 TO X = 0.31, Z = -0.2 //(0.0, 12.9305, -86.2158)
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, 12.9305, -86.2158);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //PUT LEGS 135 down to x=0.31 z=-0.31 (-38.3713) degree thigh, (-28.0837) degree shin
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, -38.3713, -28.0837);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //PUT LEGS 246 to X= 0.39, Z = -0.25 (0.0, -32.1929, -13.8979)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, -32.1929, -13.8979);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //LIFT LEGS 135 TO X = 0.31, Z = -0.2 //(0.0, 12.9305, -86.2158)
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, 12.9305, -86.2158);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //FOLLOWING MOVE TAKES LEGS 246 STRAIGHT UP //MIGHT NEED EXTRA STEP OF MOVING LEGS 135 OUT THE WAY FIRST (PROBABLY NOT??? DUE TO CURRENT ANGLES)
    //LIFT ALL LEGS UP TO X=0.39 Z=0 (0.0, 57.0026, -86.4831) 
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, 57.0026, -86.4831);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //LET BODY TAKE WEIGHT //MAYBE SKIP?
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, 60.0, 0.0);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //FOLD ALL LEGS UP
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, 75.0, 90.0);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    stowed = 0; //COMPLETED SEQUENCE TAG //ROBOT STOWED
    //0 Is Stowed //1 Is Requested Standup //2 Is Standing //3 Is Requested Stow
}


void Dead_to_alive() { 
    //START FOLDED UP
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, 75.0, 90.0);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //UNFOLD
    
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, 60.0, -60.0);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //ALL LEGS ALMOST TAKE WEIGHT AT X=0.39 Z=0 (0.0, 57.0026, -86.4831) 
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, 57.0026, -86.4831);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //ALL LEGS STRAIGHT DOWN TO X= 0.39, Z = -0.1 (0.0, 31.8042, -78.0625)
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, 31.8042, -78.0625);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //ALL LEGS STRAIGHT DOWN TO X= 0.39, Z = -0.2 (0.0, -2.8816, -49.9581)
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, -2.8816, -49.9581);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //ALL LEGS STRAIGHT DOWN TO X= 0.39, Z = -0.25 (0.0, -32.1929, -13.8979)
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, -32.1929, -13.8979);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES
    
    //STEPPING DOWN OF ONLY Z LEVEL WOULD LIKELY NOT BE REQUIRED WITH DYNAMIC ITERATION ANGLES

    //RAISE LEGS 246 TO X = 0.39, Z = -0.15 //(0.0, 15.8530, -67.1251)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, 15.8530, -67.1251);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //SIDEWAYS LEGS 246 TO X = 0.37, Z = -0.1 //(0.0, 37.2258, -87.4181)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, 37.2258, -87.4181);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //DOWN LEGS 246 TO X = 0.37, Z = -0.25 //(0.0, -20.1677, -36.0087)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, -20.1677, -36.0087);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //RAISE LEGS 135 TO X = 0.39, Z = -0.15 //(0.0, 15.8530, -67.1251)
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, 15.8530, -67.1251);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //SIDEWAYS LEGS 135 TO X = 0.31, Z = -0.2 //(0.0, 12.9305, -86.2158)
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, 12.9305, -86.2158);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //PUT LEGS 135 STRAIGHT DOWN TO x=0.31 z=-0.25 (0.0, -7.0721, -66.8352)
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, -7.0721, -66.8352);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //REPEAT LAST THREE STEPS FOR OTHER LEGS

    //RAISE LEGS 246 TO X = 0.39, Z = -0.15 //(0.0, 15.8530, -67.1251)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, 15.8530, -67.1251);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //SIDEWAYS LEGS 246 TO X = 0.31, Z = -0.2 //(0.0, 12.9305, -86.2158)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, 12.9305, -86.2158);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //PUT LEGS 246 STRAIGHT DOWN TO x=0.31 z=-0.25 (0.0, -7.0721, -66.8352)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, -7.0721, -66.8352);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //PUT ALL LEGS STRAIGHT DOWN TO x=0.31 z=-0.31 (0.0, -38.3713, -28.0837)
    for (int leg = 1; leg<7; leg++){//ALL LEGS
        New_Theta(leg, 0.0, -38.3713, -28.0837);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //MOVE ABOVE HOME / MID POINT AT Z=-0.31
    //PUT LEGS 246 TO X= 0.18, Z = -0.28 (0.0, -18.3700, -85.1958) 
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, -18.3700, -85.1958);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //SHOULD BE HOME / MID POINT AT Z=-0.31
    //MOVE LEGS 246 STRAIGHT DOWN TO X= 0.18, Z = -0.31 (0.0, -30.5120, -70.0447)
    for (int leg = 2; leg<7; leg+=2){//LEGS 246
        New_Theta(leg, 0.0, -30.5120, -70.0447);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //REPEAT LAST TWO FOR LEGS 135

    //MOVE ABOVE HOME / MID POINT AT Z=-0.31
    //PUT LEGS 135 TO X= 0.18, Z = -0.28 (0.0, -18.3700, -85.1958) 
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, -18.3700, -85.1958);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    //SHOULD BE HOME / MID POINT AT Z=-0.31
    //MOVE LEGS 135 STRAIGHT DOWN TO X= 0.18, Z = -0.31 (0.0, -30.5120, -70.0447)
    for (int leg = 1; leg<7; leg+=2){//LEGS 135
        New_Theta(leg, 0.0, -30.5120, -70.0447);
    }
    Use_Theta(); //ITERATES ALL LEG TOWARD GOAL ANGLES

    stowed = 2; //COMPLETED SEQUENCE TAG //ROBOT STANDING
    //0 Is Stowed //1 Is Requested Standup //2 Is Standing //3 Is Requested Stow
}
