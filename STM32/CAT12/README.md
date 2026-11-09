
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 12

**DATE:** 23/10/2026

**NAME OF EXP:** BME280 Sensor Interfacing Using I²C and Bosch Sensor API

**HARDWARE SETUP / PLATFORM:** STM32F401RE Nucleo Development Board + BME280 Sensor + STM32CubeMX + Keil MDK + STM32 HAL Libraries + Bosch Sensortec BME280 Sensor API

---

## OBJECTIVE

Develop an STM32-based environmental sensing application to interface the BME280 sensor using the I²C protocol and obtain compensated temperature, pressure, and humidity measurements.

Use the official Bosch Sensortec BME280 Sensor API for sensor initialization, configuration, data acquisition, and compensation.

This implementation focuses exclusively on direct STM32–BME280 sensor interfacing.

---

## 1. Circuit Diagram

The STM32F401RE communicates with the BME280 environmental sensor through the I²C1 peripheral.

### Hardware Components

- STM32F401RE Nucleo Development Board
- BME280 Environmental Sensor
- USB Cable
- Connecting Wires
- ST-LINK Programmer/Debugger

### Pin Connections

| BME280 | STM32F401RE | Function |
|--------|-------------|----------|
| VCC | 3.3V | Power Supply |
| GND | GND | Common Ground |
| SCL | PB8 | I2C1 Clock |
| SDA | PB9 | I2C1 Data |

The I²C bus requires suitable SDA and SCL pull-up resistors. The BME280 must be configured for I²C operation.

**Circuit Diagram:** To be added.

### Peripheral Configuration

| Parameter | Configuration |
|-----------|---------------|
| Microcontroller | STM32F401RET6 |
| Interface | I2C1 |
| SCL | PB8 |
| SDA | PB9 |
| I²C Clock Speed | 100 kHz |
| Addressing Mode | 7-bit |
| BME280 Address | 0x76 |
| System Clock | 84 MHz |

---

## 2. Core Logic / Pseudocode / Code Base

### Working Principle

The BME280 measures three environmental parameters:

1. Temperature
2. Atmospheric Pressure
3. Relative Humidity

The STM32 communicates with the sensor using I²C.

The Bosch BME280 API is used to initialize the sensor, configure measurement settings, retrieve sensor measurements, and calculate compensated outputs.

The measured values are stored in variables and can be inspected using the Keil debugger.

---

### Step 1: Download and Arrange Driver Files

The official Bosch Sensortec BME280 Sensor API provides three required files.

**Driver Files:**

- `bme280.c`
- `bme280.h`
- `bme280_defs.h`

**Driver Location:**

```text
Core/
├── Inc/
│   ├── bme280.h
│   └── bme280_defs.h
└── Src/
    └── bme280.c
```

The files are obtained from:

[Bosch Sensortec BME280 Sensor API](https://github.com/boschsensortec/BME280_SensorAPI)

---

### Step 2: Include Driver Files in Keil

1. Open the STM32 project in Keil µVision.
2. Add `bme280.c` to the application source group.
3. Include `bme280.h` and `bme280_defs.h` through the project header search paths.
4. Verify that the STM32 HAL I²C driver files are included.
5. Configure I2C1 using STM32CubeMX.

---

### Step 3: Implement STM32 I²C Interface Functions

The Bosch driver requires three interface functions:

- I²C register read
- I²C register write
- Delay function

**Reading Sensor Registers:**

`HAL_I2C_Mem_Read()` reads data from the BME280 registers.

**Writing Sensor Registers:**

`HAL_I2C_Mem_Write()` writes configuration data to the BME280 registers.

**Delay Function:**

`HAL_Delay()` provides the required waiting intervals for sensor operations.

The STM32-specific interface functions are linked to the Bosch API through function pointers.

**Application Code:**

```c
dev.intf_ptr = &dev_addr;
dev.intf = BME280_I2C_INTF;

dev.read = user_i2c_read;
dev.write = user_i2c_write;
dev.delay_us = user_delay_us;
```

The configured sensor address is `0x76`.

---

### Step 4: Initialize the BME280

The sensor is initialized using:

```c
rslt = bme280_init(&dev);
```

During initialization, the Bosch API reads the sensor identification and calibration information required for compensated measurements.

If initialization fails, the application enters its error handler.

---

### Step 5: Configure Sensor Settings

The available implementation configures the following sensor parameters:

| Parameter | Configuration |
|-----------|---------------|
| Temperature Oversampling | 1X |
| Pressure Oversampling | 1X |
| Humidity Oversampling | 1X |
| Filter | Off |
| Standby Time | 1000 ms |
| Power Mode | Normal |

**Sensor Configuration:**

```c
settings.osr_h = BME280_OVERSAMPLING_1X;
settings.osr_p = BME280_OVERSAMPLING_1X;
settings.osr_t = BME280_OVERSAMPLING_1X;

settings.filter = BME280_FILTER_COEFF_OFF;
settings.standby_time = BME280_STANDBY_TIME_1000_MS;
```

The configuration is applied through the Bosch sensor settings API.

The sensor is then configured to operate in normal mode for repeated measurements.

---

### Step 6: Read Sensor Data

The STM32 reads all three parameters using:

```c
rslt = bme280_get_sensor_data(
    BME280_ALL,
    &comp_data,
    &dev
);
```

If the API reports successful data acquisition, the compensated sensor values are stored in application variables.

**Data Processing:**

```c
if (rslt == BME280_OK)
{
    temperature = comp_data.temperature;
    pressure = comp_data.pressure / 100.0f;
    humidity = comp_data.humidity;
}
```

**Measurement Units:**

| Variable | Measurement | Unit |
|----------|-------------|------|
| temperature | Temperature | °C |
| pressure | Atmospheric Pressure | hPa |
| humidity | Relative Humidity | %RH |

The Bosch API handles the sensor compensation calculations.

Pressure is divided by 100 to convert from pascals to hectopascals.

---

### Step 7: Continuous Sensor Monitoring

The application continuously reads the environmental sensor.

**Pseudocode:**

1. Initialize HAL.
2. Configure the system clock.
3. Initialize GPIO.
4. Initialize I2C1.
5. Configure Bosch API interface functions.
6. Initialize the BME280 sensor.
7. Configure oversampling and filter settings.
8. Set the sensor to normal mode.
9. Read temperature, pressure, and humidity.
10. Store the compensated measurements.
11. Wait for 1000 milliseconds.
12. Repeat continuously.

---

## 3. Debugger Verification

The application stores the compensated sensor measurements in variables.

These variables can be observed using the Keil µVision Watch window.

### Variables to Monitor

| Variable | Description |
|----------|-------------|
| `rslt` | Bosch API return status |
| `dev_addr` | BME280 I²C address |
| `temperature` | Compensated temperature |
| `pressure` | Compensated pressure |
| `humidity` | Compensated relative humidity |
| `comp_data` | Bosch sensor data structure |

### Verification Procedure

1. Build the STM32 application using Keil.
2. Program the STM32F401RE through ST-LINK.
3. Start the debugger.
4. Open the Watch window.
5. Add the measurement variables.
6. Execute the program.
7. Observe the sensor measurements.
8. Verify that the values update periodically.
9. Observe whether the readings change when the sensor environment changes.

### Expected Readings

```text
Temperature : XX.XX °C
Pressure    : XXXX.XX hPa
Humidity    : XX.XX %RH
```

Actual sensor values depend on the environmental conditions.

No experimental measurements are claimed until verified on hardware.

---

## 4. Project Files

**Matching Original Project:**

`FIOT/i2c/sense`

**Project Components:**

- `sense.ioc` - STM32CubeMX configuration
- `Core/Src/main.c` - Main application
- `Core/Src/bme280.c` - Bosch sensor driver
- `Core/Inc/bme280.h` - Bosch driver header
- `Core/Inc/bme280_defs.h` - BME280 definitions
- `Drivers/` - STM32 HAL and CMSIS dependencies
- `MDK-ARM/` - Keil project configuration

**Project Configuration:**

- STM32F401RET6
- I2C1
- PB8 - SCL
- PB9 - SDA
- 100 kHz I²C bus
- BME280 address 0x76
- 84 MHz system clock

---

## 5. Inference

This experiment demonstrates interfacing the BME280 environmental sensor with the STM32F401RE microcontroller using the I²C communication protocol.

The Bosch BME280 Sensor API provides sensor initialization, configuration, data acquisition, and compensated measurements of temperature, pressure, and humidity.

The STM32 periodically retrieves the measurements and stores them in application variables for monitoring through the debugger.

Actual hardware measurements and circuit verification will be documented after testing.

---

## EXPERIMENT STATUS

- STM32 I²C configuration: Available
- Bosch BME280 driver: Available
- Sensor initialization code: Available
- Temperature measurement code: Available
- Pressure measurement code: Available
- Humidity measurement code: Available
- Debugger-based measurements: Pending verification
- Circuit diagram: To be added

**Scope:** Direct BME280 sensor interfacing with STM32 using I²C.
