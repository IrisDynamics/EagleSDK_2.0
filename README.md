
# Eagle SDK v2.2.2
Compatible with Orca6-24V, Orca6-48V and Orca15-48V motors
## WARNING!! 
Be aware that the shaft or motor will move during operation. Position your hands and other sensitive assets accordingly. 
This firmware will cause the motor to create forces and motion. Be very careful at all times. Ensure the shaft and motor are mounted in a safe location and not in danger of hitting people or property.

## Description
The SDK firmware runs on an Eagle controller board and is meant to provide communication with up to 3 Orca Series motors using MODBUS protocol. The communications have been abstracted through the Orca API (Actuator object). The SDK includes libraries to allow development of custom firmware for position and force control of the Orca motor, as well as creating custom GUI interfaces. There are built up examples for different applications as well a tutorial guide.

All user guides and reference manuals can be found at https://www.irisdynamics.com/downloads/

The best place to get started is to read the **Eagle Reference Manual** which will give direction on device and development environment set up.

There is also an **EagleSDK Tutorial Guide** with gives a step by step introduction to using this repository.

The **Orca API User Manual** describes the commanding an Orca motor using the Actuator object that abstracts the MODBUS communications.

This repo contains the following:

builds : pe-built hex files for example firmware projects with can be loaded to the Eagle

examples: source code for example projects, need to be compiled before loading to the Eagle, can be edited

IrisControls4: the Windows-based user-interface application used by Iris Dynamics Ltd. Devices to present controls and data over USB.

libraries : modbus_client (Actuator object/Orca API), ic4_library(IrisControls4 API), orca600_api (Orca memory map), GUI_panels (useful combinations of GUI elements), physics (force effects and motion), signals (periodic signals eg. sine wave)


tutorials : A "Start_Here" project that is the starting point of the tutorial guide as well as solutions projects for each of the tutorials

teensy.exe : Program used to flash firmware to the Eagle controller.

## Clone the Repo
If you do not have GIT Bash on your machine, download and install it from https://git-scm.com/downloads

Right click in the directory you would like to clone this repository to and select 'Git Bash Here'

To clone this repo with all included submodules type the git bash command:

	git clone https://github.com/irisdynamics/EagleSDK_2.0 --recurse

or if set up with SSH

	git clone git@github.com:IrisDynamics/EagleSDK_2.0.git --recurse

Note: If you miss the --recurse at the end, the submodule folders will be empty, you can populate them by running the following command in the git bash window
<code> git submodule update --init </code>

## Running Preloaded Example Firmware
Connect the Eagle board to the PC via USB (see USB connector section). Run the IrisControls4.exe, located in the IrisControls4 folder of this repo. A drop down menu above the Connect button will allow you to select the COM port of the Eagle board. GUI elements will be populated by the firmware on the Eagle Controller once it becomes connected. Moving the motor shaft should display its position on the graph corresponding to its connected port. If the motor is powered and connected the title of the graph should turn green. Using the position or force button will command the motor into the corresponding mode and allow position targets or forces to be given to the motor.

## Troubleshooting
Error Codes flags are as follows:     
Configuration Errors - 1   
Force Clipping - 32   
Temperature Exceeded - 64   
Force Exceeded - 128    
Power Exceeded - 256    
Shaft Image Failed - 512    
Voltage Invalid - 1024    
Comms Timeout - 2048    

Note: there may be a combination of multiple errors: For example, error 320 would be a Temperature Exceeded (64) + a Power Exceeded (256). 
Provided the error does not persist it can be cleared using the Clear Errors button.

## Good Luck!
We look forward to your feedback and hope this gets you on the path to success with our technology :)
