//
// List of Addresses for the MCP2515 CAN Controller
//
// Christopher Bull - Modified by Daniel Santos
//
// Student Number: 149034423
//
// Provides all register addresses required within the MCP2515 chip including 
// flags and buffers
//


// Inclusion guard to prevent multiple instances
#ifndef MCP_REG_ADDRESSES_H_
#define MCP_REG_ADDRESSES_H_


// Receiver ID filter 0 hit bits addresses
static const int RXF0SIDH_ADD   = 0b00000000;   // Standard ID high
static const int RXF0SIDL_ADD   = 0b00000001;   // Standard ID low
static const int RXF0EID8_ADD   = 0b00000010;   // Extended ID second lowest 8
static const int RXF0EID0_ADD   = 0b00000011;   // Extended ID lowest 8

// Receiver ID filter 1 hit bits addresses
static const int RXF1SIDH_ADD   = 0b00000100;   // Standard ID high
static const int RXF1SIDL_ADD   = 0b00000101;   // Standard ID low
static const int RXF1EID8_ADD   = 0b00000110;   // Extended ID second lowest 8
static const int RXF1EID0_ADD   = 0b00000111;   // Extended ID lowest 8

// Receiver ID filter 2 hit bits addresses
static const int RXF2SIDH_ADD   = 0b00001000;   // Standard ID high
static const int RXF2SIDL_ADD   = 0b00001001;   // Standard ID low
static const int RXF2EID8_ADD   = 0b00001010;   // Extended ID second lowest 8
static const int RXF2EID0_ADD   = 0b00001011;   // Extended ID lowest 8

// Receiver ID filter 3 hit bits addresses
static const int RXF3SIDH_ADD   = 0b00010000;   // Standard ID high
static const int RXF3SIDL_ADD   = 0b00010001;   // Standard ID low
static const int RXF3EID8_ADD   = 0b00010010;   // Extended ID second lowest 8
static const int RXF3EID0_ADD   = 0b00010011;   // Extended ID lowest 8

// Receiver ID filter 4 hit bits addresses
static const int RXF4SIDH_ADD   = 0b00010100;   // Standard ID high
static const int RXF4SIDL_ADD   = 0b00010101;   // Standard ID low
static const int RXF4EID8_ADD   = 0b00010110;   // Extended ID second lowest 8
static const int RXF4EID0_ADD   = 0b00010111;   // Extended ID lowest 8

// Receiver ID filter 5 hit bits addresses
static const int RXF5SIDH_ADD   = 0b00011000;   // Standard ID high
static const int RXF5SIDL_ADD   = 0b00011001;   // Standard ID low
static const int RXF5EID8_ADD   = 0b00011010;   // Extended ID second lowest 8
static const int RXF5EID0_ADD   = 0b00011011;   // Extended ID lowest 8


// Receiver and transmitter buffer control register addresses
static const int BFPCTRL_ADD    = 0b00001100;   // Receiver
static const int TXRTSCTRL_ADD  = 0b00001101;   // Transmitter


// Error counter register addresses
static const int TEC_ADD        = 0b00011100;   // Receiver
static const int REC_ADD        = 0b00011101;   // Transmitter


// Receiver buffer 0 mask addresses
static const int RXM0SIDH_ADD   = 0b00100000;   // Standard ID high
static const int RXM0SIDL_ADD   = 0b00100001;   // Standard ID low
static const int RXM0EID8_ADD   = 0b00100010;   // Extended ID second lowest 8
static const int RXM0EID0_ADD   = 0b00100011;   // Extended ID lowest 8

// Receiver buffer 0 mask addresses
static const int RXM1SIDH_ADD   = 0b00100100;   // Standard ID high
static const int RXM1SIDL_ADD   = 0b00100101;   // Standard ID low
static const int RXM1EID8_ADD   = 0b00100110;   // Extended ID second lowest 8
static const int RXM1EID0_ADD   = 0b00100111;   // Extended ID lowest 8


// CAN configuration register addresses
static const int CNF3_ADD       = 0b00101000;   // CAN config reg 3
static const int CNF2_ADD       = 0b00101001;   // CAN config reg 2
static const int CNF1_ADD       = 0b00101010;   // CAN config reg 1

// CAN interrupt register addresses
static const int CANINTE_ADD    = 0b00101011;   // Interrupt enable
static const int CANINTF_ADD    = 0b00101100;   // Interrupt flags

// Error flag register address
static const int EFLG_ADD       = 0b00101101;


// Transmitter buffer 0 register addresses
static const int TXB0CTRL_ADD   = 0b00110000;   // Control register
static const int TXB0SIDH_ADD   = 0b00110001;   // Standard ID high
static const int TXB0SIDL_ADD   = 0b00110010;   // Standard ID low
static const int TXB0EID8_ADD   = 0b00110011;   // Extended ID second lowest 8
static const int TXB0EID0_ADD   = 0b00110100;   // Extended ID lowest 8
static const int TXB0DLC_ADD    = 0b00110101;   // Data Length Code
static const int TXB0D0_ADD     = 0b00110110;   // Data byte 0
static const int TXB0D1_ADD     = 0b00110111;   // Data byte 1
static const int TXB0D2_ADD     = 0b00111000;   // Data byte 2
static const int TXB0D3_ADD     = 0b00111001;   // Data byte 3
static const int TXB0D4_ADD     = 0b00111010;   // Data byte 4
static const int TXB0D5_ADD     = 0b00111011;   // Data byte 5
static const int TXB0D6_ADD     = 0b00111100;   // Data byte 6
static const int TXB0D7_ADD     = 0b00111101;   // Data byte 7

// Transmitter buffer 1 register addresses
static const int TXB1CTRL_ADD   = 0b01000000;   // Control register
static const int TXB1SIDH_ADD   = 0b01000001;   // Standard ID high
static const int TXB1SIDL_ADD   = 0b01000010;   // Standard ID low
static const int TXB1EID8_ADD   = 0b01000011;   // Extended ID second lowest 8
static const int TXB1EID0_ADD   = 0b01000100;   // Extended ID lowest 8
static const int TXB1DLC_ADD    = 0b01000101;   // Data Length Code
static const int TXB1D0_ADD     = 0b01000110;   // Data byte 0
static const int TXB1D1_ADD     = 0b01000111;   // Data byte 1
static const int TXB1D2_ADD     = 0b01001000;   // Data byte 2
static const int TXB1D3_ADD     = 0b01001001;   // Data byte 3
static const int TXB1D4_ADD     = 0b01001010;   // Data byte 4
static const int TXB1D5_ADD     = 0b01001011;   // Data byte 5
static const int TXB1D6_ADD     = 0b01001100;   // Data byte 6
static const int TXB1D7_ADD     = 0b01001101;   // Data byte 7

// Transmitter buffer 2 register addresses
static const int TXB2CTRL_ADD   = 0b01010000;   // Control register
static const int TXB2SIDH_ADD   = 0b01010001;   // Standard ID high
static const int TXB2SIDL_ADD   = 0b01010010;   // Standard ID low
static const int TXB2EID8_ADD   = 0b01010011;   // Extended ID second lowest 8
static const int TXB2EID0_ADD   = 0b01010100;   // Extended ID lowest 8
static const int TXB2DLC_ADD    = 0b01010101;   // Data Length Code
static const int TXB2D0_ADD     = 0b01010110;   // Data byte 0
static const int TXB2D1_ADD     = 0b01010111;   // Data byte 1
static const int TXB2D2_ADD     = 0b01011000;   // Data byte 2
static const int TXB2D3_ADD     = 0b01011001;   // Data byte 3
static const int TXB2D4_ADD     = 0b01011010;   // Data byte 4
static const int TXB2D5_ADD     = 0b01011011;   // Data byte 5
static const int TXB2D6_ADD     = 0b01011100;   // Data byte 6
static const int TXB2D7_ADD     = 0b01011101;   // Data byte 7


// Receiver buffer 0 register addresses
static const int RXB0CTRL_ADD   = 0b01100000;   // Control register
static const int RXB0SIDH_ADD   = 0b01100001;   // Standard ID high
static const int RXB0SIDL_ADD   = 0b01100010;   // Standard ID low
static const int RXB0EID8_ADD   = 0b01100011;   // Extended ID second lowest 8
static const int RXB0EID0_ADD   = 0b01100100;   // Extended ID lowest 8
static const int RXB0DLC_ADD    = 0b01100101;   // Data Length Code
static const int RXB0D0_ADD     = 0b01100110;   // Data byte 0
static const int RXB0D1_ADD     = 0b01100111;   // Data byte 1
static const int RXB0D2_ADD     = 0b01101000;   // Data byte 2
static const int RXB0D3_ADD     = 0b01101001;   // Data byte 3
static const int RXB0D4_ADD     = 0b01101010;   // Data byte 4
static const int RXB0D5_ADD     = 0b01101011;   // Data byte 5
static const int RXB0D6_ADD     = 0b01101100;   // Data byte 6
static const int RXB0D7_ADD     = 0b01101101;   // Data byte 7

// Receiver buffer 1 register addresses
static const int RXB1CTRL_ADD   = 0b01110000;   // Control register
static const int RXB1SIDH_ADD   = 0b01110001;   // Standard ID high
static const int RXB1SIDL_ADD   = 0b01110010;   // Standard ID low
static const int RXB1EID8_ADD   = 0b01110011;   // Extended ID second lowest 8
static const int RXB1EID0_ADD   = 0b01110100;   // Extended ID lowest 8
static const int RXB1DLC_ADD    = 0b01110101;   // Data Length Code
static const int RXB1D0_ADD     = 0b01110110;   // Data byte 0
static const int RXB1D1_ADD     = 0b01110111;   // Data byte 1
static const int RXB1D2_ADD     = 0b01111000;   // Data byte 2
static const int RXB1D3_ADD     = 0b01111001;   // Data byte 3
static const int RXB1D4_ADD     = 0b01111010;   // Data byte 4
static const int RXB1D5_ADD     = 0b01111011;   // Data byte 5
static const int RXB1D6_ADD     = 0b01111100;   // Data byte 6
static const int RXB1D7_ADD     = 0b01111101;   // Data byte 7


// CAN status and control registers
static const int CANSTAT_ADD    = 0x0E;  // CAN status register
static const int CANCTRL_ADD    = 0x0F;  // CAN control register


#endif  // MCP_REG_ADDRESSES_H_