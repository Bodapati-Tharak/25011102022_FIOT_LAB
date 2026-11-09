
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 9

**DATE:** 28/09/2026

**NAME OF EXP:** STM32 UART Command Controlled LED

**HARDWARE SETUP / PLATFORM:** STM32F103C8T6 Microcontroller + STM32CubeMX + Keil MDK + STM32 HAL Libraries + PC Serial Terminal

---

## TASK 9A: Basic UART Communication

### 1. Circuit Diagram

This experiment establishes serial communication between an STM32 microcontroller and a PC terminal through UART.

**Hardware Components:**

- STM32F103C8T6 Microcontroller
- STM32 Development Board
- USB-to-TTL Serial Converter
- PC with PuTTY Terminal
- Power Supply
- Connecting Wires

**UART Configuration from Source Code:**

| Parameter | Configuration |
|-----------|---------------|
| UART Peripheral | USART1 |
| TX Pin | PA9 |
| RX Pin | PA10 |
| Baud Rate | 115200 |
| Word Length | 8 Bits |
| Stop Bits | 1 |
| Parity | None |
| Hardware Flow Control | None |

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Configure UART using STM32CubeMX and HAL.

Establish communication between the STM32 and a PC terminal.

Implement character transmission, string transmission, reception, and echo functionality.

### Working Principle

UART (Universal Asynchronous Receiver/Transmitter) is used for asynchronous serial communication.

The STM32 transmits data through its TX pin and receives data through its RX pin.

The communication parameters must match the settings of the PC terminal.

The STM32 HAL library provides functions to transmit and receive data.

**Important HAL Functions:**

- `HAL_UART_Init()` - Initializes the UART peripheral.
- `HAL_UART_Transmit()` - Transmits characters or strings.
- `HAL_UART_Receive()` - Receives characters or strings.
- `HAL_UART_Transmit_IT()` - Interrupt-driven transmission.
- `HAL_UART_Receive_IT()` - Interrupt-driven reception.
- `HAL_UART_Transmit_DMA()` - DMA-based transmission.
- `HAL_UART_Receive_DMA()` - DMA-based reception.

### Character and String Transmission

A character or string is transmitted from the STM32 to the PC terminal using the UART peripheral.

**Example Transmission:**

```c
unsigned char ch[] = "hello\r\n";

HAL_UART_Transmit(&huart1, ch, sizeof(ch)-1, HAL_MAX_DELAY);
```

The message is transmitted through USART1 and displayed on the terminal.

### UART Receive and Echo

The STM32 receives data from the PC and sends the received data back.

**Existing Code:**

```c
unsigned char rxbyte[6];

HAL_UART_Receive(&huart1, rxbyte, 6, 5000);

HAL_UART_Transmit(&huart1, rxbyte, 6, 5000);
```

This example attempts to receive six bytes and transmit them back.

A complete implementation should check the receive status and transmit only valid received data.

---

### 3. Pseudocode

1. Initialize the HAL library.
2. Configure the system clock.
3. Configure USART1 using STM32CubeMX.
4. Initialize UART through HAL.
5. Configure the PC terminal with matching UART settings.
6. Transmit a character or string.
7. Receive characters from the PC terminal.
8. Echo the received characters back to the PC.
9. Repeat the communication process.

---

### 4. Carriage Return and Line Feed Investigation

The experiment requires investigating the behaviour of carriage return and line feed characters in PuTTY.

**Control Characters:**

- `\r` - Carriage Return (CR)
- `\n` - Line Feed (LF)

**Test Cases:**

| Test | String |
|------|--------|
| Test 1 | `"HELLO\r\n"` |
| Test 2 | `"HELLO\r"` |
| Test 3 | `"HELLO\n"` |
| Test 4 | `"HELLO\r\nWORLD\r\n"` |

**Purpose:**

Observe the difference between CR and LF when displaying text on a serial terminal.

The actual observations in PuTTY are to be recorded after testing.

---

### 5. Code Base

**Available Project:**

`FIOT/UART/UART`

**Configuration:**

- STM32F103C8T6 Microcontroller
- USART1 Asynchronous Mode
- PA9 - USART1_TX
- PA10 - USART1_RX
- 115200 Baud Rate
- 72 MHz Configured System Clock
- STM32 HAL Libraries

**Current Implementation:**

The available source contains basic UART transmission and reception examples.

The active main loop receives six bytes and attempts to echo them back to the PC.

The implementation requires receive-status checking and verification.

---

### 6. Inference

The experiment demonstrates UART-based serial communication between the STM32 microcontroller and a PC terminal.

The expected result is successful character and string transmission, reception, and echo.

Actual UART communication results and terminal observations are pending verification.

---

## TASK 9B: String-Based Application Logic

### 1. Circuit Diagram

The experiment involves controlling an LED using commands transmitted from a PC terminal through UART.

**Hardware Components:**

- STM32 Microcontroller
- STM32 Development Board
- LED
- Current-Limiting Resistor
- USB-to-TTL Serial Converter
- PC with PuTTY
- Connecting Wires

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Develop a UART-based command interface for the STM32.

The system must accept string commands from a terminal and perform the corresponding LED operation.

### Required Commands

| UART Command | LED Operation |
|--------------|---------------|
| LED ON | Turn LED ON |
| LED OFF | Turn LED OFF |
| LED TOGGLE | Toggle LED State |

### Working Principle

The STM32 receives characters through UART.

The received characters form a string command.

The application compares the received command against predefined commands.

Based on the command, the STM32 performs the requested LED operation.

**Command Processing:**

```text
PC Terminal
     |
     v
UART Receive
     |
     v
Process Received String
     |
     v
Compare Command
     |
     +---- LED ON ------> Turn LED ON
     |
     +---- LED OFF -----> Turn LED OFF
     |
     +---- LED TOGGLE --> Toggle LED
```

---

### 3. Pseudocode

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize UART.
4. Configure the LED GPIO as output.
5. Receive characters from the PC terminal.
6. Store the characters in a command buffer.
7. Detect the end of the command.
8. Compare the received string with predefined commands.
9. If command is "LED ON", turn ON the LED.
10. If command is "LED OFF", turn OFF the LED.
11. If command is "LED TOGGLE", toggle the LED.
12. Continue receiving commands.

---

### 4. Code Base

**Required HAL Functions:**

- `HAL_UART_Receive()` - Receive UART data.
- `HAL_UART_Transmit()` - Send UART responses.
- `HAL_GPIO_WritePin()` - Set or reset the LED output.
- `HAL_GPIO_TogglePin()` - Toggle the LED state.

**Required Functionality:**

- UART Initialization
- Command Reception
- String Comparison
- LED ON Control
- LED OFF Control
- LED Toggle Control

**Source Code Status:**

A complete implementation of TASK 9B has not been identified in the available UART project.

---

### 5. Inference

UART commands can provide a simple text-based interface for controlling embedded hardware.

The expected result is that the STM32 receives commands from PuTTY and changes the LED state accordingly.

Implementation and hardware verification are pending.

---

## PROJECT FILES

**Available Original Project:**

`FIOT/UART/UART`

The project contains:

- STM32CubeMX `.ioc` Configuration
- `Core/Src` Source Files
- `Core/Inc` Header Files
- `Drivers` HAL and CMSIS Files
- `MDK-ARM` Keil Project Files

**Pending:**

- Complete TASK 9B source code
- Circuit diagrams
- Hardware verification
- PuTTY test observations

---

## EXPERIMENT STATUS

TASK 9A: Partial UART transmission and echo implementation available.

TASK 9B: UART command-controlled LED implementation pending.

Circuit diagrams and verified results will be added afterward.
