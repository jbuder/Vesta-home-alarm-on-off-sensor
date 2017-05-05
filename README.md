# Vesta-home-alarm-on-off-sensor
Connect Vesta home alarm output relay to ESP8266 (WEMOS mini D1) with MQTT to Home Assistant
This to show the status of the home alarm on any mobilephone or PC and have your
smarthouse respond to any changes of the alarm.

You need to have the installation code to your Vesta 1923 alarm panel to set the output relay to
on/off all = on, or to what ever you want in the relay output list of choise.
Edit the Arduino IDE program with your wifi settings and MQTT settings
Load the Arduino IDE program to Wemos.
Setup your Home Assistant configuration file with the sensor and MQTT server.
Connect the Ground and D3 of the Wemos to the relay output connector on the back of the alarm panel.
If you want visual indication connect common catode RGB LED to Wemos D0=red ,D5=green.


Have fun...



