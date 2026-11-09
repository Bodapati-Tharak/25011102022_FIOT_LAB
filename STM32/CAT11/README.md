
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 11

**DATE:** 14/10/2026

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO and User Input Programming

**HARDWARE SETUP / PLATFORM:** STM32 Nucleo-F401RE Development Board + STM32CubeMX + Keil MDK + STM32 HAL Libraries

---

## PREREQUISITES

Before implementing the experiment:

1. Observe the on-board oscillator frequency.
2. Identify the STM32F401RE controller specifications, including clock frequency, GPIO ports, UARTs, I2C and SPI peripherals.
3. Decide the clock configuration using STM32CubeMX.
4. Refer to the Nucleo-F401RE board pinout.
5. Identify the on-board LED and user push-button connections.

**Reference:** STM32 Nucleo-64 User Manual UM1724

---

## TASK 1: On-board LED Bring-Up

### 1. Circuit Diagram

The experiment verifies the STM32 Nucleo-F401RE board by controlling its on-board LED through a GPIO output.

**Hardware Components:**

- STM32 Nucleo-F401RE Development Board
- On-board LED
- ST-LINK Programmer/Debugger
- USB Cable
- PC with STM32CubeMX and Keil MDK

The exact GPIO pin and system clock configuration will be documented with the circuit diagram.

**Circuit Diagram:** To be added.

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Develop and program an STM32 application to verify the NUCLEO-F401RE hardware and GPIO output configuration by blinking the on-board LED at a fixed interval.

**Working Principle:**

The STM32 microcontroller controls an on-board LED through a GPIO output.

The program alternately changes the LED output state with a fixed time interval between transitions.

**Pseudocode:**

1. Initialize the STM32 HAL library.
2. Configure the system clock.
3. Enable the required GPIO peripheral clock.
4. Configure the LED GPIO pin as output.
5. Initialize the LED state.
6. Enter an infinite loop.
7. Toggle the LED GPIO output.
8. Wait for the selected interval.
9. Repeat continuously.

**Important HAL Functions:**

- `HAL_Init()` - Initialize the HAL library.
- `SystemClock_Config()` - Configure the system clock.
- `HAL_GPIO_TogglePin()` - Toggle the LED output.
- `HAL_Delay()` - Provide a delay between LED transitions.

**Source Code:** Pending implementation and verification.

### 3. Inference

This task demonstrates STM32 GPIO output configuration and basic hardware bring-up.

The expected result is periodic blinking of the on-board LED.

Actual hardware verification is pending.

---

## TASK 2: On-board Switch Control with State Remembrance

### 1. Circuit Diagram

The experiment uses the on-board user push-button to control the on-board LED.

**Hardware Components:**

- STM32 Nucleo-F401RE Development Board
- On-board User Push-Button
- On-board LED
- ST-LINK Programmer/Debugger
- USB Cable

**Circuit Diagram:** To be added.

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Modify the application so that the on-board push-button controls the LED.

The LED must toggle its state whenever a valid button press is detected.

The LED must remember its previous state after the button is released.

**Working Principle:**

The push-button is configured as a GPIO input and the LED is configured as a GPIO output.

The application monitors the button state and detects a new valid press.

Every valid press toggles the LED output.

Releasing the button does not change the LED state.

Switch debouncing prevents multiple unwanted toggles during one physical press.

**Expected Behaviour:**

| Button Action | LED State |
|---------------|-----------|
| Initial State | OFF |
| First Valid Press | ON |
| Button Released | Remains ON |
| Second Valid Press | OFF |
| Button Released | Remains OFF |
| Third Valid Press | ON |

### Pseudocode

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize the LED GPIO as output.
4. Initialize the button GPIO as input.
5. Initialize the LED state.
6. Continuously monitor the button.
7. Detect a new valid button press.
8. Apply software debouncing.
9. Toggle the LED state once.
10. Preserve the LED state after button release.
11. Repeat continuously.

**Important HAL Functions:**

- `HAL_GPIO_ReadPin()` - Read the push-button.
- `HAL_GPIO_TogglePin()` - Toggle the LED.
- `HAL_GetTick()` - Support time-based debouncing.

**Source Code:** Pending implementation and verification.

### 3. Inference

This task demonstrates GPIO input handling and state-based LED control.

The expected result is one LED toggle per valid button press.

The LED retains its previous state after the button is released.

Actual hardware testing is pending.

---

## TASK 3: Short-Press and Long-Press Detection

### 1. Circuit Diagram

The same on-board push-button and LED are used to distinguish between short and long button presses.

**Hardware Components:**

- STM32 Nucleo-F401RE Development Board
- On-board User Push-Button
- On-board LED
- ST-LINK Programmer/Debugger
- USB Cable

**Circuit Diagram:** To be added.

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Extend the application to distinguish between a short button press and a long button press.

The STM32 must perform different actions depending on how long the push-button remains pressed.

**Working Principle:**

The microcontroller records the time when the button is pressed.

When the button is released, the elapsed duration is calculated.

The button press is classified as short or long based on the selected duration threshold.

The official CAT11 question does not specify a numerical duration threshold or exact LED responses, so these must be defined and documented when the implementation is prepared.

**Press Duration:**

Press Duration = Release Time - Press Time

### Pseudocode

1. Initialize the HAL library.
2. Configure the system clock.
3. Configure the LED and push-button GPIO pins.
4. Initialize the application state.
5. Continuously monitor the push-button.
6. Detect a valid button press.
7. Record the press start time.
8. Monitor the button without interrupting normal application execution.
9. Detect button release.
10. Record the release time.
11. Calculate the press duration.
12. Compare the duration with the selected threshold.
13. Classify the event as a short or long press.
14. Perform the corresponding action.
15. Repeat continuously.

**Important HAL Functions:**

- `HAL_GPIO_ReadPin()` - Read the button state.
- `HAL_GetTick()` - Measure elapsed time.
- `HAL_GPIO_WritePin()` - Control the LED output.
- `HAL_GPIO_TogglePin()` - Toggle LED state.

**Source Code:** Pending implementation and verification.

### 3. Inference

This task demonstrates time-based button input classification using STM32 GPIO.

The expected result is accurate detection of short and long button presses, followed by the corresponding application action.

Hardware verification is pending.

---

## PROJECT FILES

**Required Project Components:**

- STM32CubeMX `.ioc` Configuration
- `Core/Src` Application Source Files
- `Core/Inc` Header Files
- `Drivers` STM32 HAL and CMSIS Dependencies
- `MDK-ARM` Keil Project Configuration
- Startup Assembly File
- Circuit Diagram

**Current Status:**

A matching CAT11 implementation has not been identified in the available project archive.

Project files will be added after implementation and verification.

---

## EXPERIMENT STATUS

**TASK 1:** On-board LED blink implementation pending.

**TASK 2:** Switch-controlled LED toggling and state remembrance implementation pending.

**TASK 3:** Short-press and long-press detection implementation pending.

Circuit diagrams, clock measurements and actual hardware results will be added after verification.

---

## FINAL INFERENCE

This experiment introduces STM32F401RE GPIO programming, on-board LED control, user push-button interfacing, state remembrance and button press-duration classification.

The required functionality and expected behavior have been documented according to the official CAT11 question.

Implementation and hardware verification are pending.
