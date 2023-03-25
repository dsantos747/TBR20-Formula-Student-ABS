//
// Instruction Set for MCP2515 SPI to CAN Communication Header
//
// Christopher Bull - Modified by Daniel Santos
//
// Student Number: 149034423
//
// Includes the instructions required to communicate data via SPI with an 
// MCP2515 for CAN bus communication
//
// A configuration file for CAN IDs and sensor value adjustments is included 
// under "config.h"
//


// Inclusion guard to prevent multiple instances
#ifndef CAN_INSTRUCTION_SET_H_
#define CAN_INSTRUCTION_SET_H_


// Modes of operation for the MCP2515
static const int CAN_NORMAL_OS  = 0b00001000;   // Normal mode with one-shot
static const int CAN_NORMAL_RT  = 0b00000000;   // Normal mode with reattempts
static const int CAN_SLEEP      = 0b00100000;   // Sleep mode
static const int CAN_LOOPBACK   = 0b01000000;   // Loopback mode
static const int CAN_LISTEN     = 0b01100000;   // Listen-only mode
static const int CAN_CONFIG     = 0b10000000;   // Configuration mode for setup


// Instruction set declarations for the MCP2515
static const int CAN_RESET          = 0b11000000;  // Reset controller
static const int CAN_READ           = 0b00000011;  // Read from start address
static const int CAN_READ_RX_0_ID   = 0b10010000;  // Read receive buff 0 at ID
static const int CAN_READ_RX_0_D0   = 0b10010010;  // Read receive buff 0 at D0
static const int CAN_READ_RX_1_ID   = 0b10010100;  // Read receive buff 1 at ID
static const int CAN_READ_RX_1_D0   = 0b10010110;  // Read receive buff 1 at D0
static const int CAN_WRITE          = 0b00000010;  // Write from start address
static const int CAN_LOAD_TX0_ID    = 0b01000000;  // Load transmit buff 0 at ID
static const int CAN_LOAD_TX0_D0    = 0b01000001;  // Load transmit buff 0 at D0
static const int CAN_LOAD_TX1_ID    = 0b01000010;  // Load transmit buff 1 at ID
static const int CAN_LOAD_TX1_D0    = 0b01000011;  // Load transmit buff 1 at D0
static const int CAN_LOAD_TX2_ID    = 0b01000100;  // Load transmit buff 2 at ID
static const int CAN_LOAD_TX2_D0    = 0b01000101;  // Load transmit buff 2 at D0
static const int CAN_RTS_TX0        = 0b10000001;  // Request to send buff 0
static const int CAN_RTS_TX1        = 0b10000010;  // Request to send buff 1
static const int CAN_RTS_TX2        = 0b10000100;  // Request to send buff 2
static const int CAN_READ_STATUS    = 0b10100000;  // Check transmit and receive
static const int CAN_RX_STATUS      = 0b10110000;  // Filter and type check
static const int CAN_BIT_MOD        = 0b00000101;  // Modify bits in register



// Called for SPI configuration of the LPC1768 with the MCP2515
int configSPI();


// Read bytes from a register address in the MPC2515 using "detaLength" as the 
// number of bytes that should be read and "data" as an already initialised 
// array to store the data equal to the length of the data
uint8_t* readRegCAN(int regAdd, int dataLength, uint8_t* data, int startAdd);


// Write to a single register address in the MCP2515
int writeRegCAN(int regAdd, uint8_t* dataPtr, int dataLength);


// Reset the MCP2515 controller (loses values stored in buffers also)
int resetCAN();


// Configures the CAN controller in conjunction with the "config.h" file
int configCAN();


// Write data to the CAN bus with associated ID "id" using the first bit of the 
// data as the "dataPtr" and the length of the data using the "dataLengthPtr" 
// in bytes
int writeMessageCAN(int id, uint8_t* dataPtr, int dataLength);


// Checks to see if a message has been received on the MCP2515, returns 1 for
// true, a message received, or 0 for false, a message not received
bool checkMessageReceivedCAN();


// Read data from the MCP receive buffers which collect data from the CAN bus
// Can include ID or just data using "includeID" set to 1 or 0 respectively
// Returns ID then data as an array if both selected, otherwise just data alone
// in the format of four ID bytes, then a data length byte, then teh data bytes,
// or just a data length byte followed by the data bytes
uint8_t* readCAN(bool includeID, uint8_t* data);


// Retrieves the ID in int form from the data given by the "readCAN" function
int getID(uint8_t* data);


// Retrieves the data length in int form from the data given by the "readCAN" 
// function
int getDataLength(uint8_t* data);


#endif  // CAN_INSTRUCTION_SET_H_