# RFID-Based Access Control System

## About the Project

This project is based on RFID (Radio Frequency Identification) technology and uses an Arduino Uno and an RC522 RFID reader to scan RFID cards and identify authorized users.

The Arduino processes the card information received from the RFID reader and checks it against the authorization logic programmed into the system. Based on the result, the system determines whether access should be granted or denied.

The project helped me understand how RFID technology works and how a microcontroller can be used to develop a simple access control system.

## Objectives

- To understand the working principle of RFID technology.
- To interface an RC522 RFID reader with an Arduino Uno.
- To read and identify RFID cards or tags.
- To implement basic access authorization logic.
- To gain practical experience in embedded systems and hardware interfacing.

## Hardware Components

- Arduino Uno
- RC522 (MFRC522) RFID reader module
- Compatible RFID card or tag
- Breadboard and jumper wires, if used
- USB cable and suitable power supply

## Software and Libraries

- Arduino IDE
- MFRC522 library
- SPI library

## Working Principle

1. The RC522 RFID reader waits for a compatible RFID card or tag.
2. When a card is scanned, the reader obtains its identifier.
3. The Arduino Uno processes the identifier.
4. The program checks whether the card is authorized.
5. The system responds according to the result of the authorization check.

The exact output depends on the functionality implemented in the Arduino code.

## Typical Circuit Connections

The following connections are commonly used when interfacing an RC522 module with an Arduino Uno using SPI.

| RC522 Pin | Arduino Uno Pin |
|---|---|
| SDA / SS | D10 |
| SCK | D13 |
| MOSI | D11 |
| MISO | D12 |
| RST | D9 |
| GND | GND |
| 3.3V | 3.3V |
| IRQ | Not connected |

**Note:** Verify these pin assignments against your actual circuit and Arduino code. The RC522 operates at 3.3V; do not power it from the Arduino's 5V pin. Check the signal-voltage compatibility of your module before connecting it.

## How to Run the Project

1. Install the Arduino IDE.
2. Install the MFRC522 library through the Arduino IDE Library Manager.
3. Connect the RC522 module to the Arduino Uno.
4. Open the project `.ino` file in the Arduino IDE.
5. Check the pin definitions and select the correct board and port.
6. Upload the program to the Arduino Uno.
7. Scan a compatible RFID card and observe the system's response.

## Results

The project is intended to demonstrate RFID card identification and basic access authorization. Add your actual test results and photographs here after verifying the system with authorized and unauthorized cards.

## Skills Learned

- Arduino programming
- Embedded systems
- RFID technology
- SPI communication
- Microcontroller interfacing
- Basic access control logic

## Future Improvements

- Add an LCD or OLED display to show access status.
- Integrate a buzzer or LEDs for visual and audio feedback.
- Connect a suitable relay or electronic lock driver for physical door control.
- Add access logs and improved credential management.

These are possible future enhancements, not features claimed to be implemented in the current project.

## Author

**[Prajwal V]**

Electronics and Communication Engineering (ECE)

