
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 6

**DATE:** 17/08/2026

**NAME OF EXP:** UART Driver and Serial Debugging

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision + USB-to-TTL Serial Converter + PuTTY

---

## TASK A: UART Initialization and Character Transmission

### 1. Circuit Diagram

The experiment involves interfacing the AT89S52 microcontroller with a PC terminal using UART communication through a USB-to-TTL serial converter.

**Hardware Components:**

- AT89S52 Microcontroller
- 8051 Development Board
- USB-to-TTL Serial Converter
- PC with PuTTY Terminal
- Power Supply
- Connecting Wires

**UART Connections:**

| AT89S52 Pin | Connection |
|-------------|------------|
| P3.1 (TXD) | USB-to-TTL RX |
| P3.0 (RXD) | USB-to-TTL TX |
| GND | USB-to-TTL GND |

The UART signal voltage must be compatible with the microcontroller and USB-to-TTL converter.

The board crystal frequency must also be verified.

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Develop an interrupt-driven UART driver for the 8051 microcontroller that communicates with a PC terminal through a USB-to-TTL serial interface.

Configure UART communication for 9600-8-N-1 and demonstrate character transmission using PuTTY.

**UART Configuration:**

| Parameter | Configuration |
|-----------|---------------|
| UART Mode | 8-bit UART |
| Operation | Asynchronous |
| Baud Rate | 9600 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Baud Rate Generator | Timer1 |

**Expected Output:**

The following message should be continuously transmitted to the PC terminal:

```text
Hello from 8051
```

---

### 3. Working Principle

The 8051 provides serial communication through its built-in UART peripheral.

Timer1 is used as the baud-rate generator.

The serial control register determines the UART operating mode and enables reception.

The serial buffer register is used for transmitting and receiving data.

During transmission, characters are written individually into the serial buffer register.

The transmit-complete flag indicates when the character has finished transmitting.

The PC terminal receives and displays the transmitted characters.

### Important Registers

- `SCON` - Serial Control Register
- `SBUF` - Serial Buffer Register
- `TMOD` - Timer Mode Register
- `TH1` - Timer1 Reload Register
- `TR1` - Timer1 Run Control
- `TI` - Transmit Interrupt Flag
- `RI` - Receive Interrupt Flag
- `ES` - Serial Interrupt Enable
- `EA` - Global Interrupt Enable

### Baud Rate Configuration

For the reference 11.0592 MHz crystal, using Timer1 Mode 2 with SMOD = 0:

```text
Baud Rate = Crystal Frequency /
            [384 × (256 - TH1)]

9600 = 11059200 / [384 × 3]

256 - TH1 = 3

TH1 = 253 = FDH
```

Therefore:

```c
TMOD = 0x20;
TH1 = 0xFD;
SCON = 0x50;
TR1 = 1;
```

These settings assume a classic 12-clock 8051 with an 11.0592 MHz crystal and SMOD = 0.

---

### 4. Pseudocode

1. Include the 8051 register definition header.
2. Configure Timer1 in Mode 2.
3. Load the Timer1 reload value for 9600 baud.
4. Configure the UART for 8-bit asynchronous operation.
5. Enable serial reception.
6. Start Timer1.
7. Store the message "Hello from 8051".
8. Transmit each character through SBUF.
9. Wait for transmission completion in the polling version.
10. Clear the transmit-complete flag.
11. Repeat the transmission continuously.

The complete driver is also required to support interrupt-based communication.

---

### 5. Code Base

**Existing Source Code:**

The available `uart.c` project demonstrates basic UART character transmission.

It uses:

- Timer1 Mode 2
- UART Mode 1
- SBUF for transmission
- TI flag for transmit completion

The existing code transmits the string "gagan" continuously.

**Current Limitations:**

- The required message has not been implemented.
- UART reception is not implemented.
- UART echo is not implemented.
- Interrupt-driven RX buffering is not implemented.
- Baud-rate configuration needs verification against the actual board clock.

The complete TASK A implementation is pending correction and verification.

---

### 6. Inference

UART communication allows the 8051 microcontroller to transmit data serially to a PC terminal.

Timer1 provides the timing required for asynchronous serial communication.

The expected result is continuous display of "Hello from 8051" in PuTTY at 9600 baud.

The final hardware result is pending verification.

---

## TASK B: UART Echo

### 1. Circuit Diagram

The same UART connection is used for bidirectional communication between the 8051 development board and PC.

**Communication Flow:**

```text
PC (PuTTY)
    |
    v
USB-to-TTL Converter
    |
    v
8051 UART RX
    |
    v
8051 UART TX
    |
    v
PC (PuTTY)
```

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Develop an application that continuously receives characters from the PC terminal and immediately transmits the same characters back.

**Expected Behaviour:**

Whatever character is typed in PuTTY must be returned by the 8051.

Example:

**Input:**

```text
ABC123
```

**Expected Echo:**

```text
ABC123
```

Another example:

**Input:**

```text
Hello 8051
```

**Expected Echo:**

```text
Hello 8051
```

---

### 3. Working Principle

The 8051 UART receives serial data through the RXD pin.

Received characters are made available through the serial buffer register.

The receive interrupt flag indicates the arrival of new data.

The received character is transmitted back through the TXD pin.

An interrupt-driven receive buffer can be used to store incoming characters until the application processes them.

**Important Concepts:**

- UART Reception
- UART Transmission
- Serial Interrupt
- Receive Interrupt Flag
- Transmit Interrupt Flag
- UART Echo
- Ring Buffer

---

### 4. Pseudocode

1. Initialize the UART for 9600-8-N-1 communication.
2. Configure the serial receive mechanism.
3. Enable serial interrupts for interrupt-driven reception.
4. Wait for a character from PuTTY.
5. Read the received character.
6. Store the character in the receive buffer.
7. Clear the receive interrupt flag.
8. Retrieve the character from the buffer.
9. Transmit the same character through UART.
10. Repeat continuously.

---

### 5. Code Base

The required UART echo implementation must support receiving and retransmitting characters.

**Required Functionality:**

- UART Initialization
- Character Transmission
- Character Reception
- Interrupt-Driven Reception
- RX Ring Buffer
- Character Echo

**Source Code Status:**

The existing project contains a basic UART transmit example.

The UART echo implementation and interrupt-driven receive ring buffer are pending.

---

### 6. Inference

UART echo demonstrates bidirectional serial communication between a microcontroller and a PC.

The expected result is that each character typed in PuTTY is received by the 8051 and transmitted back to the terminal.

Hardware testing and result verification are pending.

---

## PROJECT FILES

**Available in Original Project:**

- `uart.c` - UART transmission example
- `Uart.uvproj` - Keil µVision project
- `STARTUP.A51` - Startup assembly file

**Pending:**

- Corrected UART transmission code
- UART echo implementation
- Interrupt-driven receive ring buffer
- Circuit diagram
- Hardware verification

---

## EXPERIMENT STATUS

TASK A: Basic transmission code available; correction and verification pending.

TASK B: UART echo and receive buffer implementation pending.

Circuit diagram and hardware results will be added after verification.
