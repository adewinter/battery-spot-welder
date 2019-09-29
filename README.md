# DIY battery spot welder

This repo contains my design for a simple DIY spot welder.  This welder is intended to be used for welding nickel strips onto lithium ion (or similar) cells in order to connect the cells together.

* The `.fzz` file in the root of this repo should be opened with [Fritzing](https://fritzing.org).  It contains the wiring diagram/schematic for this welder.   
* The `3d/` folder contains the [Fusion 360](https://www.autodesk.com/products/fusion-360/overview) model files.  These files will demonstrate how the components will physically come together.  It also contains a very simple box enclosure design that can be 3d printed.
* The `battery-welder/` folder contains the arduino code used for this project.

You can connect to the spot welder via your phones BLE (Bluetooth Low Energy) functionality using the [Dabble Android/iOS app](https://thestempedia.com/docs/dabble/getting-started-with-dabble/) (available in their respective app stores). Once connected, open up the 'terminal' function in the app.  Send an integer value to change the firing time for the solenoid.  This will help to control how deep the weld is (i.e. how much power goes through the welder contacts).

That's it!
