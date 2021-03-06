# ESP32 Sensing device V1.0

(Update May 18, 2022)

The thermistor and photo-resistor sensors are working well. As they use GPIO 25 and 27 A2D capability (ADC2), the WiFi interface cannot be enabled at the same time the sensors are being read: the ADC2 electronics is shared with the onboard  WiFi capability. An updated version of the device is being prepared to use ADC1 GPIOs instead.

(Update May 17, 2022)

All the trials are positive so far. For R1, instead of 10K, I'm using 2.7M ohms.
Remains the thermistor and photo-resistor sensors to try.

(Updated March 29, 2022)

This is a small footprint ESP32-based sensing device, with the following characteristics:

- 30x28 mm circuit board (30x40 mm with ESP32 antenna)
- Two power modes:
    - Battery (AAx2) (through external battery case)
    - External 5 Volts power support (through power-only Micro USB-B port)
- Battery level monitoring circuit
- Three Sensing ports:
    - Multi-Purpose (configurable through Resistor and Capacitor parts)
    - Thermistor (https://learn.adafruit.com/thermistor/using-a-thermistor)
    - Photoresistor (https://learn.adafruit.com/photocells/using-a-photocell)
- External FTDI port (through a 3-pins [GND, RxD, TxD] port) (https://learn.adafruit.com/ftdi-friend)
- RST / PGM buttons
- Power LED (for external power only)
- Designed with KiCAD V6.0.4 (https://www.kicad.org)
- Public Domain

<img src="pictures/Front_3D.png" alt="picture" width="300"/>&nbsp;&nbsp;&nbsp;&nbsp;<img src="pictures/Back_3D.png" alt="picture" width="300"/>

<img src="pictures/Schematic.png" alt="picture" width="612"/>

The choice of components is related to their availability in my inventory. 

## Design Description

Looking at the schematic, you will find here the information related to each subsection present on the device. Some subsections are required, others are optional depending on your needs.

The electronic component identifiers required for each subsection are listed inside square brackets.

### Required Subsections

- **ESP-WROOM-32** [**U1**] - This is the processor in use on the device.
- **RESET Button** [**SW2**, **R6**, **C1**] - Required to maintain the processor working and do a reset when it is required to take back the control for programming or when the device is not behaving properly.
- **PGM Button** [**SW1**, **R5**] - For programming the processor, the PGM Button must be pressed as the reset button is also pressed such that the processor will be put in program loading. The FTDI interface must be connected to the computer to transmit the new program.
- **FTDI** [**D2**, **J1**] - This is the connection to an external FTDI device that allows for communication between the ESP32 processor and a development PC for program loading and debugging output. Connector's pins are labeled **G** (Ground), **R** (RxD), and **T** (TxD) relative to the ESP32 pinout: The External FTDI GND pin must be connected to **G**, the FTDI RxD pin must be connected to **T**, and the FTDI TxD pin must be connected to **R**. Power must be supplied to the board through AA batteries or external power supply.

### Optional Subsections

- **AAx2 Battery Connector** [**J2**] - If power is to be supplied with AA batteries, the connector is required. The batteries holder wires can also be directly soldered in the through-holes. Please respect the polarity (a '+' sign is present on the board to indicate the positive wire location). **Do not connect any battery if you intend to use an external power supply.**
- **External 5V Power**, [**U2**, **J6**, **D1**, **D3**, **R13**, **C2**, **C3**, **C4**, **C5**] - This is a linear 3.3V regulator circuit, only required when a DC 5 Volts power supply is used. It is expected that the power supply is using a male micro USB-B connector. **Do not implement this subsection if you intend to use batteries.**
- **Voltage Monitoring** [**Q1**, **Q2**, **R1**, **R2**, **R3**, **R4**] - This circuit will allow for reading the 3.3 V power voltage for the device through ADC1_0 internal to the ESP32. If AA batteries are used, it will allow monitoring the battery level to replace them when required. The MOSFET transistor [**Q2**] insure that the circuit will not take a load on the batteries. Must be enabled through [**Q1**] using GPIO17.
- **Generic Sensor Input** [**J3**, **R7**, **R8**, **R9**, **R10**] - This is a port to retrieve some sensor information. The four resistors must be adjusted to consider the kind of sensing to be done (pull-up, pull-down, etc.). Some resistors locations can be used for capacitors if required (e.g. adding an RC circuit). This sensor is connected to GPIO15 (ADC2_3) of the ESP32.
- **Heat Sensor** [**J4**, **R11**] - Allow for reading the level of Heat using an external thermistor through an A2D of the processor (ADC2). This sensor is connected to GPIO25 (ADC2_8) of the ESP32. Can be used with another kind of sensor as appropriate. As the ADC2 circuitry is also used by the WiFi interface, the WiFi interface cannot be enabled at the same time the sensor is being read.
- **Light Sensor** [**J5**, **R12**] - Allow for reading the level of Heat using an external photoresistor through an A2D of the processor (ADC2). This sensor is connected to GPIO27 (ADC2_7) of the ESP32. Can be used with another kind of sensor as appropriate. As the ADC2 circuitry is also used by the WiFi interface, the WiFi interface cannot be enabled at the same time the sensor is being read.

<img src="pictures/ESP32-wroom-32-pinout-mischianti-high-resolution.png" alt="picture" width="612"/>

### Some potential issues

- The thermistor and photoresistive interfaces are exploratory. The known lack of linearity of the ESP32 A2D may have an impact on the quality of the retrieved data. See [here](https://www.e-tinkers.com/2019/10/using-a-thermistor-with-arduino-and-unexpected-esp32-adc-non-linearity/), and [here](https://rntlab.com/question/analogread-for-ntc-thermistor/) for further information.

- The Micro USB-B connector is a specific part with only 2 through-hole pins (GND and 5V). See the BOM below for purchase locations. On Amazon, there are 100, 30, and 10 pieces bundles available. A more conventional 5-pins connector may be adapted (physical tweak or modification to the board design).

- The LED is for use only with the external power supply and is hooked on the 5v side of the linear regulator. It could have been hooked to the 3.3v side, closer to the ESP32.

- The linear 3.3v regulator capacitors may have to be different than the one selected. In particular, on the output side, to get a better transient response, a 22uF tantalum may replace the one indicated (per the AMS1117 spec sheet).

- Using batteries to power the device: depending on the processor speed and the networking requirements at startup (WiFi, BT, BLE), the AA batteries may not be able to supply the required startup current (100 to 500 mA). Many options are possible: use larger batteries, lithium instead of alkaline, add some capacitors (tantalum or other) at C4/C5 locations.

## Bill of Material (BOM)

| Reference(s) | Value | Footprint | Where to find |
|:------------:|:-----:|:---------:|:--------------|
| C1           | .1uF  | 0805      |               |
| C2, C5       | 10uF  | 0805      |               |
| C3, C4       | 100nF | 0805      |               |
| D1           | MBR120VLSF or equivalent | SOD-123 | [e-Radionica](https://e-radionica.com/en/schottky-diode-mbr120vlsft3g-sod123.html), [Digikey](https://www.digikey.com/en/products/detail/on-semiconductor/MBR120VLSFT3G/1477157), [Mouser](https://www.mouser.com/ProductDetail/onsemi/MBR120VLSFT3G?qs=3JMERSakebrD2yr9jFliaA%3D%3D) |
| D2 | 1N4148WS | SOD-323 | [Digikey](https://www.digikey.com/en/products/detail/on-semiconductor/1N4148WS/1873805), [Mouser](https://www.mouser.ca/ProductDetail/onsemi-Fairchild/1N4148WS?qs=2%2FYqgE%252BHg%252BKBrKZlAsMLhw%3D%3D) |
| D3 | LED | 0805 | |
| J1 | Connector 1x3 | Pin Header 2.54mm | |
| J2, J3, J4, J5 | Connector 1x2 | Pin Header 2.54mm | |
| J6 | Micro-B USB | | [AliExpress](https://fr.aliexpress.com/item/32886396127.html?gatewayAdapt=glo2fra), [Amazon](https://www.amazon.com/uxcell-100PCS-Connector-Replacement-Adapter/dp/B07R1HG29D/ref=psdc_172544_t1_B07R1HRM1T) |
| Q1 | MMBT3904 | SOT-23 | |
| Q2 | NDS356AP or IRLML5103TRPBF or equivalent | SOT-23 | |
| R1, R3 to R7, R10 to R12 | 10k ohms | 0805 | |
| R2 | 1k ohms | 0805 | |
| R8, R9 | 0 ohms | 0805 | |
| R13 | 220 ohms | 0805 | |
| SW1, SW2 | PTS526_SK15_SMTR2_LFS | SMTR2 | [Mouser](https://www.mouser.com/ProductDetail/CK/PTS526-SK15-SMTR2-LFS?qs=UXgszm6BlbF5Ezp94JAQtw%3D%3D), [Digikey](https://www.digikey.com/en/products/detail/c-k/PTS526-SK15-SMTR2-LFS/10056626), [e-Radionica](https://e-radionica.com/en/smd-pushbutton.html) |
| U1 | ESP-WROOM-32 | | [e-Radionica](https://e-radionica.com/en/esp32-wroom-32d-wifi-module.html) |
| U2 | AMS1117-3.3 | SOT-223-3 | |

## Copyright (c) 2022 Guy Turcotte

Permission is hereby granted, free of charge, to any person obtaining a copy of this project and associated documentation files (the "Project Content"), to deal in the Project without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Project Content, and to permit persons to whom the Project Content is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Project Content.

THE PROJECT CONTENT IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE PROJECT CONTENT OR THE USE OR OTHER DEALINGS IN THE PROJECT CONTENT.