# AstraHandsToOSC

This is a simple openFrameworks application which forwards data about tracked hands from Orbbec Astra cameras to other clients via OSC.

### Building
To compile, you will need [openFrameworks](http://openframeworks.cc/download/) 0.9.x along with the following addons:

- ofxOsc (built in)
- [ofxJSON](https://github.com/jefftimesten/ofxJSON.git)
- [ofxOrbbecAstra](https://github.com/mattfelsen/ofxOrbbecAstra.git)

### Configuration
Edit the `settings.json` file to specify your OSC destination's host/ip address & port and the OSC address to use. You can press `r` to reload the settings while the app is running.

### Message format
For every hand that is tracked, a separate message will be sent out according to the following format:

| index | type  | data               |
|-------|-------|--------------------|
| 0     | int   | id                 |
| 1     | float | position x (in mm) |
| 2     | float | position y (in mm) |
| 3     | float | position z (in mm) |