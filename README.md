# Shot-Timer
This is a small DIY project to create an automated shot timer for an espresso machine that features a 3-way solenoid valve.

To do this, you will need:
 - Arduino Pro Micro (or any other similar MCU, included code is written for a pro micro).
 - SSD1306 0.96" 124x64 OLED display.
 - Reed switch.*
 - Small AC-DC 5V power supply.**

* Take note of the reed switch specifications. The pull in value (designated by the unit AT) is the sensitivity of the device and you will want to source one with the lowest value possible. Anything with a min value of 10AT should work fine but 40AT+ will be too unreliable. If your choice doesn’t show an AT value, check for the wattage and current throughput, lower the better (10W 500mA should work fine) or even size; smaller is better.
** Power supply can be as small as 300mA if you plan to only do a shot timer. If you want to expand the functionality to include other features, you may want to consider something more powerful.

