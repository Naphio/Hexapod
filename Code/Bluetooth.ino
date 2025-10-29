

//This file makes limited use of publicly available code with unclear licensing status for academic, non-commercial purposes only. No redistribution is intended.//
//The Github source of these files can be found at https://github.com/jvpernis/esp32-ps3.//
//This code allows for the use of a ps3 controller to supply various inputs to the esp32 board via bluetooth communication.//

//The only reference to this code is in the calling of the function found below.//

int battery=0;
#include <Ps3Controller.h>

void onConnect(){
    Serial.println("Connected."); 
}

void Ps3setup(){
    
    Ps3.attach(inputs); //Attach input function //Handles inputs outside main loop function
    Ps3.attachOnConnect(onConnect); //Attach above onConnect function to trigger when controller connects
    Ps3.begin("78:42:1c:2a:9e:76"); //Accept inputs from bluetooth hexadecimal address 
}

//Based largely on Notify function from PS3 Controller Host library "Ps3Demo" example by jvpernis
//"Ps3Demo" example provides full list of all inputs of ps3 controller. Any code beyond simple notification of an input is added.

void inputs()
{
    //--- Digital cross/square/triangle/circle button events ---
    if( Ps3.event.button_down.cross ){
        Serial.println("Started pressing the cross button");
        if (move ==3){
            ArmInputs[1][2] = 1; //RIGHT ARM BACK
        }
    }
    if( Ps3.event.button_up.cross ) {
        Serial.println("Released the cross button");
    }

    if( Ps3.event.button_down.square ) {
        Serial.println("Started pressing the square button");
        if (move ==3){
            ArmInputs[1][3] = 1; //RIGHT ARM LEFT
        }
    }
    if( Ps3.event.button_up.square )
        Serial.println("Released the square button");

    if( Ps3.event.button_down.triangle ){
        Serial.println("Started pressing the triangle button");
        if (move ==3){
            ArmInputs[1][1] = 1; //RIGHT ARM FORWARD
        } 
    }
    if( Ps3.event.button_up.triangle )
        Serial.println("Released the triangle button");

    if( Ps3.event.button_down.circle ) {
        Serial.println("Started pressing the circle button");
        if (move ==3){
            ArmInputs[1][4] = 1; //RIGHT ARM RIGHT
        }
    }
    if( Ps3.event.button_up.circle )
        Serial.println("Released the circle button");

    //--------------- Digital D-pad button events --------------
    if( Ps3.event.button_down.up ){
        Serial.println("Started pressing the up button");
        if (move ==3){
            ArmInputs[6][1] = 1; //LEFT ARM FORWARD
        }
    }
    if( Ps3.event.button_up.up )
        Serial.println("Released the up button");

    if( Ps3.event.button_down.right ){
        Serial.println("Started pressing the right button");
        if (move ==3){
            ArmInputs[6][4] = 1; //LEFT ARM RIGHT
        }
    }
    if( Ps3.event.button_up.right )
        Serial.println("Released the right button");

    if( Ps3.event.button_down.down ){
        Serial.println("Started pressing the down button");
        if (move ==3){
            ArmInputs[6][2] = 1; //LEFT ARM BACK
        }
    }
    if( Ps3.event.button_up.down )
        Serial.println("Released the down button");

    if( Ps3.event.button_down.left ){
        Serial.println("Started pressing the left button");
        if (move ==3){
            ArmInputs[6][3] = 1; //LEFT ARM LEFT
        }
    }
    if( Ps3.event.button_up.left )
        Serial.println("Released the left button");

    //------------- Digital shoulder button events -------------
    if( Ps3.event.button_down.l1 ){
        Serial.println("Started pressing the left shoulder button");
        if (move ==3){
            ArmInputs[6][5] = 1; //LEFT ARM UP
        }
    }
    if( Ps3.event.button_up.l1 )
        Serial.println("Released the left shoulder button");

    if( Ps3.event.button_down.r1 ){
        Serial.println("Started pressing the right shoulder button");
        if (move ==3){
            ArmInputs[1][5] = 1; //RIGHT ARM UP
        }
    }
    if( Ps3.event.button_up.r1 )
        Serial.println("Released the right shoulder button");

    //-------------- Digital trigger button events -------------
    if( Ps3.event.button_down.l2 ){
        Serial.println("Started pressing the left trigger button");
        if (move ==3){
            ArmInputs[6][6] = 1; //LEFT ARM DOWN
        }
    }
    if( Ps3.event.button_up.l2 )
        Serial.println("Released the left trigger button");

    if( Ps3.event.button_down.r2 ){
        Serial.println("Started pressing the right trigger button");
        if (move ==3){
            ArmInputs[1][6] = 1; //RIGHT ARM DOWN
        }
    }
    if( Ps3.event.button_up.r2 )
        Serial.println("Released the right trigger button");

    //--------------- Digital stick button events --------------
    if( Ps3.event.button_down.l3 )
        Serial.println("Started pressing the left stick button");
    if( Ps3.event.button_up.l3 )
        Serial.println("Released the left stick button");

    if( Ps3.event.button_down.r3 )
        Serial.println("Started pressing the right stick button");
    if( Ps3.event.button_up.r3 )
        Serial.println("Released the right stick button");

    //---------- Digital select/start/ps button events ---------
    if( Ps3.event.button_down.select ) {
        Serial.println("Started pressing the select button");
        //CAN ONLY REQUEST STOW IF ROBOT IS IN STANDING CONDITION
        if (stowed == 2) { //IF ROBOT STANDING
            stowed = 3; //STOW ROBOT UP ON NEXT LOOP
        }
    }
    if( Ps3.event.button_up.select )
        Serial.println("Released the select button");

    if( Ps3.event.button_down.start ){
        Serial.println("Started pressing the start button");
        //CAN ONLY REQUEST STANDUP IF ROBOT IS IN STANDING CONDITION
        if (stowed == 0){ //IF ROBOT STOWED
            stowed = 1; //STAND ROBOT UP ON NEXT LOOP
        }
    }
    if( Ps3.event.button_up.start )
        Serial.println("Released the start button");

    if( Ps3.event.button_down.ps ){
        Serial.println("Started pressing the Playstation button");
        if (move == 1) {
            move =3;
        }
        else if (move == 3){
            move =1;
        }
    }
    if( Ps3.event.button_up.ps )
        Serial.println("Released the Playstation button");


    //---------------- Analog stick value events ---------------
    // RIGHT STICK IS OMINDIRECTIONAL MOVEMENT
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
        Serial.print("Moved the left stick:");

        leftinput = 1;

        int x_dir = Ps3.data.analog.stick.lx;
        int y_dir = Ps3.data.analog.stick.ly;

        //ADDED ANGLE/MAGNITUDE CODE
        float angle = (180/M_PI)*atan2(x_dir, y_dir); //-PI < PI
        float magnitude = sqrt(x_dir*x_dir + y_dir*y_dir);

        //LIMIT MAGNITUDE ABOVE 12 BELOW 127
        if (magnitude>127.0)
        {
            magnitude =127.0;  
        }
        else if (magnitude < 12.0)
        {
            magnitude =0.0;
        }
        //SEND MAGNITUDE AND ANGLE TO DIRECTION ARRAY
        direction[0][0] = magnitude;
        direction[0][1] = angle;

        //MOVE HANDLING DONE HERE TO ONLY UPDATE ON NEW INPUT
        if (direction[0][0] > 12.0) {
            //RECALC START AND END POINTS
            for (int leg = 1; leg<7; leg++){//ALL LEGS
                Get_xy_circle(leg,-0.33); //START END
            }
            //START MOVE SEQUENCE
            move = 1;
        }
        else if (direction[0][0] < 12.0) {
            move = 0;
            Home();
        }
        
        //PRINT VALUES 
        //Serial.print(" magnitude: "); Serial.println(direction[0][0], DEC);    
        //Serial.print(" angle: "); Serial.println(direction[0][1], DEC);    

    }

    // RIGHT STICK IS TURNING
   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
        Serial.print("Moved the right stick:");
        int r_x_dir = Ps3.data.analog.stick.rx;
        int r_y_dir = Ps3.data.analog.stick.ry;

        //ADDED ANGLE/MAGNITUDE CODE
        float angle = (180/M_PI)*atan2(r_x_dir, r_y_dir); //-PI < PI //RIGHT STICK ANGLE NOT CURRENTLY USED
        float magnitude = r_x_dir;

        //LIMIT MAGNITUDE ABOVE 12 BELOW 127
        if (magnitude>127.0)
        {
            magnitude =127.0;  
        }
        else if (magnitude<-127.0) 
        {
            magnitude =-127.0;
        }
        else if (abs(magnitude) < 12.0)
        {
            magnitude =0.0;
        }
        
        //SEND MAGNITUDE AND ANGLE TO DIRECTION ARRAY
        direction[1][0] = magnitude;
        direction[1][1] = angle; //NOT CURRENTLY USED
   }

   //--------------- Analog D-pad button events ----------------

//0 Is Stowed //1 Is Requested Standup //2 Is Standing //3 Is Requested Stow
   if( abs(Ps3.event.analog_changed.button.up) ){
        Serial.print("Pressing the up button: ");
        Serial.println(Ps3.data.analog.button.up, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.right) ){
        Serial.print("Pressing the right button: ");
        Serial.println(Ps3.data.analog.button.right, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.down) ){
        Serial.print("Pressing the down button: ");
        Serial.println(Ps3.data.analog.button.down, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.left) ){
        Serial.print("Pressing the left button: ");
        Serial.println(Ps3.data.analog.button.left, DEC);
   }

   //---------- Analog shoulder/trigger button events ----------
   if( abs(Ps3.event.analog_changed.button.l1)){
        Serial.print("Pressing the left shoulder button: ");
        Serial.println(Ps3.data.analog.button.l1, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r1) ){
        Serial.print("Pressing the right shoulder button: ");
        Serial.println(Ps3.data.analog.button.r1, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.l2) ){
        Serial.print("Pressing the left trigger button: ");
        Serial.println(Ps3.data.analog.button.l2, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.r2) ){
        Serial.print("Pressing the right trigger button: ");
        Serial.println(Ps3.data.analog.button.r2, DEC);
   }

   //---- Analog cross/square/triangle/circle button events ----
   if( abs(Ps3.event.analog_changed.button.triangle)){
        Serial.print("Pressing the triangle button: ");
        Serial.println(Ps3.data.analog.button.triangle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.circle) ){
        Serial.print("Pressing the circle button: ");
        Serial.println(Ps3.data.analog.button.circle, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.cross) ){
        Serial.print("Pressing the cross button: ");
        Serial.println(Ps3.data.analog.button.cross, DEC);
   }

   if( abs(Ps3.event.analog_changed.button.square) ){
        Serial.print("Pressing the square button: ");
        Serial.println(Ps3.data.analog.button.square, DEC);
   }

   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( battery == ps3_status_battery_charging )      Serial.println("charging");
        else if( battery == ps3_status_battery_full )     Serial.println("FULL");
        else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
        else if( battery == ps3_status_battery_low)       Serial.println("LOW");
        else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
        else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
        else Serial.println("UNDEFINED");
    }

}