
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 2

**DATE:** 20/07/2026

**NAME OF EXP:** 8051 Tool Chain setup – Development Board – AT89S52

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## TASK A: Hardware Board Bring-Up

### 1. Circuit Diagram

The experiment involves identifying the AT89S52 microcontroller, programmer, power supply, user LED and GPIO connections.

**Hardware Details:**

| Parameter | Details |
|---|---|
| MCU | AT89S52 |
| CPU Core | 8051 |
| Operating Voltage | To be verified on hardware |
| Debug/Programming Interface | To be verified |
| LED GPIO Port | P1 (as used in source code) |
| LED GPIO Pin | P1.0 (as used in source code) |
| LED Active State | To be verified |
| LED Frequency | Target: approximately 1 Hz |

Circuit diagram: To be added.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The microcontroller board is connected to the host computer using the appropriate programming interface. The board's power rails, LED connections and GPIO pins must be identified and verified before programming.

**Procedure:**

1. Identify the AT89S52 microcontroller.
2. Identify the board's power supply and programmer.
3. Verify the supply voltage using a multimeter.
4. Identify the user LED GPIO port and pin.
5. Configure the target device in Keil µVision.
6. Compile the Embedded C program.
7. Program the microcontroller and verify its operation.

### 3. Inference

Hardware bring-up confirms the board's connections, power supply and programming interface before the GPIO experiment.

Actual hardware measurements are to be recorded after verification.

---

## TASK B: Bare-Metal LED Blink

### 1. Circuit Diagram

The experiment demonstrates LED blinking using direct GPIO register access on the 8051 microcontroller.

**Connections used in the program:**

- Microcontroller: AT89S52
- GPIO Port: Port 1
- GPIO Pin: P1.0
- Peripheral: LED with suitable current-limiting resistor
- Power Supply: As required by the development board

Circuit diagram: To be added.

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The LED is controlled through the P1.0 GPIO pin.

The program repeatedly changes the GPIO output state and uses a software delay between transitions to produce a blinking effect.

**Pseudocode:**

1. Include the 8051 register definition header.
2. Define P1.0 as the LED control pin.
3. Initialize the LED output state.
4. Enter an infinite loop.
5. Toggle the LED output.
6. Execute the software delay.
7. Repeat continuously.

**Code Base:**

The program is written in Embedded C using Keil C51.

- `reg51.h` provides 8051 register definitions.
- `sbit led = P1^0` assigns the LED control variable to P1.0.
- `led = !led` toggles the GPIO output state.
- `delay()` generates a software timing interval.
- `while(1)` repeats the blinking operation continuously.

The delay must be calibrated for the actual MCU clock frequency to achieve approximately 1 Hz blinking.

### 3. Inference

The intended result is periodic LED blinking through direct GPIO register control.

The actual blinking frequency and hardware result require verification.

---

## TASK C: Custom Delay Function

### 1. Core Logic / Pseudocode / Code Base

**Working Principle:**

A custom software delay function uses nested loops to introduce an approximate timing interval without using Arduino APIs, HAL libraries or RTOS services.

**Pseudocode:**

1. Define a delay function.
2. Initialize the outer loop counter.
3. Execute the inner loop repeatedly.
4. Continue until both loop counters finish.
5. Return to the main program.
6. Use the delay between LED state transitions.

**Code Base:**

A `delay()` function is included in the Embedded C source.

Its timing depends on the processor clock and compiler optimization. The required timing must be verified on the actual hardware.

### 2. Inference

The custom delay function demonstrates basic software-based timing for controlling GPIO output transitions.

---

## PROJECT FILES

The required source and project files will be added after code verification.

- Embedded C source code
- Keil µVision project file
- Required startup file
- Firmware HEX file, if applicable
- Circuit diagram

---

## FINAL INFERENCE

This experiment introduces the 8051 development toolchain, hardware board bring-up, direct GPIO register access, LED control and software delay generation.

The final implementation results will be updated after hardware verification.
