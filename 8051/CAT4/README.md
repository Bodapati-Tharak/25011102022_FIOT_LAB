
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 4

**DATE:** 03/08/2026

**NAME OF EXP:** Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## ACTIVITY: Matrix Keypad, Seven-Segment Display and LED Control

### 1. Circuit Diagram

The experiment involves interfacing a matrix keypad, a seven-segment display, and four LEDs with the AT89S52 microcontroller.

**Hardware Components:**

- AT89S52 Microcontroller
- 8051 Development Board
- Matrix Keypad
- Seven-Segment Display
- Four LEDs
- Current-Limiting Resistors
- Power Supply
- Connecting Wires

The exact GPIO pin assignments, clock configuration and peripheral connections will be documented in the circuit diagram.

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Design an embedded human-machine interface in which the matrix keypad acts as the input device, the seven-segment display provides visual feedback, and the LEDs indicate different operating modes.

Whenever a valid key is pressed:

1. Display the key value on the seven-segment display.
2. Execute the corresponding LED function.

---

### 3. Functional Requirements

| Key Press | Seven-Segment Display | LED Operation |
|-----------|------------------------|---------------|
| 1 | 1 | LED1 ON |
| 2 | 2 | LED2 ON |
| 3 | 3 | LED3 ON |
| 4 | 4 | LED4 ON |
| 5 | 5 | Running LED Pattern |
| 6 | 6 | Alternate LEDs (1010 ↔ 0101) |
| 7 | 7 | Binary Counter (0–15) |
| 8 | 8 | All LEDs Blink |
| 9 | 9 | All LEDs OFF |
| 0 | 0 | Reset System |

---

### 4. Working Principle

The matrix keypad provides user input to the microcontroller.

The microcontroller scans the keypad to detect the pressed key.

After detecting a valid key, the corresponding digit is displayed on the seven-segment display.

Based on the pressed key, the microcontroller executes the associated LED operation.

**Keypad Operations:**

**Keys 1–4: Individual LED Control**

Each key turns ON the corresponding LED.

**Key 5: Running LED Pattern**

The LEDs operate sequentially:

LED1 → LED2 → LED3 → LED4 → Repeat

**Key 6: Alternating LED Pattern**

Four LEDs alternate between:

1010 → 0101 → Repeat

**Key 7: Binary Counter**

The four LEDs represent binary values from 0 to 15.

0000 → 0001 → 0010 → ... → 1111

**Key 8: All LEDs Blink**

All four LEDs blink simultaneously.

1111 → 0000 → Repeat

**Key 9: All LEDs OFF**

All LEDs are turned OFF.

**Key 0: Reset System**

The system returns to its initial state.

---

### 5. Pseudocode

1. Include the 8051 register definition header.
2. Configure GPIO connections for the keypad.
3. Configure GPIO connections for the seven-segment display.
4. Configure GPIO pins for four LEDs.
5. Initialize the peripherals.
6. Start scanning the keypad.
7. Detect a valid key press.
8. Identify the pressed key value.
9. Display the corresponding digit.
10. Execute the required LED operation.
11. Continue monitoring keypad input.
12. Repeat continuously.

---

### 6. Code Base

The program is intended to be implemented using bare-metal Embedded C and direct 8051 register access.

**Required Functions:**

```c
void keypad_scan(void);

void display_digit(unsigned char value);

void led_control(unsigned char key);

void running_led(void);

void binary_counter(void);

void alternate_led(void);

void blink_all(void);
```

**Function Descriptions:**

- `keypad_scan()` - Scans the keypad to detect a key press.
- `display_digit()` - Displays the selected digit on the seven-segment display.
- `led_control()` - Selects the corresponding LED operation.
- `running_led()` - Generates the running LED pattern.
- `binary_counter()` - Displays binary values from 0 to 15 using four LEDs.
- `alternate_led()` - Alternates between 1010 and 0101.
- `blink_all()` - Controls simultaneous LED blinking.

**Programming Requirements:**

- Embedded C
- Direct GPIO Register Access
- No Arduino APIs
- No HAL Libraries
- No RTOS Services

**Source Code:** Pending implementation and verification.

---

### 7. Inference

The experiment is designed to demonstrate interfacing a matrix keypad, seven-segment display and LEDs with the AT89S52 microcontroller.

The expected operation is to identify the pressed key, display its value and execute the corresponding LED function.

The implementation and hardware results are pending verification.

---

## PROJECT FILES

The required files will be added after implementation and verification.

- Embedded C Source Code
- Keil µVision Project File
- Required Startup File
- Firmware HEX File (if generated)
- Circuit Diagram

---

## EXPERIMENT STATUS

Documentation prepared according to the official CAT4 question.

Source code, circuit diagram and hardware verification are pending.
