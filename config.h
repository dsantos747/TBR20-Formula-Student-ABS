// TBR20 Sensor Conditioning and CAN Communication Module Configuration File
//
// Christopher Bull - Modified by Daniel Santos
//
// This file contains the configurable components of the sensor conditiong 
// module including CAN IDs and sensor types
// All constants listed below can be configured within the specified bounds
// but does not consider clashes of ID with existing CAN systems, therefore 
// dbc files should be analysed before configuration
//
// This config file is for the ESC program


// Inclusion guard to prevent multiple instances
#ifndef CONFIG_H_
#define CONFIG_H_


// Boolean choice of whether sensor is connected to device and should be 
// measured and transmitted
static bool VEH_YAW_ON          = 1;    // Vehicle Yaw from Accelerometer
static bool VEH_SPEED_ON        = 1;    // Vehicle Speed from Accelerometer
static bool WHEEL_SPEED_FL_ON   = 1;    // Wheel speed front left
static bool WHEEL_SPEED_FR_ON   = 1;    // Wheel speed front right
static bool WHEEL_SPEED_RL_ON   = 0;    // Wheel speed rear left
static bool WHEEL_SPEED_RR_ON   = 0;    // Wheel speed rear right
static bool DAMPER_POT_FL_ON    = 0;    // Damper potentiometer front left
static bool DAMPER_POT_FR_ON    = 0;    // Damper potentiometer front right
static bool DAMPER_POT_RL_ON    = 0;    // Damper potentiometer rear left
static bool DAMPER_POT_RR_ON    = 0;    // Damper potentiometer rear right
static bool STEERING_ANGLE_ON   = 1;    // Steering angle
static bool APPS_1_NON_INV_ON   = 0;    // APPS right, not inverted
static bool APPS_2_INV_ON       = 0;    // APPS left, inverted
static bool BSE_FRONT_ON        = 1;    // Brake System Encoder front brake loop
static bool BSE_REAR_ON         = 0;    // Brake System Encoder rear brake loop
static bool HAND_CLUTCH_ON      = 0;    // Steering wheel hand clutch 
static bool CLUTCH_POS_ON       = 0;    // Gear position/number sensor
static bool GEAR_ACT_POS_ON     = 0;    // Gear actuator position


// CAN IDs, extended ID is automatically accounted for
static const int VEH_YAW_ID        = 0x18;  // Vehicle Yaw from Accelerometer
static const int VEH_SPEED_ID      = 0x19;  // Vehicle Speed from Accelerometer
static const int WHEEL_SPEED_FL_ID = 0x20;  // Wheel speed front left
static const int WHEEL_SPEED_FR_ID = 0x21;  // Wheel speed front right
static const int WHEEL_SPEED_RL_ID = 0x22;  // Wheel speed rear left
static const int WHEEL_SPEED_RR_ID = 0x23;  // Wheel speed rear right  
static const int DAMPER_POT_FL_ID  = 0x24;  // Damper potentiometer front left
static const int DAMPER_POT_FR_ID  = 0x25;  // Damper potentiometer front right
static const int DAMPER_POT_RL_ID  = 0x26;  // Damper potentiometer rear left
static const int DAMPER_POT_RR_ID  = 0x27;  // Damper potentiometer rear right
static const int STEERING_ANGLE_ID = 0x28;  // Steering angle
static const int APPS_1_NON_INV_ID = 0x30;  // APPS right, not inverted
static const int APPS_2_INV_ID     = 0x33;  // APPS left, inverted
static const int BSE_FRONT_ID      = 0x34;  // BSE front brake loop
static const int BSE_REAR_ID       = 0x35;  // BSE rear brake loop
static const int HAND_CLUTCH_ID    = 0x36;  // Steering wheel hand clutch
static const int HYDRAULICS_ID     = 0x300; // Hydraulics inc hand clutch & gear


// CAN DLC (Data Length Code), data length for each sensor data segment
static const int VEH_YAW_DLC           = 4; // Vehicle Yaw from Accelerometer
static const int VEH_SPEED_DLC         = 4; // Vehicle Speed from Accelerometer
static const int WHEEL_SPEED_FL_DLC    = 4; // Wheel speed front left
static const int WHEEL_SPEED_FR_DLC    = 4; // Wheel speed front right
static const int WHEEL_SPEED_RL_DLC    = 4; // Wheel speed rear left
static const int WHEEL_SPEED_RR_DLC    = 4; // Wheel speed rear right 
static const int DAMPER_POT_FL_DLC     = 2; // Damper potentiometer front left
static const int DAMPER_POT_FR_DLC     = 2; // Damper potentiometer front right
static const int DAMPER_POT_RL_DLC     = 2; // Damper potentiometer rear left
static const int DAMPER_POT_RR_DLC     = 2; // Damper potentiometer rear right
static const int STEERING_ANGLE_DLC    = 2; // Steering angle
static const int APPS_1_NON_INV_DLC    = 2; // APPS right, not inverted
static const int APPS_2_INV_DLC        = 2; // APPS left, inverted
static const int BSE_FRONT_DLC         = 2; // BSE front brake loop
static const int BSE_REAR_DLC          = 2; // BSE rear brake loop
static const int HAND_CLUTCH_DLC       = 2; // Steering wheel hand clutch
static const int HYDRAULICS_DLC        = 3; // Hydraulics (clutch, gear sensors)



// Sensor value offsets for each sensor
static const float DAMPER_POT_FL_OFFS   = 0; // Damper potentiometer front left
static const float DAMPER_POT_FR_OFFS   = 0; // Damper potentiometer front right
static const float DAMPER_POT_RL_OFFS   = 0; // Damper potentiometer rear left
static const float DAMPER_POT_RR_OFFS   = 0; // Damper potentiometer rear right
static const float STEERING_ANGLE_OFFS  = 0; // Steering angle
static const float APPS_1_NON_INV_OFFS  = 0; // APPS right, not inverted
static const float APPS_2_INV_OFFS      = 0; // APPS left, inverted
static const float BSE_FRONT_OFFS       = 0; // BSE front brake loop
static const float BSE_REAR_OFFS        = 0; // BSE rear brake loop
static const float HAND_CLUTCH_OFFS     = 0; // Steering wheel hand clutch


// Post offset sensor value gains (multipliers)
static const float DAMPER_POT_FL_GAIN   = 1; // Damper potentiometer front left
static const float DAMPER_POT_FR_GAIN   = 1; // Damper potentiometer front right
static const float DAMPER_POT_RL_GAIN   = 1; // Damper potentiometer rear left
static const float DAMPER_POT_RR_GAIN   = 1; // Damper potentiometer rear right
static const float STEERING_ANGLE_GAIN  = 1; // Steering angle
static const float APPS_1_NON_INV_GAIN  = 1; // APPS right, not inverted
static const float APPS_2_INV_GAIN      = 1; // APPS left, inverted
static const float BSE_FRONT_GAIN       = 1; // BSE front brake loop
static const float BSE_REAR_GAIN        = 1; // BSE rear brake loop
static const float HAND_CLUTCH_GAIN     = 1; // Steering wheel hand clutch


// Amount of time to wait for each sensor to retrieve and send updated value 
// (aiming for roughly 1ms per loop max)
static const int LOOP_WAIT_AMOUNT       = 3;    // Wait time in loop (us)
static const int WHEEL_SPEED_FL_COUNT   = 5;    // Wheel speed front left
static const int WHEEL_SPEED_FR_COUNT   = 5;    // Wheel speed front right
static const int WHEEL_SPEED_RL_COUNT   = 5;    // Wheel speed rear left
static const int WHEEL_SPEED_RR_COUNT   = 5;    // Wheel speed rear right  
static const int DAMPER_POT_FL_COUNT    = 10;   // Damper pot front left
static const int DAMPER_POT_FR_COUNT    = 10;   // Damper pot front right
static const int DAMPER_POT_RL_COUNT    = 10;   // Damper pot rear left
static const int DAMPER_POT_RR_COUNT    = 10;   // Damper pot rear right
static const int STEERING_ANGLE_COUNT   = 1;    // Steering angle
static const int APPS_COUNT             = 1;    // Both APPS
static const int BSE_FRONT_COUNT        = 10;   // BSE front brake loop
static const int BSE_REAR_COUNT         = 10;   // BSE rear brake loop
static const int HAND_CLUTCH_COUNT      = 1;    // Steering wheel hand clutch


// Error communication settings
static const int SENSOR_ERROR_ID                = 0x700;        // Errors CAN ID
static const int SENSOR_ERROR_DLC               = 1;            // Error DLC

// CAN error message codes
static const uint8_t APPS_IMPLAUS_ERR           = 0b00000001;   // APPS
                                                                // implausibile
static const uint8_t APPS_1_RANGE_ERR           = 0b00000010;   // APPS out of
                                                                // range
static const uint8_t APPS_2_RANGE_ERR           = 0b00000011;   // APPS out of
                                                                // range
static const uint8_t STEERING_ANGLE_RANGE_WARN  = 0b00000100;   // Steer angle
                                                                // out of range
static const uint8_t BSE_F_RANGE_ERR            = 0b00000110;   // BSE out of
                                                                // range
static const uint8_t BSE_R_RANGE_ERR            = 0b00000111;   // BSE out of
                                                                // range
static const uint8_t WHEEL_SPEED_F_IMPLAUS_WARN = 0b00001000;   // Wheel speed F
                                                                // implausibile
static const uint8_t WHEEL_SPEED_R_IMPLAUS_WARN = 0b00001001;   // Wheel speed R
                                                                // implausibile
static const uint8_t WHEEL_SPEED_F_RANGE_WARN   = 0b00001010;   // Wheel speed F
                                                                // out of range
static const uint8_t WHEEL_SPEED_R_RANGE_WARN   = 0b00001011;   // Wheel speed R
                                                                // out of range
static const uint8_t DAMPER_POT_F_RANGE_WARN    = 0b00001100;   // Damper pot F
                                                                // out of range
static const uint8_t DAMPER_POT_R_RANGE_WARN    = 0b00001101;   // Damper pot R
                                                                // out of range
static const uint8_t HAND_CLUTCH_RANGE_ERR      = 0b00001111;   // Hand clutch
                                                                // out of range


// Boolean choice of whether sensor is connected to device and should be 
// monitored by health system

// Implausibility checks
static bool WHEEL_SPEED_F_IMPLAUS_HEALTH_ON = 1;    // Wheel speed front 
static bool WHEEL_SPEED_R_IMPLAUS_HEALTH_ON = 0;    // Wheel speed rear
static bool APPS_IMPLAUS_HEALTH_ON          = 1;    // APPS 

// Maximum and minimum range checks
static bool WHEEL_SPEED_F_RANGE_HEALTH_ON   = 1;    // Wheel speed front
static bool WHEEL_SPEED_R_RANGE_HEALTH_ON   = 0;    // Wheel speed rear
static bool DAMPER_POT_F_HEALTH_ON          = 1;    // Damper pots front
static bool DAMPER_POT_R_HEALTH_ON          = 0;    // Damper pots rear
static bool STEERING_ANGLE_HEALTH_ON        = 1;    // Steering angle
static bool APPS_RANGE_HEALTH_ON            = 1;    // APPS
static bool BSE_F_HEALTH_ON                 = 0;    // BSE front
static bool BSE_R_HEALTH_ON                 = 0;    // BSE rear
static bool HAND_CLUTCH_HEALTH_ON           = 1;    // Hand clutch


// Maximum error ranges
static const int APPS_MIN               = 3000;     // APPS min raw value
static const int APPS_MAX               = 61000;    // APPS max raw value
static const float WHEEL_SPEED_F_MAX    = 33.33;    // Front wheel speed (m/s)
static const float WHEEL_SPEED_R_MAX    = 33.33;    // Rear wheel speed (m/s)
static const int DAMPER_POT_F_MIN       = 3000;     // Damper pot min raw value
static const int DAMPER_POT_F_MAX       = 61000;    // Damper pot max raw value
static const int DAMPER_POT_R_MIN       = 3000;     // Damper pot min raw value
static const int DAMPER_POT_R_MAX       = 61000;    // Damper pot max raw value
static const int BSE_F_MIN              = 3000;     // BSE front min raw value
static const int BSE_F_MAX              = 61000;    // BSE front max raw value
static const int BSE_R_MIN              = 3000;     // BSE rear min raw value
static const int BSE_R_MAX              = 61000;    // BSE rear max raw value
static const int HAND_CLUTCH_MIN        = 1000;     // Hand clutch min raw value
static const int HAND_CLUTCH_MAX        = 65000;    // Hand clutch max raw value
static const int STEERING_ANGLE_MIN     = 3000;     // Steer angle min raw value
static const int STEERING_ANGLE_MAX     = 61000;    // Steer angle min raw value

// Maximum implausibility (maximum difference between two sensors)
static const float WHEEL_SPEED_F_IMPLAUS    = 3.0;  // Front wheels (m/s)
static const float WHEEL_SPEED_R_IMPLAUS    = 1.0;  // Rear wheels (m/s)
static const int   APPS_IMPLAUS             = 6553; // APPS 10% difference


// Timeout and sample time for wheelspeed sensing (microseconds)
static const int WHEEL_SPEED_TIMEOUT        = 1000000;  // Max time before reset
static const int TIMEOUT_BUFFER             = 10000;    // Offset for timeout

// Wheel speed implausibility decay (prevents old values being checked against 
// new values for implausibility
static const int WHEEL_SPEED_DECAY = 20;


// Car specific attributes
static const float WHEEL_DIAMETER   = 0.4;  // In meters
static const int TONE_RING_TEETH    = 16;   // No teeth on tone ring


// CAN bus configuration register setup values (TBR19 runs at 1 Mbps) and
// oscillator is 16 Mhz
static const uint8_t CNF1 = 0b01000000; // SJW=2TQ, BRP=1
static const uint8_t CNF2 = 0b10001010; // BTL 1, SAM 0, Phase1=2TQ, Prop=3TQ
static const uint8_t CNF3 = 0b00000001; // SOF 0, WAKFIL 0, Phase2=2TQ


// MCP2515 interrupt and request to send registers
static const uint8_t TXRTSCTRL  = 0b00000000;       // RTS pin disable
static const uint8_t CANINTE    = 0b00000000;       // Interrupts disabled
static const uint8_t RXB0CTRL   = 0b00000000;       // RTS pin disable


#endif      // CONFIG_H_