# Mocap_Fusion_Gloves
Arduino/SteamVR motion capture gloves. Check out more of my free motion capture tools and apps at www.MocapFusion.com
<br>
## Assembly Guide:
[![Youtube Tutorial](https://raw.githubusercontent.com/guiglass/LUXOR/gh-pages/img/fusion_gloves/fusion_gloves_thumb.png)](https://www.youtube.com/watch?v=PCBvUHJH8Gw)
<br>
Files for assembling and programming these super low latency "DIY" motion capture glove using an Arduino and 5x SEN-08606 Flex Sensor 4.5" for each finger and a Vive tracker that is strapped to the 3D printed hand strap.
<br>
<br>
Parts:
<br>
nRF24 wireless radios (RP-SMA): https://www.sparkfun.com/products/705

nRF24 wireless radios: https://www.sparkfun.com/products/691

SEN-08606 Flex Sensors: https://www.sparkfun.com/products/8606

Knit Gloves: https://www.amazon.com/OPT-Brand-Winter-Gloves-Wholesale/dp/B07XZL1ZK8

Dynaflex (black): https://www.amazon.com/18280-DYNAFLEX-Black-Building-Material/dp/B000BQWXEO

Boneduino with nRF24 raido: http://duinopeak.com/index.php?route=product/product&manufacturer_id=9&product_id=30

<br>
<br>
Wiring Diagrams:
<br>

![Code Example 1](https://github.com/guiglass/Mocap_Fusion_Gloves/blob/main/Code%20Example%201/connection_guide_template_1.png)
Example #1 requires only a single Arduino Mega and is wired directly to the mocap PC through USB.

***
<br>

![Code Example 1](https://github.com/guiglass/Mocap_Fusion_Gloves/blob/main/Code%20Example%202/connection_guide_template_2.png)
Example #2 Uses a Arduino Mega for for the gloves and sends the finger data wirelessly to a receiving Arduion Uno connected to the mocap PC through USB.

***
<br>

![Code Example 1](https://github.com/guiglass/Mocap_Fusion_Gloves/blob/main/Code%20Example%203/connection_guide_template_3.png)
Example #3 two Arduino Unos or Boneduinos connected to each glove individually, both send the finger data wirelessly to a receiving Arduino Uno connected to the mocap PC through USB.


