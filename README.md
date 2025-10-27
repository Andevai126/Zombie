# Zombie
A hardware and software solution for your psychological tormenting needs.

## Description
The developed device can play any soundtracks, spaced over large periods of time. It is compact, runs on a single battery and is low power.

## Getting started
[Learn how to upload code to an ATtiny85.](https://www.youtube.com/watch?v=sycSdI49hlY)

### Hardware components list
- ATtiny85
- DFPlayer
- 32GB SD card (Can be way smaller) "expensive"
- 18650 battery "expensive"
- 3W speaker
- 2x MJE3055T transistor
- Push button
- LED
- 1x 10kΩ resistor
- 5x 1kΩ resistor
- 1x 10μF capacitor (Only needed for uploading code)

### Hardware schematic
![Schematic of circuit](images/circuit.png)

### Software
This is a [PlatformIO project in VSCode](https://docs.platformio.org/en/stable/integration/ide/vscode.html). Create a new PlatformIO project, and replace all files and folders with this repository.
Build and upload the code. The first time building can take a while.

### Sound tracks
Copy the audio files found in "/audio" to the SD card.

## Notes
- [DFPlayer documentation](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299#Connection_Diagram).
- Both .wav and .mp3 work.
- "/test_scripts" is only for testing purposes, and is not required.

## Acknowledgements
- [External interrupt](https://web.archive.org/web/20240123141250/https://www.gadgetronicx.com/attiny85-external-pin-change-interrupt/)
