// TBR20 ABS Project - Daniel Santos - Student Number 159218259  
//  
// CAN-based ABS Program - With ESC elements
//
// This program is the full ABS and ESC iteration, which uses the MCP2515 and
// MCP2561 chips to read from the CAN bus. It also takes input from a 
// 5-position rotary switch, to which aggressiveness values (slip thresholds) 
// can be assigned. If yaw rate during cornering isn't as expected based on
// steer angle and vehicle speed, front left-right brake bias is modulated to 
// correct it.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mbed.h"
#include "config.h"
#include "can_instruction_set.h"
#include "mcp_reg_addresses.h"
#include <SPI.h>

// Define input pins   
DigitalIn dashSwitch_off(p8);        //Each of these corresponds to one of the
DigitalIn dashSwitch_low(p9);        //five positions on the dash-mounted
DigitalIn dashSwitch_med(p10);       //rotary switch, which are= ABS off;
DigitalIn dashSwitch_high(p11);      //low ABS aggressiveness; medium ABS aggro;
DigitalIn dashSwitch_wet(p12);       //high ABS aggro; ABS for wet conditions.

// Define output pins
DigitalOut FLapply(p13);             //FL Apply Valve on manifold
DigitalOut FRapply(p14);             //FR Apply Valve on manifold             
DigitalOut FLdump(p15);              //FL Dump Valve on manifold
DigitalOut FRdump(p16);              //FR Dump Valve on manifold
DigitalOut pump(p17);                //DC Motor for pump on manifold

// Define pins for CAN
SPI spi(p5, p6, p7);                // mosi, miso, sclk

// Slip calculator function
double slip(double x, double y)  // X should be vehicle speed, y should be wheel speed
{ 
    return((x - y)/x);
}

int main()
{
    wait_us(100000);        // Wait for electronics to stablise before setup
    configSPI();         // Setup SPI with STM32 chip
    resetCAN();             // Reset the CAN controller with SPI command
    configCAN();         // Setup CAN controller with configuration.h file 

    // Variable Preallocation
    int switch_abs;                     //Switch-Case variable
    int switch_flslip;                  //Switch-Case variable
    int switch_frslip;                  //Switch-Case variable
    double slipThres_dump = 0;          //Slip Threshold for Pressure Dump
    double slipThres_hold = 0;          //Slip Threshold for Pressure Hold
    double fl_slip = 0;                 //Relative Slip at FL Wheel
    double fr_slip = 0;                 //Relative Slip at FR Wheel
    double wheel_steer = 0;             //Average Wheel heading angle
    double exp_yaw = 0;                 //Calculated expected yaw rate
    double yaw_diff = 0;                //Expected - Actual Yaw rate
    double wheelbase = 1.535;           //Car Wheel Base
    double Ftrack = 1.2;                //Car track width at front axle
    double y_cog = 0.005;               //COG Y-position (positive = right)
    double FLdump_mult = 0;             //ESC multiplier for FL pressure dump
    double FLhold_mult = 0;             //ESC multiplier for FL pressure hold
    double FRdump_mult = 0;             //ESC multiplier for FR pressure dump
    double FRhold_mult = 0;             //ESC multiplier for FR pressure hold
    double fl_speed_diff = 0;           //FL wheel speed from yaw
    double fr_speed_diff = 0;           //FR wheel speed from yaw
    double fl_speed_corrected = 0;      //FL wheel speed accounting for yaw
    double fr_speed_corrected = 0;      //FR wheel speed accounting for yaw
    double* veh_speed;                  //Vehicle speed pointer
    veh_speed = 0;                          //Value
    double* fl_speed;                   //FL Wheel Speed pointer
    fl_speed = 0;                           //Value
    double* fr_speed;                   //FR Wheel Speed pointer
    fr_speed = 0;                           //Value
    double* steer;                      //Steering Wheel Angle pointer
    steer = 0;                              //Value
    double* yaw;                        //Yaw Rate pointer
    yaw = 0;                                //Value
    double* brake_pres;                 //Brake Pressure pointer
    brake_pres = 0;                         //Value
    bool rec = checkMessageReceivedCAN();   // Check for message reception
    
    while(1){
        
    //While loop only runs if it detects that the switch on the dash is at any
    //position which isn't ABS-off. Writing it this way (rather than
    //while(dashSwitch_off=0) ) is an additional safety measure, as if no signal
    //is detected the ABS won't run - standard braking resumed.
      while(dashSwitch_low == 1 || dashSwitch_med == 1 || dashSwitch_high == 1 || dashSwitch_wet == 1){                                                               //change this to be while any of the input pins is not 1

    //This is where the slip difference values at which ABS does pressure hold
    //or pressure dump are defined. These are important parameters to modify
    //from results of testing.
        if (dashSwitch_low == 1){        //Lowest setting of ABS aggressiveness
            slipThres_dump = 0.5;
            slipThres_hold = 0.3;}
        else if (dashSwitch_med == 1){   //Medium setting of ABS aggressiveness
            slipThres_dump = 0.45;
            slipThres_hold = 0.25;}
        else if (dashSwitch_high == 1){  //High setting of ABS aggressiveness
            slipThres_dump = 0.4;
            slipThres_hold = 0.2;}
        else if (dashSwitch_wet == 1){   //Wet weather setting for ABS aggro
            slipThres_dump = 0.35;
            slipThres_hold = 0.25;}

        uint8_t* data;                          // Data pointer
        rec = checkMessageReceivedCAN();        // Check for message reception
        if(rec == 1){
            data = readCAN(1, data);                    // Read CAN data
            int id = getID(&data[0]);                   // Determine ID of data
            int dataLength = getDataLength(&data[0]);   // Get DLC of data
               
            // If received CAN message is wanted, translate it to value   
            if (id == VEH_SPEED_ID) // Vehicle speed, in kph
            {
                veh_speed = reinterpret_cast<double*>(&data[1]); 
            }
            else if (id == WHEEL_SPEED_FL_ID) // FL Wheel Speed, in kph
            {
                fl_speed = reinterpret_cast<double*>(&data[1]);
            }
            else if (id == WHEEL_SPEED_FR_ID) // FR Wheel Speed, in kph
            {
                fr_speed = reinterpret_cast<double*>(&data[1]);
            }
            else if (id == STEERING_ANGLE_ID) // Steering Angle
            {
                steer = reinterpret_cast<double*>(&data[1]);                     
            }
            else if (id == VEH_YAW_ID) // Steering Angle
            {
                yaw = reinterpret_cast<double*>(&data[1]);                     
            }
            else if (id == BSE_FRONT_ID) // Front loop brake pressure
            {
                brake_pres = reinterpret_cast<double*>(&data[1]);                     
            }
            free(data); // Clear data
        }

        //Calculate Slip at FL and FR wheels
        fl_slip = slip(*veh_speed,*fl_speed); //Very positive = Locking
        fr_slip = slip(*veh_speed,*fr_speed);                                               

        //Steering Wheel to Wheel Heading Angle Conversion
        //Steering Wheel Ranges from -90 to 90, average wheel heading angle
        //ranges from -28.5 to 28.5
        wheel_steer = *steer / 3.1578947368421052631578947368421;   //Scale
        wheel_steer = wheel_steer * 3.14159265359 / 180;    //Convert to rads

        //Expected Yaw Rate (Negative Value = left (anti-clockwise))
        exp_yaw = (*veh_speed/3.6) * tan(wheel_steer) / wheelbase;

        //Yaw discrepancy
        yaw_diff = exp_yaw - *yaw;          
        if (yaw_diff < 0)                   //If loop acts as an abs() function
            {yaw_diff = yaw_diff * -1;}
        else
            break;


        //Check brake pedal is pressed, and speed is relatively fast
        //Important to prevent ABS actuating all the time or at low speeds
        //Conditions: If steer is neutral, check enable ABS if required
        //If steer is not neutral and there is a difference between the car yaw
        //rate and expected yaw rate, run over/understeer correction ABS
        //If steer is not neutral and the car is yawing as expected based on the
        //steer angle and speed, enable ABS while turning
        if (*brake_pres>2 && *veh_speed>10)
          {switch_abs = 1;}                 //Enable Straight-Line ABS
        else if (*brake_pres>2 && *veh_speed>10 && yaw_diff>0.5)
          {switch_abs = 2;}                 //Enable Out-Of-Control Steering ABS
        else
          {switch_abs = 0;}                 //Don't Enable ABS

      
        switch (switch_abs)
          {
            case 1: //Enable straight-line ABS - code below makes it happen!

            //FL circuit - valve control decision tree
            if (fl_slip>slipThres_dump) //Large slip difference = pressure dump    
              {switch_flslip = 3;}        
            else if (fl_slip>slipThres_hold) //Medium d_slip = pressure hold
              {switch_flslip = 2;}
            else
              {switch_flslip = 1;} //Insignificant slip difference = no ABS
        
            switch (switch_flslip){ // Modulate FL circuit valves
                case 1: // Pressure Apply
                    FLapply = 0;    // Open apply valve
                    FLdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;                   
                case 2: // Pressure Hold
                    FLapply = 1;    // Close apply valve
                    FLdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;
                case 3: // Pressure Dump
                    FLapply = 1;    // Close apply valve
                    FLdump = 1;     // Open dump valve
                    pump = 1;       // Actuate pump
                break;
            }   
            
            //FR circuit - valve control decision tree
            if (fr_slip>slipThres_dump) //Large slip difference = pressure dump
                {switch_frslip = 3;}        
            else if (fr_slip>slipThres_hold) //Medium d_slip = pressure hold
                {switch_frslip = 2;}
            else
                {switch_frslip = 1;} //Insignificant slip difference = no ABS
        
            switch (switch_frslip){ // Modulate FL circuit valves
                case 1: // Pressure Apply
                    FRapply = 0;    // Open apply valve
                    FRdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;
                case 2: // Pressure Hold
                    FRapply = 1;    // Open apply valve
                    FRdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;
                case 3: // Pressure Dump
                    FLapply = 1;    // Close apply valve
                    FLdump = 1;     // Open dump valve
                    pump = 1;       // Actuate pump
                break;
            }
            break;
            
            case 2:         //ESC based ABS
            //We want to divert the existing brake pressure to the wheel which
            //would correct it. The if loop below identifies left oversteer &
            //understeer and right oversteer & understeer, then assigns values
            //to multipliers which reduce the limits at which "pressure hold"
            //and "pressure dump" kick in - limiting brake pressure to that
            //wheel and hence increasing brake pressure at the other wheel.
            //Finding optimal multiplier values should be the focus of testing,
            //although the 1.0 values shouldn't be changed. If you want to delay
            //ABS kicking in, change the global threshold values above.
            if (exp_yaw<0){             // Turning left
                if (*yaw<exp_yaw){      // Oversteer
                    FLdump_mult=0.6;    // These multiplier values reduce brake
                    FLhold_mult=0.6;    // pressure at the left wheel,
                    FRdump_mult=1.0;    // increasing at the right wheel
                    FRhold_mult=1.0;                            
                }
                else {                  // Understeer
                    FLdump_mult=1.0;    // These multiplier values reduce brake
                    FLhold_mult=1.0;    // pressure at the right wheel,
                    FRdump_mult=0.8;    // increasing at the left wheel
                    FRhold_mult=0.8;
                }
            }
            else {                      // Turning Right 
                if (*yaw>exp_yaw){      // Oversteer                                     
                    FLdump_mult=1.0;    // These multiplier values reduce brake
                    FLhold_mult=1.0;    // pressure at the right wheel,
                    FRdump_mult=0.6;    // increasing at the left wheel
                    FRhold_mult=0.6;
                }
                else {                  // Understeer
                    FLdump_mult=0.8;    // These multiplier values reduce brake
                    FLhold_mult=0.8;    // pressure at the left wheel,
                    FRdump_mult=1.0;    // increasing at the right wheel
                    FRhold_mult=1.0;
                }
            }

            //Calculate Corrected FL and FR wheel speeds
            //These are the actual wheel speed, minus the expected increse or
            //decrease in wheel speed from the car being yawing. This is to 
            //still be able to correctly calculate relative slip of wheels.
            fl_speed_diff = *yaw * (((Ftrack/2)+y_cog)/cos(wheel_steer));
            fr_speed_diff = *yaw * (((Ftrack/2)-y_cog)/cos(wheel_steer));
                    
            fl_speed_corrected=*veh_speed + fl_speed_diff;
            fr_speed_corrected=*veh_speed - fr_speed_diff;      // - is to account for yaw being negative in left direction

            //Calculate Slip at FL and FR wheels
            fl_slip = slip(*veh_speed,fl_speed_corrected); //Very positive = Locking
            fr_slip = slip(*veh_speed,fr_speed_corrected);
            
            //FL circuit - valve control decision tree
            if (fl_slip>(slipThres_dump*FLdump_mult)) // Pressure dump
              {switch_flslip = 3;}        
            else if (fl_slip>slipThres_hold*FLhold_mult) //Pressure hold
              {switch_flslip = 2;}
            else
              {switch_flslip = 1;} //Insignificant slip difference = no ABS
        
            switch (switch_flslip){ // Modulate FL circuit valves
                case 1: // Pressure Apply
                    FLapply = 0;    // Open apply valve
                    FLdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;                   
                case 2: // Pressure Hold
                    FLapply = 1;    // Close apply valve
                    FLdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;
                case 3: // Pressure Dump
                    FLapply = 1;    // Close apply valve
                    FLdump = 1;     // Open dump valve
                    pump = 1;       // Actuate pump
                break;
            }   
            
            //FR circuit - valve control decision tree
            if (fr_slip>slipThres_dump*FRdump_mult) //Pressure dump
                {switch_frslip = 3;}        
            else if (fr_slip>slipThres_hold*FRhold_mult) //Pressure hold
                {switch_frslip = 2;}
            else
                {switch_frslip = 1;} //Insignificant slip difference = no ABS
        
            switch (switch_frslip){ // Modulate FL circuit valves
                case 1: // Pressure Apply
                    FRapply = 0;    // Open apply valve
                    FRdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;
                case 2: // Pressure Hold
                    FRapply = 1;    // Open apply valve
                    FRdump = 0;     // Close dump valve
                    pump = 0;       // Don't actuate pump
                break;
                case 3: // Pressure Dump
                    FLapply = 1;    // Close apply valve
                    FLdump = 1;     // Open dump valve
                    pump = 1;       // Actuate pump
                break;
            }
            break;

            
            case 0:         // If ABS shouldn't be enabled
                FLapply = 0;    // Open apply valve
                FLdump = 0;     // Close dump valve
                FRapply = 0;    // Open apply valve
                FRdump = 0;     // Close dump valve
                pump = 0;       // Don't actuate pump      
            break;
          }

        }
    }
}