//Esp32
#include <dummy.h>
#include <math.h>

//Ps3ControllerInterface
//#include "Bluetooth.h"

//PCA9685
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//Variables
#include "Limb_Const.h"
#include "Function_Declarations.h"

float direction[1][1]; //[0][1] is left stick //[1][1] is right stick


float LegAngles[8][5]={            //STARTUP CONDITION -- LEGS FOLDED UP ABOVE BODY
    {0.0, 0.0,  0.0,  0.0, 0.0},     //EMPTY
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG1
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG2
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG3
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG4
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG5
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG6
    {0.0, 0.0,  0.0,  0.0, 0.0},     //EMPTY
};

float NextLegAngles[8][5] ={       //NEXT POSITION STARTUP 
    {0.0, 0.0,  0.0,  0.0, 0.0},     //EMPTY
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG1
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG2
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG3
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG4
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG5
    {0.0, 0.0, 75.0, 90.0, 0.0},     //LEG6
    {0.0, 0.0,  0.0,  0.0, 0.0},     //EMPTY
}; 

float LegCoords[8][9]={0.0}; // XYZ   INCLUDES INITIAL POSITION, CURRENT POSITION AND FINAL POSITION
float Servovals[7][4]={0.0}; // SERVO VALUES - Values going into servo set.pwm command

float servmin = 100.0;
float mid = 290;
float servmax = 480.0;
//ABSOLUTE LIMITS ARE 80-500


bool Legdirection[8][4]; //0 is lowered - 1 is raised
float CoordIntervals[8][4]={0.0}; // INCREMENTAL STEP DISTANCE


int move = 0; //0 Is Neutral // 1 Is Move // 2 Is Turn // 3 Is ArmedQuad // 4 Is Home
int stowed = 0; //0 Is Stowed //1 Is Requested Standup //2 Is Standing //3 Is Requested Stow


bool leftinput = 0; //0 Is Left Joystick Idle //1 Is Left Joystick New Input
bool rightinput = 0; //0 Is Right Joystick Idle //1 Is Right Joystick New Input

int rerun = 0; //0 Is no rerun of joint movement //1 is rerun

int step = 0;
int stepmax=21; //also used weirdly in coord intervals and current xy (stepmax-11) means cant be changed - also hardcoded step 5 in Home()
float stepheight = 0.03;

// you can also call it with a different address and I2C interface (0x40) (0x41)
Adafruit_PWMServoDriver pwm123 = Adafruit_PWMServoDriver(0x40); //LEGS 1/2/3
Adafruit_PWMServoDriver pwm456 = Adafruit_PWMServoDriver(0x41); //LEGS 4/5/6

//Forward Kinematics - Angles (degrees) to Coordinates (x,y,z)

void setup()
{
    Serial.begin(115200);

    //PS3 CONTROLLER INTERFACING. FROM Bluetooth.ino
    Ps3setup();

    //PCA9685 CONNECTIONS
    pwm123.begin();
    pwm456.begin();
    uint32_t freq1=pwm123.getOscillatorFrequency();
    uint32_t freq2=pwm456.getOscillatorFrequency();
    Serial.print("Frequency PCA0x40: "); Serial.println(freq1);
    Serial.print("Frequency PCA0x41: "); Serial.println(freq2);

    pwm123.setOscillatorFrequency(25000000);
    pwm456.setOscillatorFrequency(25000000);

    pwm123.setPWMFreq(50);
    pwm456.setPWMFreq(50);

    Wire.setClock(400000); //Fast I2C communication mode

    //Initialise leg directions
    //0 is lowered - 1 is raised
    Legdirection[1][1]=true;Legdirection[3][1]=true;Legdirection[5][1]=true; //RAISE LEGS 135
    Legdirection[2][1]=false;Legdirection[4][1]=false;Legdirection[6][1]=false; //LOWER LEGS 246
    //DONE
    Serial.println("Ready.");
}

void loop()
{

    if (Serial.available() > 0) {

        String command = Serial.readStringUntil('\n'); // Read until newline character
        Serial.print("Command"); Serial.println(command);
        //command.trim(); // Remove leading/trailing whitespace
        // Process the command
        char c=command[0];
        Serial.print("C:");Serial.println(c);
        if (command[0] =='a'){ //UNFOLD
            Dead_to_alive();
            step = 5;
            Serial.println("UNFOLD");
        }
        else if (command[0] =='b'){
            step=0;
            Serial.println("Reset Step");
        }
        else if (command[0] =='c'){
            Serial.println("FOLD UP");
            Alive_to_dead();
            Dead_dead();
            move=0;
        }
        else if (command[0] =='s'){
            step=5;
            Serial.println("WALK LOOP TEST");
            for (int leg = 1; leg<7; leg++){//ALL LEGS
                Get_xy_circle(leg,-0.33); //START END
            }
            move =1; //Start Walk Incrementation
        }
        else if (command[0] =='h'){
            Home();

            move =0;
        }
        else if (command[0] =='p'){
            ArmUp();
        }
        else if (command[0] =='i'){
            ArmInputs[1][1] = 1;
            ArmInputs[6][1] = 1;
        }
        
    }
//0 Is Stowed //1 Is Requested Standup //2 Is Standing //3 Is Requested Stow
    if      (stowed ==0){
        //continue; //UNSURE HOW TO EXIT ALL MOVEMENT COMMANDS WITH CONTINUE
        Serial.println("ROBOT STOWED");
        Dead_dead();
    }
    else if (stowed ==1) { //IF STANDUP REQUESTED
        Serial.println("CALLED DEAD TO ALIVE");
        Dead_to_alive(); //Sets stowed = 3 upon completion of sequence
    }
    else if (stowed ==2){
        //move =1; //???
        Serial.println("ROBOT STANDING");
    }
    else if (stowed ==3) { //IF STOW REQUESTED
        Serial.println("CALLED ALIVE TO DEAD");
        Alive_to_dead(); //Sets stowed = 1 upon completion of sequence
    }

//IF GATE THE REST OF THE LOOP WITH STOWED ==2 (STANDING)
    if (stowed ==2) {

        if (leftinput == 1) { //LEFT JOYSTICK NEW INPUT CHECK
            step=5; //Home position
            Serial.println("LEFT JOYSITCK INPUT");
            for (int leg = 1; leg<7; leg++){//ALL LEGS
                Get_xy_circle(leg,-0.33); //START END
            }
            move =1;
            leftinput = 0;
        }
        if (rightinput == 1) { //RIGHT JOYSTICK NEW INPUT CHECK
            step=5; //Home position
            Serial.println("LEFT JOYSITCK INPUT");
            for (int leg = 1; leg<7; leg++){//ALL LEGS
                Get_xy_circle(leg,-0.33); //START END
            }
            move =1;
            rightinput = 0;
        }


        /*if (direction[0][0] < 12.0) { //Check if movment input is zeroed - cancel stepping sequence
            move = 0;
            Home();
        }*/
        if (direction[0][0] >12.0) { //execute movment if input is sufficient
            move = 1; //Execute next if statement
        }

        if (move ==1){
            Increment_Walk(); //ITERATE POSITION FOR STEP
            Use_xy(); //IK -- UPDATES NEW THETA MATRIX
        }
        if (move ==3){
            CheckArm(); //CHECK FOR NEW ARM INPUTS AND EXECUTE
        }
        if (move ==4){
            Home();
            move =0;
        }
        for (int leg=1; leg<7; leg++){
            Current_Theta(leg, NextLegAngles[leg][1], NextLegAngles[leg][2], NextLegAngles[leg][3]); //BYPASS THETA INCREMENTING
        }
        Theta_to_Servo(); //Convert incremented thetas to servo values //HAS LIMITED THETA INPUTS HERE
        Export_to_Servos(); //Send incremented servo values to servos


        //Use_Theta();

        Serial.println("100 delay"); delay(100); 
        
        //STEP HANDLING
        Serial.print("STEP: "); Serial.println(step);
        if (move ==1){
            if (step == stepmax){
                step = 0;
            }
            else {
                step = step+1;
            }
        }
    }
}
