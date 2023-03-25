//
// Instruction Set for MCP2515 SPI to CAN Communication
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


// Include files and libraries required, also includes mbed library 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mbed.h"
#include "config.h"
#include "mcp_reg_addresses.h"
#include "can_instruction_set.h"


// Setup SPI pins for communication to the CAN controller and USB for 
// communication between the LCP1768 and a connected PC terminal
SPI         controlCAN(p5, p6, p7);     // SPI pins (MISO, MOSI, SCK)
DigitalOut  ncsControlCAN(p8);          // Inverted chip select control pin
Serial      pcCAN(USBTX, USBRX);        // USB output and input


// SPI configuration for the communication of the LPC1768 to the MCP2515
int configSPI()
{
    ncsControlCAN=0;                    // Pull control pin low to start 
    controlCAN.format(8,0);             // 8 bits and mode 0
    controlCAN.frequency(8000000);      // 8 Mbps SPI transmission
    ncsControlCAN=1;                    // Release control pin to finish
    return(0);
}


// Read from register beginning at "regAdd" for length of "dataLength" in bytes
// from the MCP2515
uint8_t* readRegCAN(int regAdd, int dataLength, uint8_t* dataPtr, int startAdd)
{
    
    ncsControlCAN = 0;                  // Pull control pin low to start 
    controlCAN.write(CAN_READ);         // Send read command to MCP2515
    controlCAN.write(regAdd);           // Send address to be read on MCP2515
    
    // Read the number of bytes asked by "dataLength"
    for(int i = startAdd; i < dataLength + startAdd; i++)
    {
        dataPtr[i] = controlCAN.write(0x00);   // Allow time to read from MCP2515
    }
    
    ncsControlCAN = 1;                      // Release control pin to finish
    
    return(dataPtr);                        // Return data location if desired
}


// Write to register beginning at "regAdd" for length of "dataLength" in bytes
// from the MCP2515 using "dataPtr" as the address of data to send
int writeRegCAN(int regAdd, uint8_t* dataPtr, int dataLength)
{
    ncsControlCAN = 0;                  // Pull control pin low to start             
    controlCAN.write(CAN_WRITE);        // Send write command to MCP2515
    controlCAN.write(regAdd);           // Send address to be written on MCP2515
    
    
    // Read the number of bytes asked by "dataLength"
    for(int i = 0; i < dataLength; i++)     
    {
        controlCAN.write(dataPtr[i]);   // Write data to adresses on MCP2515
    }
    
    ncsControlCAN = 1;                  // Release control pin to finish
    
    return(0);
}    


// Reset the MCP2515 via SPI commands
int resetCAN()
{
    ncsControlCAN = 0;              // Pull control pin low to start 
    controlCAN.write(CAN_RESET);    // Send CAN reset command
    ncsControlCAN = 1;              // Release control pin to finish

    return(0);
}


// Set the CAN configuration registers for CAN communication specified by the
// "config.h" file
int configCAN()
{
    uint8_t data = 0;               // Byte for holding configuration data
    uint8_t* dataPtr = &data;       // Pointer to configuration data
    int dataLength = 1;             // Provides data length for writing
    
    
    *dataPtr = 0;
    dataPtr = readRegCAN(CANSTAT_ADD, 1, dataPtr, 0);   // Read MCP2515 CAN 
                                                        // setup status reg
        
    // Set MCP2515 to configuration mode
    *dataPtr = 0;
    dataPtr = readRegCAN(CANCTRL_ADD, 1, dataPtr, 0);   // CAN control register 
                                                        // current
    while(*dataPtr != CAN_CONFIG)
    {
        *dataPtr = CAN_CONFIG;              // MCP2515 config mode command
        writeRegCAN(CANCTRL_ADD, dataPtr, dataLength);  // Write config command
        *dataPtr = 0;
        dataPtr = readRegCAN(CANCTRL_ADD, 1, dataPtr, 0);   // Allow check for 
                                                            // config mode
    }

    // Set the configuration registers to those specified in "config.h"
    *dataPtr = 0;
    dataPtr = readRegCAN(CNF1_ADD, 1, dataPtr, 0);      // Configuration reg 1 
                                                        // current
    while(*dataPtr != CNF1)
    {
        *dataPtr = CNF1;                            // Control reg 1 setup
        writeRegCAN(CNF1_ADD, dataPtr, dataLength); // Send control reg 1 setup  
        *dataPtr = 0;
        dataPtr = readRegCAN(CNF1_ADD, 1, dataPtr, 0);  // Check control reg 1 
                                                        // setup
    }

    *dataPtr = 0;
    dataPtr = readRegCAN(CNF2_ADD, 1, dataPtr, 0);  // Configuration reg 2 
                                                    // current
    while(*dataPtr != CNF2)
    {
        *dataPtr = CNF2;                            // Control reg 2 setup
        writeRegCAN(CNF2_ADD, dataPtr, dataLength); // Send control reg 2 setup 
        *dataPtr = 0;
        dataPtr = readRegCAN(CNF2_ADD, 1, dataPtr, 0);  // Check control reg 2 
                                                        // setup
    }
   
    *dataPtr = 0;
    dataPtr = readRegCAN(CNF3_ADD, 1, dataPtr, 0);  // Configuration reg 3 
                                                    // current
    while(*dataPtr != CNF3)
    {           
        *dataPtr = CNF3;                            // Control reg 3 setup
        writeRegCAN(CNF3_ADD, dataPtr, dataLength); // Send control reg 3 setup     
        *dataPtr = 0;
        dataPtr = readRegCAN(CNF3_ADD, 1, dataPtr, 0);  // Check control reg 3 
                                                        // setup
    }


    // Set MCP2515 back to normal one shot mode
    *dataPtr = CAN_NORMAL_OS;                   // MCP2515 normal mode command
    writeRegCAN(CANCTRL_ADD, dataPtr, dataLength);  // Send mode command
    *dataPtr = 0;
    dataPtr = readRegCAN(CANCTRL_ADD, 1, dataPtr, 0);   // Ensure MCP2515 is 
                                                        // in normal mode
    while(*dataPtr != CAN_NORMAL_OS)
    {
        *dataPtr = CAN_NORMAL_OS;               // MCP2515 normal mode command
        writeRegCAN(CANCTRL_ADD, dataPtr, dataLength);  // Send mode command
        *dataPtr = 0;
        dataPtr = readRegCAN(CANCTRL_ADD, 1, dataPtr, 0);   // Ensure MCP2515 is 
                                                            // in normal mode
    }


    // Setup interrupts and request to send registers whilst ensuring any
    // satus bits are reset to zero, editable in "config.h"
    *dataPtr = TXRTSCTRL;
    writeRegCAN(TXRTSCTRL_ADD, dataPtr, dataLength);    // Write RTS setup


    *dataPtr = 0;
    dataPtr = readRegCAN(CANINTE_ADD, 1, dataPtr, 0);   // Interrupt control 
                                                        // register current
    while(*dataPtr != CANINTE)
    {    
        *dataPtr = CANINTE;                             // Interrupt config
        writeRegCAN(CANINTE_ADD, dataPtr, dataLength);  // Write interrupt setup
        *dataPtr = 0;
        dataPtr = readRegCAN(CANINTE_ADD, 1, dataPtr, 0);   // Check interrupt 
                                                            // setup
    }

    pcCAN.printf("\nCAN bus Configured Correctly\n");   // Print finish to PC

    return(0);
}


// Write a CAN message through use of transmission buffer 0 and the request to
// send command
// Uses a specified CAN ID "id" and data pointed to by "dataPtr" with length
// "dataLength" in bytes
int writeMessageCAN(int id, uint8_t* dataPtr, int dataLength)
{
    // Check that data length input does not exceed the expect, otherwise
    // truncate and print warning to PC
    if(dataLength > 8)
    {
        dataLength = 8;
        pcCAN.printf("Data length too large, changed to maximum (8 bytes)");
    }
 
    uint8_t dataByte = 0;               // Byte for holding data
    uint8_t* dataBytePtr = &dataByte;   // Pointer to data byte

    // Ensure flags are  zero and interrupts are reset to configuration setup
    dataBytePtr = readRegCAN(CANINTE_ADD, 1, dataBytePtr, 0);   // Interrupt 
                                                                //control reg
    while(*dataBytePtr != CANINTE)
    {    
        *dataBytePtr = CANINTE;                             // Interrupt config
        writeRegCAN(CANINTE_ADD, dataBytePtr, dataLength);  // Write interrupt
        *dataBytePtr = 0;
        dataBytePtr = readRegCAN(CANINTE_ADD, 1, dataBytePtr, 0);   // Check 
                                                                    // int setup
    }

    // Check to see if the CAN ID is standard size (<2048) or extended (>2047)
    // then change appropriate ID registers for corresponding ID
    if(id < 2048)           // Standard ID
    {
        // Write highest 8 bits of address to standard ID higher register
        // (can be 11 bits long including lower register)
        *dataBytePtr = (id >> 3) & 0b11111111;
        writeRegCAN(TXB0SIDH_ADD, dataBytePtr, 1);
       
        // Write lowest 3 bits of address to standard ID lower register
        // highest bits but do not set lowest 5
        *dataBytePtr = ((id & 0x07) << 5) & 0b11100000;
        writeRegCAN(TXB0SIDL_ADD, dataBytePtr, 1);
        
        // Write zeros to extended ID registers for safety
        *dataBytePtr = 0;
        writeRegCAN(TXB0EID8_ADD, dataBytePtr, 1);
        writeRegCAN(TXB0EID0_ADD, dataBytePtr, 1);
    }
    else if (id > 2047)     // Extended ID   
    {
        // Standard ID higher register bits (highest bits of extended ID)
        *dataBytePtr = (id >> 24);   
        writeRegCAN(TXB0SIDH_ADD, dataBytePtr, 1); 
        
        // Write highest two bits to standard ID lower register for extended ID
        // then include extended ID signal bit as well as lower standard ID bits
        *dataBytePtr = (id >> 16) & 0b00000011;   
        *dataBytePtr = ((id >> 13) & 0b11100000) | *dataBytePtr;
        *dataBytePtr =  dataByte | 0b00001000;          // Add extended ID signal
        writeRegCAN(TXB0SIDL_ADD, dataBytePtr, 1); 
        
        
        // Write bits 8 to 15 to the extended ID 8 register (EID8)
        *dataBytePtr = (id >> 8) & 0b11111111;                
        writeRegCAN(TXB0EID8_ADD, dataBytePtr, 1); 
        
        
        // Write lowest byte to the extended ID 0 register (EID0)
        *dataBytePtr = id & 0b11111111;     
        writeRegCAN(TXB0EID0_ADD, dataBytePtr, 1);  
    } 
      

    // Write data length code to transmission buffer 0 for data length
    *dataBytePtr = dataLength;                                
    writeRegCAN(TXB0DLC_ADD, dataBytePtr, 1);

    // Write data to transmission buffer
    writeRegCAN(TXB0D0_ADD, &dataPtr[0], dataLength);
    

    ncsControlCAN = 0;              // Pull control pin low to start           
    controlCAN.write(CAN_RTS_TX0);  // Send CAN RTS command for TXB0  
    ncsControlCAN = 1;              // Release control pin to finish and send
    wait_us(150);                   // Time allocated for transmission 
    
    return(0);
    
}


// Checks the interrupt flags to see if the receiver buffer has a message
// stored
bool checkMessageReceivedCAN()
{
    uint8_t data = 0;               // Byte for holding flag data
    uint8_t* dataPtr = &data;       // Pointer to flag data
    bool messageReceived = 0;
    dataPtr = readRegCAN(CANINTF_ADD, 1, dataPtr, 0);    // Read interrupt flag reg
    *dataPtr = *dataPtr & 0b00000001;           // Only last flag bit required

    // If data from flags (CANINTF) shows last bit high, a message has been 
    // received and placed in RXB0 otherwise a relevant message has not been 
    // received since clearing the flag
    if(*dataPtr == 0b00000001)
    {
        messageReceived = 1; 
    }
    else
    {
        messageReceived = 0;
    }
    
    return(messageReceived);    // Return true or false for message reception
        
}


// Read a CAN message through use of receiver buffer 0
// Finds the data length and the ID of the message before returning an array 
// of 4 byte address (standard or extended), followed by a byte of data length
// then the data in bytes 
uint8_t* readCAN(bool includeID, uint8_t* data)
{
    uint8_t dataByte = 0;                   // Byte for holding flag data
    uint8_t* dataBytePtr = &dataByte;       // Pointer to flag data
    bool eID = 0;                           // True or false for extended ID
    int id = 0;                             // Variable to hold CAN ID  
    
    
    // Read standard ID lower register to see if extended ID is used (bit 3)
    dataBytePtr = readRegCAN(RXB0SIDL_ADD, 1, dataBytePtr, 0);    // Read SIDL
    
    // Find bit 3 and check for extended ID through bit shift and mask
    *dataBytePtr = (*dataBytePtr >> 3) & 0b00000001;  
    if(*dataBytePtr == 1)
    {
        eID = 1;        // Extended ID used
    }
    else
    {
        eID = 0;        // Standard ID used
    }  
 
    
    // Find the data length from the Data Length Code register (bottom 4 bits)
    dataBytePtr = readRegCAN(RXB0DLC_ADD, 1, dataBytePtr, 0);    // Read DLC reg
    int dataLength = *dataBytePtr & 0b00001111; 
    
    // If standard ID is used and ID is wanted by user, place the ID in the 
    // first four bytes followed by one byte data length and then the data 
    // bytes, else if extended ID used and wanted by user, this will also be 
    // placed in the first four bytes followed by one byte data length and data
    // bytes, otherwise return data length byte followed by data bytes
    if(eID == 0 && includeID == 1)      // Standard ID wanted
    {
        data = (uint8_t*)malloc(dataLength + 5);        // Create byte array
                                                        // of required length
                                                        
        // Get full standard ID via shifting and masks
        dataBytePtr = readRegCAN(RXB0SIDH_ADD, 1, dataBytePtr, 0);  // Read SIDH
        id = *dataBytePtr & 0b11111111;
        id = id << 3;
        dataBytePtr = readRegCAN(RXB0SIDL_ADD, 1, dataBytePtr, 0);  // Read SIDL
        id = id | ((*dataBytePtr >> 5) & 0b00000111);
        
        // Get the data from the receiver 0 buffer data registers for required
        // data length starting from the sixth byte
        data = readRegCAN(RXB0D0_ADD, dataLength, &data[0], 5);
        
        // First two bytes for standard ID are always zero (not needed)
        data[0] = 0;
        data[1] = 0;
        
        // Place full 11 bit standard ID in third and fourth byte
        data[2] = (id >> 8) & 0b00000111;
        data[3] = id & 0b11111111;
        
        // Place data length in fifth
        data[4] = dataLength;   
    }
    else if(eID == 1 && includeID == 1)     // Extended ID wanted
    {
        // Get full extended ID via shifting and masks
        
        // Upper eight bits of address
        dataBytePtr = readRegCAN(RXB0SIDH_ADD, 1, dataBytePtr, 0);  // Read SIDH
        id = *dataBytePtr << 21;
        
        // Next five bits of address       
        dataBytePtr = readRegCAN(RXB0SIDL_ADD, 1, dataBytePtr, 0);  // Read SIDL
        id = id | ((*dataBytePtr & 0b11100000) << 18);
        id = id | ((*dataBytePtr & 0b00000011) << 16);
        
        // Next eight bits of address
        dataBytePtr = readRegCAN(RXB0EID8_ADD, 1, dataBytePtr, 0);  // Read EID8
        id = id | ((*dataBytePtr & 0b11111111) << 8); 
        
        // Lowest eight bits of address   
        dataBytePtr = readRegCAN(RXB0EID0_ADD, 1, dataBytePtr, 0);  // Read EID0
        id = id | (*dataBytePtr & 0b11111111); 
        
        
        data = (uint8_t*)malloc(dataLength + 5);        // Create byte array
                                                        // of required length
                                                        
        // Get the data from the receiver 0 buffer data registers for required
        // data length starting from the sixth byte
        data = readRegCAN(RXB0D0_ADD, dataLength, &data[0], 5);
        
        // Place the ID in the associated break down in bytes (first four)
        data[0] = (id >> 24) & 0b00011111;
        data[1] = (id >> 16) & 0b11111111;
        data[2] = (id >> 8) & 0b11111111;
        data[3] = id & 0b11111111;
        
        // Place data length in the fifth byte
        data[4] = dataLength;    
    }      
    else                                    // No ID wanted
    {
        data = (uint8_t*)malloc(dataLength + 1);        // Create byte array
                                                        // of required length
                                                        
        // Get the data and place from the second byte
        data = readRegCAN(RXB0D0_ADD, dataLength, &data[0], 1); 
        
        // Place data length in the first byte
        data[0] = dataLength;
    }  
    
    
    // Set the flags to zero
    *dataBytePtr = 0;    
    writeRegCAN(CANINTF_ADD, dataBytePtr, 1);

    
    return(data);       // Return the array of ID, DLC, and data
}


// This function converts the ID bytes from the reading of the CAN receiver 
// buffer into a single int type
int getID(uint8_t* data)
{
    int id = 0;     // Start with empty ID
    
    // For each byte associated with the CAN ID shift left then add each byte
    // to create the corrected int ID, creates it with MSB first until full
    for(int i = 0; i < 4; i++)
    {
        id = id << 8;
        id = id | (data[i] & 0b11111111);
    }

    return(id);     // Return the ID
}

// This function converts the data length byte from the reading of the CAN 
// receiver buffer into a single int type
int getDataLength(uint8_t* data)
{
    int dataLength = data[4];       // Get the data length  

    return(dataLength);             // Return the data length
}