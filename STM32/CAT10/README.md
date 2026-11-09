
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 10

**DATE:** 05/10/2026

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands

**HARDWARE SETUP / PLATFORM:** STM32F103C8T6 Microcontroller + Wemos D1 Mini ESP8266 + STM32CubeMX + Keil MDK + STM32 HAL Libraries

---

## TASK 9A: Establish STM32 ↔ Wemos UART Communication

### 1. Circuit Diagram

The experiment involves interfacing an STM32 development board with a Wemos D1 Mini ESP8266 module through UART.

The STM32 sends AT commands to the Wemos and receives its responses.

A second UART is used to display the communication results on a PC terminal.

**Hardware Components:**

- STM32F103C8T6 Microcontroller
- STM32 Development Board
- Wemos D1 Mini ESP8266 Module
- USB-to-TTL Serial Converter
- PC with PuTTY / Serial Terminal
- Power Supply
- Connecting Wires

**UART Connections from the Project:**

| STM32 Pin | Connection |
|-----------|------------|
| PA9 (USART1_TX) | Wemos RX |
| PA10 (USART1_RX) | Wemos TX |
| PA2 (USART2_TX) | PC Serial RX |
| PA3 (USART2_RX) | PC Serial TX |
| GND | Common Ground |

The UART signals use 3.3V logic. The Wemos module must be powered through an appropriate power input.

**UART Configuration:**

| Parameter | Value |
|-----------|-------|
| USART1 | STM32 ↔ Wemos |
| USART2 | STM32 ↔ PC |
| Baud Rate | 115200 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Hardware Flow Control | None |

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Establish UART communication between the STM32 and Wemos ESP8266 before attempting Wi-Fi communication.

The STM32 must transmit the `AT` command followed by carriage return and line feed.

The Wemos is expected to respond with `OK`.

**Working Principle:**

UART communication is established between the STM32 and ESP8266 using the STM32 HAL library.

USART1 sends AT commands to the Wemos and receives responses.

USART2 forwards the received responses to the PC terminal.

**Expected Communication:**

```text
STM32 -> Wemos:
AT\r\n

Wemos -> STM32:
OK\r\n
```

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize USART1 and USART2.
4. Configure both UART peripherals.
5. Transmit the `AT\r\n` command through USART1.
6. Receive the response from the Wemos.
7. Forward the received response through USART2.
8. Display the response using PuTTY.
9. Verify communication.

**Important HAL Functions:**

- `HAL_UART_Init()` - Initialize UART.
- `HAL_UART_Transmit()` - Transmit AT commands.
- `HAL_UART_Receive()` - Receive Wemos responses.
- `HAL_UARTEx_ReceiveToIdle()` - Receive variable-length UART data where applicable.

**Code Base:**

The existing project uses the STM32 HAL UART functions for transmitting AT commands and forwarding received responses.

The current implementation uses blocking UART receive operations with specified buffer sizes and timeouts.

Actual response lengths and receive status require verification.

### 3. Inference

UART provides serial communication between the STM32 microcontroller and ESP8266 Wi-Fi modem.

The expected result is successful AT-command transmission and an `OK` response displayed on the PC terminal.

Hardware verification is pending.

---

## TASK 9B: Explore the ESP8266 AT Command Interface

### 1. Circuit Diagram

The same UART connections from TASK 9A are used to communicate with the ESP8266 AT-command interface.

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Investigate the ESP8266 AT commands required to configure the Wi-Fi modem, inspect network information and establish network communication.

### AT Command Investigation

| Requirement | AT Command |
|-------------|------------|
| Check modem response | `AT` |
| Check firmware version | `AT+GMR` |
| Set station mode | `AT+CWMODE=1` |
| Scan available Wi-Fi networks | `AT+CWLAP` |
| Connect to an access point | `AT+CWJAP="SSID","PASSWORD"` |
| Obtain IP information | `AT+CIFSR` |
| Establish TCP connection | `AT+CIPSTART` |
| Send application data | `AT+CIPSEND` |

The exact arguments for connection and data-transmission commands depend on the ESP8266 AT firmware and connection settings.

**Additional Commands Used in the Project:**

- `AT+CWDHCP` - Configure DHCP.
- `AT+CWQAP` - Disconnect from the access point.
- `AT+CIPMUX` - Configure multiple connections.
- `AT+CIPSERVER` - Configure a TCP server.

### Working Principle

AT commands provide a text-based interface for controlling the ESP8266 modem.

The STM32 sends commands through UART and receives the corresponding modem responses.

Different commands are used to identify the modem, configure its operating mode, scan networks, connect to Wi-Fi and inspect network status.

### Pseudocode

1. Initialize both UART peripherals.
2. Send the basic AT command.
3. Verify the modem response.
4. Query the firmware version.
5. Configure the Wi-Fi operating mode.
6. Scan available wireless networks.
7. Configure or join the selected access point.
8. Query the IP address.
9. Explore TCP connection and data-transmission commands.
10. Display the received responses through the PC terminal.

### Code Base

The available STM32 project contains AT commands for:

- Basic modem communication
- Station mode configuration
- DHCP configuration
- Wi-Fi connection
- IP address query
- Multiple TCP connections
- TCP server configuration

Not all commands in the investigation table are implemented as separate tests in the current source.

### 3. Inference

The ESP8266 AT-command interface allows a host microcontroller to configure Wi-Fi and network-related operations through UART.

The expected result is that the STM32 sends valid AT commands and receives the appropriate modem responses.

Individual command results require hardware verification.

---

## TASK 9C: Connect Wemos to Wi-Fi

### 1. Circuit Diagram

The STM32 communicates with the ESP8266 through USART1, while USART2 provides debugging output to the PC terminal.

**Hardware Components:**

- STM32 Development Board
- Wemos D1 Mini ESP8266
- Wi-Fi Access Point
- PC Serial Terminal
- Connecting Wires
- Power Supply

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Develop STM32 firmware that configures the Wemos ESP8266 as a Wi-Fi station and connects it to a university or local Wi-Fi network using AT commands.

### Working Principle

The STM32 initializes UART communication with the ESP8266.

It sends commands to configure the modem in station mode.

The STM32 then sends the access-point credentials and waits for the modem's response.

After a successful connection, the STM32 queries the network information and displays it through the PC terminal.

**Required AT Command Sequence:**

```text
AT
    |
    v
AT+CWMODE=1
    |
    v
AT+CWJAP="SSID","PASSWORD"
    |
    v
Wait for Wi-Fi Connection
    |
    v
AT+CIFSR
    |
    v
Display Network Information
```

**Expected Responses:**

```text
>> AT
<< OK

>> AT+CWMODE=1
<< OK

>> AT+CWJAP="SSID","PASSWORD"
<< WIFI CONNECTED
<< WIFI GOT IP
<< OK
```

The exact response format can vary with the ESP8266 AT firmware.

**Expected Verification:**

```text
WIFI MODE   : STATION
WIFI STATUS : CONNECTED
IP ADDRESS  : xxx.xxx.xxx.xxx
```

### Pseudocode

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize USART1 for the Wemos.
4. Initialize USART2 for PC communication.
5. Send the AT command to verify communication.
6. Configure the ESP8266 in station mode.
7. Send the Wi-Fi connection command.
8. Wait for the connection response.
9. Check whether the connection is established.
10. Query the assigned IP address.
11. Forward network information to the PC terminal.
12. Display the Wi-Fi connection status.

### Code Base

**Available Project:**

`FIOT/Wemis/wemos`

**Hardware Configuration:**

- STM32F103C8T6
- USART1 - Wemos Communication
- USART2 - PC Debugging
- 115200 Baud Rate
- STM32 HAL
- Configured 72 MHz System Clock

The project contains commands for Wi-Fi station configuration, connection to an access point, and retrieval of IP information.

It also includes an experimental HTTP server implementation beyond the basic Wi-Fi connection requirement.

**Security Note:**

Actual Wi-Fi credentials are not included in this documentation and must be removed from public source code before submission.

### 3. Inference

The experiment demonstrates how an STM32 microcontroller can control an ESP8266 Wi-Fi modem using AT commands.

The expected result is successful Wi-Fi station configuration, connection to a wireless network and retrieval of network information.

Physical communication results and the assigned IP address require verification.

---

## PROJECT FILES

**Primary Original Project:**

`FIOT/Wemis/wemos`

**Project Components:**

- `wemos.ioc` - STM32CubeMX configuration
- `Core/Src` - STM32 source code
- `Core/Inc` - Application header files
- `Drivers` - STM32 HAL and CMSIS dependencies
- `MDK-ARM` - Keil MDK project configuration

**Additional Project:**

`FIOT/WEMOS/HTTP`

This is a separate STM32F401RE-based project demonstrating further ESP8266 HTTP communication.

It is not required for the basic CAT10 UART and Wi-Fi connection tasks.

**Pending:**

- Circuit diagram
- Hardware verification
- PuTTY terminal observations
- Source-code cleanup before public upload

---

## EXPERIMENT STATUS

**TASK 9A:** UART communication source available; hardware verification pending.

**TASK 9B:** AT-command investigation partially represented in existing code; remaining tests require verification.

**TASK 9C:** Wi-Fi station setup and connection code available; hardware verification pending.

The experiment documentation follows the CAT10 question paper. Circuit diagrams and actual observations will be added later.
