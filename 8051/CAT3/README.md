
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 3

**DATE:** 27/07/2026

**NAME OF EXP:** Timer-Based LED Pattern Generator and Button Interrupt Controller

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## ACTIVITY: Four-State LED Control System

### 1. Circuit Diagram

The system consists of four LEDs connected to four GPIO pins and one push-button connected to a GPIO input.

**Hardware Components:**

- AT89S52 Microcontroller
- 8051 Development Board
- Four LEDs
- One Push-Button
- Current-Limiting Resistors
- Power Supply
- Connecting Wires

The exact GPIO connections and clock configuration will be documented along with the circuit diagram.

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The experiment involves designing a register-level GPIO controller using bare-metal Embedded C.

Four LEDs are configured as digital outputs, and one push-button is configured as a digital input.

Each valid button press advances the system to the next LED operating mode.

Switch debouncing must ensure that one physical button press causes exactly one state transition.

The system operates in four modes.

#### Mode 1: Running LED Pattern

Initially, all LEDs are OFF.

On the first valid button press, the system enters Mode 1.

The LEDs turn ON sequentially:

LED1 → LED2 → LED3 → LED4 → LED1 → ...

Only one LED is active at a time.

#### Mode 2: Binary Counter

On the second valid button press, the system enters Mode 2.

The four LEDs display a 4-bit binary counting sequence.

```text
0000
0001
0010
0011
0100
...
1111
0000
```

The sequence repeats continuously.

#### Mode 3: Alternating LED Pattern

On the third valid button press, the system enters Mode 3.

The LEDs alternate between two patterns:

```text
1010
0101
1010
0101
...
```

#### Mode 4: All LED Flash

On the fourth valid button press, the system enters Mode 4.

All four LEDs flash simultaneously.

```text
1111
0000
1111
0000
...
```

---

### 3. Pseudocode

1. Include the 8051 register definition header file.
2. Configure four GPIO pins as LED outputs.
3. Configure one GPIO pin as a push-button input.
4. Initialize all LEDs to the OFF state.
5. Initialize the current mode to the idle state.
6. Monitor the push-button for a valid press.
7. Apply switch debouncing to prevent multiple transitions.
8. On each valid press, advance to the next mode.
9. Execute the selected LED pattern.
10. Repeat the selected pattern until another valid press occurs.
11. Continue the four-mode operating sequence.

---

### 4. Code Base

The implementation is intended to use Embedded C with direct 8051 register access.

**Concepts Used:**

- GPIO Input and Output
- Memory-Mapped Register Access
- LED Pattern Generation
- Push-Button Interfacing
- Switch Debouncing
- State Machine
- Timer-Based Timing

**Implementation Requirements:**

- No Arduino APIs
- No HAL Libraries
- No RTOS Services
- One mode transition per valid button press
- Four distinct LED operating modes

**Source Code:** Pending implementation and verification.

---

### 5. Inference

The experiment is designed to demonstrate GPIO control, button interfacing, switch debouncing, and state-based LED pattern generation using the AT89S52 microcontroller.

The expected behavior is that each valid push-button press selects the next operating mode without producing multiple unintended transitions.

The implementation and physical hardware results are yet to be verified.

---

## PROJECT FILES

The following files will be added after implementation:

- Embedded C Source Code
- Keil µVision Project File
- Required Startup File
- Firmware HEX File (if generated)
- Circuit Diagram

---

## EXPERIMENT STATUS

Documentation prepared according to the official CAT3 question.

Source code, circuit diagram, and hardware verification are pending.
