# TBR20-Formula-Student-ABS
These are the scripts required for the Team Bath Racing TBR20 Anti-Lock Braking System installation. This was created as part of my final year project for my MEng Mechanical with Automotive Engineering degree at the University of Bath. It is being added to github now as legacy reference, and is being marked as public in case any current Formula Student teams (or anyone else) would like to adapt it for their use.

This program is written in C/C++, and designed to be run on an mbed NXP LPC1768.
The system installation has inputs from a dashboard-mounted rotary switch, and the on-car CAN bus (via an MCP2515 CAN controller).
The outputs are the valves and DC motor in a Bosch Motorcycle ABS unit.

Please refer to the schematic appended below for installation details.

The script "main.cpp" contains the primary ABS decision logic. All additional files are required for interfacing with the MCP2515 CAN controller, to read on-car telemetry data.

Note: The program was never implemented, as the onset of the Covid-19 Pandemic cancelled our car build.

[Full ABS Schematic.pdf](https://github.com/dsantos747/TBR20-Formula-Student-ABS/files/11069975/Full.ABS.Schematic.pdf)
