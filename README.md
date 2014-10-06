Gesture_controller_lamp
=======================

The gesture regonition technology referes to the mathmatical interpretation of human motions 
using a sensor device. Gestures can originate from any bodily motion or state but commonly originate 
from the face or hand.   

There are many ways to implement hand gesture regonition using sensors and many trade off associated 
 with each of them

*Proximity sensor ( Very sensitive under direct sun light)
*Infrared sensors ( Relatively high power consumptions, Used by Samsung Galaxy S5 air gesture)
*Tempture sensors( Sensitive to ambient temperture)


<img src="https://raw.githubusercontent.com/eddyzhangGit/Gesture_controller_lamp/master/image/Eagle_cad_schematic.PNG" 
alt="IMAGE ALT TEXT HERE" width="700" height="450" border="10" />


However, The principle is the same. We calculate the time difference between 2 sensors event to 
recognize the direction of linear motions.

The following project utilizes 2 proximity sensors to detect 
simple air gesture. 
BOM:
*STM Proximity Sensors
*Raspberry Pi Micro-Computer
*5K Pull up resister for I2C
*Breadboard and Wires
*LED(later replace with lamp)

<img src="https://raw.githubusercontent.com/eddyzhangGit/Gesture_controller_lamp/master/image/demo.jpg" 
alt="IMAGE ALT TEXT HERE" width="700" height="450" border="10" />

MileStone 1:  
Program the Respberry pi to establish communication with 
Proximity sensor through I2C. 
Get some distance reading back.


<img src="https://raw.githubusercontent.com/eddyzhangGit/Gesture_controller_lamp/master/image/distance.PNG" 
alt="IMAGE ALT TEXT HERE" width="700" height="450" border="10" />
   Getting distance data fron Proximity sensors

MileStone 2: 
Develop a algorimth in C to detect hand geature.   See https://github.com/eddyzhangGit for source code.

<img src="https://raw.githubusercontent.com/eddyzhangGit/Gesture_controller_lamp/master/image/measuring_loop_code.PNG" 
alt="IMAGE ALT TEXT HERE" width="700" height="450" border="10" />
  a measurment loop to check the direction of motion.

<img src="https://raw.githubusercontent.com/eddyzhangGit/Gesture_controller_lamp/master/image/sweep_from_0_to_1.jpg" 
alt="IMAGE ALT TEXT HERE" width="700" height="450" border="10" />
      sweep hand from sensor 0 to sensor 1 to turn on the LED

<img src="https://raw.githubusercontent.com/eddyzhangGit/Gesture_controller_lamp/master/image/sweep_from_1to_0.jpg" 
alt="IMAGE ALT TEXT HERE" width="700" height="450" border="10" />
       sweep hand from sensor 1 to sensor 0 to turn off the LED

MileStone 3:
Replacing the LED with a real LAMP.

Options 1: designed a swtich that can handle 110V AC inout
Option 2: buy a off-the shelf high power programable switch to control lamp


_Author: Eddy Zhang

_Email : <eddy.zhang@mail.utoronto.ca>_

_Phone: 416-655-6473_
