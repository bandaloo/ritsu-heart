# Arduino Heart Project
This repository contains the code to run the Arduino Heart Project. Currently,
the code in this repo is just the NeoPixel sample.

## Contributing Code
It would be nice if you used the default C/C++ VS Code formatter before
submitting a pull request, but I'm not going to be weird about it.

If the code starts to get pretty complicated, we should have a discussion about
splitting up the functionality into separate `.c` and `.h` files.  The first
answer on [this stackoverflow post](https://arduino.stackexchange.com/questions/61634/multiple-ino-files-in-the-same-sketch)
explains that this is possible with a `.ino` file, and also how to do it. 

## How to never use the Arduino IDE
You are probably interested in never ever using the Arduino IDE, since it
doesn't have really basic stuff like code completion and jumping to
definitions.  If you wanna use VS Code, here's what you'll need to do.

First, install the Arduino extension for VS Code. This is really easy to do
with VS Code's built in package manager. (If you want, you can even just open
up the command palette and type `ext install vscode-arduino`. Pretty neat!)

In order to not be greeted by a bunch of red squiggles and to unlock the full
power of Intellisense, you're going to need to make sure VS Code knows where
all of those headers are. Here's how you do that:

You can access the `c_cpp_properties.json` file from the command palette with
the command `CMD + SHIFT + P` and searching for "edit configurations".

For Mac, add this to your `c_cpp_properties.json` file:
```
"includePath": [
  "${workspaceFolder}/**",
  "~/Documents/Arduino/libraries/Adafruit_NeoPixel",
  "/Applications/Arduino.app/Contents/Java/libraries",
  "/Applications/Arduino.app/Contents/Java/hardware/tools/avr/avr/include",
  "/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/variants/standard"
],
"browse": {
  "limitSymbolsToIncludedHeaders": false,
  "path": [
    "/System/Library/Frameworks/Kernel.framework/Versions/A/Headers",
    "/Applications/Arduino.app/Contents/Java/"
  ]
},
"forcedInclude": [
  "/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/Arduino.h"
],
```
The above example worked on my Mac.

For Windows, add this to your `c_cpp_properties.json`
```
"includePath": [
    "{$workspaceFolder}/libraries",
    "C:/Users/<your username>/Documents/Arduino/Adafruit_NeoPixel",
    "C:/Program Files (x86)/Arduino/hardware/tools/avr/lib/gcc/avr/5.4.0/include",
    "C:/Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino",
    "C:/Program Files (x86)/Arduino/hardware/arduino/avr/variants/standard",
    "C:/Program Files (x86)/Arduino",
],
```
Remember to replace `<your username>` with the correct thing. (I'm not sure if
`~` works in Windows, but probably.)

If we end up needing any other libraries, we add them to the `"includePath"`
section of the above JSON.

For Linux, good luck Joe. 
