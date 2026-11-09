
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 8

**DATE:** 18/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** STM32F103C8T6 (Blue Pill) + STM32CubeMX + Keil MDK + STM32 HAL Libraries

---

## TASK 8A: GPIO Input/Output

### 1. Circuit Diagram

The experiment involves interfacing a push-button and an LED with the STM32 microcontroller.

The corresponding GPIO pins are configured so that the LED follows the switch state.

**Hardware Components:**

- STM32F103C8T6 Microcontroller
- STM32 Blue Pill Development Board
- Push-Button
- LED
- Current-Limiting Resistor
- Power Supply
- Connecting Wires

**GPIO Configuration from the Available Project:**

| GPIO Pin | Configuration | Function |
|----------|---------------|----------|
| PB0 | Digital Input with Pull-Up | Push-Button |
| PB1 | Push-Pull Output | LED |

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The push-button is connected to PB0, and the LED is controlled using PB1.

The STM32 continuously reads the state of the input pin using the HAL GPIO functions.

When the switch input reads LOW, the program sets PB1 HIGH.

Otherwise, PB1 is set LOW.

The LED therefore follows the switch state, assuming an active-HIGH LED connection.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Enable the required GPIO peripheral clocks.
4. Configure PB0 as a digital input with pull-up.
5. Configure PB1 as a push-pull digital output.
6. Start an infinite loop.
7. Read the push-button state.
8. If PB0 is LOW, set PB1 HIGH.
9. Otherwise, set PB1 LOW.
10. Repeat continuously.

**Code Base:**

The program is implemented using STM32 HAL GPIO functions.

**Important HAL Functions:**

- `HAL_Init()` - Initializes the HAL library.
- `SystemClock_Config()` - Configures the system clock.
- `MX_GPIO_Init()` - Initializes the GPIO pins.
- `HAL_GPIO_ReadPin()` - Reads the switch input.
- `HAL_GPIO_WritePin()` - Controls the LED output.

**Main Application Logic:**

```c
if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
}
else
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}
```

**Available Project:**

`FIOT/Ex-2/Task-1`

The project contains the STM32CubeMX configuration, HAL-generated source files and Keil project configuration.

---

### 3. Inference

This task demonstrates basic STM32 GPIO input and output interfacing.

The expected result is that the LED follows the state of the push-button.

Actual hardware operation is pending verification.

---

## TASK 8B: Event-Based Control

### 1. Circuit Diagram

The experiment uses a push-button and LED connected to STM32 GPIO pins.

The circuit can use the same hardware connections as TASK 8A.

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Modify the firmware so that every valid button press toggles the LED state.

Investigate switch bounce and implement a software solution to ensure that one physical press produces exactly one toggle.

**Working Principle:**

Unlike TASK 8A, the LED does not simply follow the current button state.

Instead, the system detects a valid button press event and changes the LED state.

Switch debouncing prevents unwanted multiple toggles.

**Expected Behaviour:**

| Button Event | LED State |
|--------------|-----------|
| Initial State | OFF |
| First Valid Press | ON |
| Second Valid Press | OFF |
| Third Valid Press | ON |
| Fourth Valid Press | OFF |

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock and GPIO pins.
3. Initialize the LED state.
4. Monitor the push-button input.
5. Detect a new button press.
6. Apply software debouncing.
7. Confirm the button press is valid.
8. Toggle the LED state once.
9. Wait for the button to be released.
10. Repeat continuously.

**Important HAL Functions:**

- `HAL_GPIO_ReadPin()` - Read the button.
- `HAL_GPIO_TogglePin()` - Toggle the LED.
- `HAL_GetTick()` - Provide a millisecond time reference.

**Source Code:** Pending implementation and verification.

---

### 3. Inference

This task demonstrates event-based GPIO control and software debouncing.

The expected result is exactly one LED toggle for each valid physical button press.

Hardware verification is pending.

---

## TASK 8C: Short Press vs Long Press

### 1. Circuit Diagram

This task uses the same STM32, push-button and LED connections.

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Modify the application to classify button presses based on how long the button remains pressed.

**Press Duration:**

| Button Press | Duration |
|--------------|----------|
| Short Press | Less than 1 second |
| Long Press | Greater than or equal to 1 second |

**Required System Response:**

| User Action | System Response |
|-------------|-----------------|
| Short Press | Toggle LED |
| Long Press | Enter continuous LED blinking mode |
| Next Short Press | Stop blinking |
| Long Press Again | Return to blinking mode |

**Working Principle:**

The program records the system tick when the button is pressed.

The STM32 continues executing the main application while monitoring the button.

When the button is released, the program records the release time.

The press duration is calculated using:

```text
Press Duration = Release Time - Press Time
```

The duration determines whether the event is a short press or a long press.

**Important Constraint:**

The application must not use a blocking delay to determine whether a button press is long.

`HAL_GetTick()` is used to measure elapsed time without blocking the application.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock and GPIO.
3. Initialize the LED and operating mode.
4. Continuously monitor the push-button.
5. Detect a valid button press.
6. Record the press start time using HAL_GetTick().
7. Continue executing the application.
8. Detect the valid button release.
9. Record the release time.
10. Calculate the press duration.
11. If duration is less than 1000 ms, classify as short press.
12. Otherwise, classify as long press.
13. Perform the required LED operation.
14. Continue monitoring the button.

**Important HAL Functions:**

- `HAL_GPIO_ReadPin()`
- `HAL_GPIO_WritePin()`
- `HAL_GPIO_TogglePin()`
- `HAL_GetTick()`

**Source Code:** Pending implementation and verification.

---

### 3. Inference

This task demonstrates press-duration measurement and event-based GPIO control.

The expected result is correct classification of short and long button presses with the corresponding LED behaviour.

Hardware verification is pending.

---

## PROJECT FILES

**Available Projects:**

- `Ex-2/Task-1` - GPIO input/output using PB0 and PB1
- `EX_1/LED_BLINK` - Basic LED toggling example using PC13

**Required Project Components:**

- STM32CubeMX `.ioc` Configuration
- `Core/Src` Source Files
- `Core/Inc` Header Files
- Keil MDK Project Configuration
- Required STM32 HAL and CMSIS Dependencies

**Pending:**

- TASK 8B implementation
- TASK 8C implementation
- Circuit diagrams
- Hardware verification results

---

## EXPERIMENT STATUS

TASK 8A: Source code and STM32 project available; hardware verification pending.

TASK 8B: Complete event-based toggle and debouncing implementation not identified.

TASK 8C: Short-press and long-press classification implementation not identified.

Circuit diagrams and verified observations will be added later.

