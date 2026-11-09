
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 5

**DATE:** 10/08/2026

**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller + 8051 Development Board + Keil µVision

---

## TASK 1: LED Fading Using Software PWM

### 1. Circuit Diagram

The experiment uses Timer0 of the AT89S52 microcontroller to generate periodic interrupts for software-based timing and LED brightness control.

**Hardware Components:**

- AT89S52 Microcontroller
- 8051 Development Board
- LED
- Current-Limiting Resistor
- 11.0592 MHz Crystal (reference clock from question)
- Oscilloscope for timing verification
- Power Supply

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Timer0 is configured to generate periodic interrupts.

The timer interrupt acts as a software time base instead of using blocking software delay loops.

Initially, a periodic interrupt is used to toggle an LED every 1 second.

The same timer-based approach is extended to generate software PWM signals for controlling LED brightness.

The PWM duty cycle is gradually varied from 0% to 100% and back to 0%.

**Duty Cycle Sequence:**

```text
0% → 10% → 20% → 30% → 40% → 50%
→ 60% → 70% → 80% → 90% → 100%
→ 90% → 80% → ... → 10% → 0%
```

**Suggested PWM Frequency:** 500 Hz to 1 kHz

The LED should appear to fade smoothly rather than visibly flicker.

### Timer Calculation

For a classic 12-clock 8051 with an 11.0592 MHz crystal:

```text
Machine Cycle Time = 12 / 11.0592 MHz

Machine Cycle Time ≈ 1.085 µs

Counts for 1 ms ≈ 922

Timer Reload = 65536 - 922

Timer Reload = 64614 = FC66H
```

Therefore:

```c
TH0 = 0xFC;
TL0 = 0x66;
```

The reload values provide an approximately 1 ms timer interval, assuming the specified clock configuration.

### Pseudocode

1. Include the 8051 register definition header.
2. Configure the LED GPIO pin as output.
3. Configure Timer0 in 16-bit mode.
4. Load Timer0 with the calculated reload value.
5. Enable Timer0 interrupt and global interrupts.
6. Start Timer0.
7. Generate a periodic software time base.
8. Toggle the LED at the required interval.
9. Extend the timing logic to generate software PWM.
10. Gradually increase the PWM duty cycle.
11. Gradually decrease the PWM duty cycle.
12. Repeat continuously without blocking delay loops.

### Code Base

The existing project contains a Timer0 interrupt example using Embedded C.

**Important Registers:**

- `TMOD` - Timer mode configuration
- `TH0` - Timer0 high-byte register
- `TL0` - Timer0 low-byte register
- `ET0` - Timer0 interrupt enable
- `EA` - Global interrupt enable
- `TR0` - Timer0 start/stop control

**Programming Requirements:**

- Direct register access
- Timer0 interrupt-based timing
- Non-blocking implementation
- No software delay loops for timing
- No Arduino APIs
- No HAL libraries
- No RTOS services

**Implementation Status:**

Timer0 interrupt example available. One-second timing accumulation and complete PWM fading require implementation and verification.

---

### 3. Inference

The timer interrupt provides a periodic time base that can be used to control LED output and generate software PWM.

Changing the PWM duty cycle changes the average LED drive level and therefore its perceived brightness.

The actual fading behavior and waveform measurements are pending verification.

---

## TASK 2: Variable-Frequency Square-Wave Generation

### 1. Circuit Diagram

A GPIO output pin is used to generate square-wave and pulse signals under timer interrupt control.

**Required Hardware:**

- AT89S52 Microcontroller
- 8051 Development Board
- GPIO Output Pin
- Oscilloscope
- Power Supply

**Circuit Diagram:** To be added.

---

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The microcontroller generates a square-wave signal by periodically changing a GPIO output between HIGH and LOW states.

The output frequency is controlled using the timer-based interrupt interval.

Different output frequencies must be generated and verified using an oscilloscope.

### Required Frequency Modes

| Mode | Frequency |
|------|-----------|
| Mode 1 | 100 Hz |
| Mode 2 | 500 Hz |
| Mode 3 | 1 kHz |
| Mode 4 | 2 kHz |
| Mode 5 | 5 kHz |

### Different Signal Types

**1. Square Wave**

```text
101010101010
```

**2. Variable Duty-Cycle Wave**

```text
1111000011110000
```

**3. Pulse Train**

```text
100000001000000010000000
```

**4. Burst Signal**

```text
1010101010 0000000000 1010101010
```

### Pseudocode

1. Configure a GPIO pin as output.
2. Initialize Timer0 in 16-bit mode.
3. Calculate the required timing interval.
4. Load the appropriate timer reload value.
5. Enable the timer interrupt.
6. Start Timer0.
7. Toggle the output according to the selected frequency.
8. Generate the required signal pattern.
9. Verify output frequency and duty cycle using an oscilloscope.
10. Repeat continuously.

### Code Base

The implementation must use direct register access and timer interrupt-based GPIO control.

The existing Timer0 example provides a starting point.

Multi-frequency signal generation and the additional waveform patterns are pending implementation.

---

### 3. Inference

Timer interrupts can be used to generate periodic digital signals without relying on blocking software delays.

The output frequency depends on the effective interval between GPIO transitions.

The actual waveform frequencies and duty cycles must be verified using an oscilloscope.

---

## TASK 3: Stepper-Motor Speed and Direction Control (Optional)

### 1. Circuit Diagram

The experiment uses a timer interrupt to control the stepping sequence and speed of a stepper motor through a suitable motor driver.

**Circuit Diagram:** To be added if implemented.

---

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The timer interrupt determines when the microcontroller advances to the next step in the motor sequence.

**Stepping Sequence:**

```text
1000 → 0100 → 0010 → 0001 → Repeat
```

Reversing the stepping order can reverse the direction of rotation.

**Speed Modes:**

| Speed | Step Interval |
|-------|---------------|
| Slow | 100 ms/step |
| Medium | 50 ms/step |
| Fast | 10 ms/step |

### Pseudocode

1. Configure GPIO outputs for the motor driver.
2. Configure Timer0.
3. Select the motor speed.
4. Select the motor direction.
5. Generate the first motor step.
6. Wait for the timer-based step interval.
7. Generate the next step in the sequence.
8. Repeat the sequence while the motor operates.

### Code Base

This task is optional in the official CAT5 question.

**Implementation Status:** Not included in the currently identified source code.

---

### 3. Inference

A timer-controlled stepping sequence can be used to regulate stepper-motor speed and direction.

Actual operation has not been verified.

---

## PROJECT FILES

**Available in the original project:**

- `PWM.c` - Timer0 interrupt example
- `led4.uvproj` - Keil µVision project
- `STARTUP.A51` - Startup assembly file

**Pending:**

- Correction and verification of source code
- Complete PWM and frequency-mode implementation
- Circuit diagram
- Hardware verification results

---

## EXPERIMENT STATUS

Timer0 interrupt code is available but requires correction.

PWM fading, frequency modes and actual hardware measurements remain unverified.

The optional stepper-motor task has not been implemented in the identified source files.
