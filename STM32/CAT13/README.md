
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 13

**DATE:** 27/10/2026

**NAME OF EXP:** BME280 Sensor Interfacing Using I²C and (MQTT) using Custom Built ESP8266 API

**HARDWARE SETUP / PLATFORM:** STM32F401RE Nucleo Development Board + BME280 Sensor + Wemos D1 Mini ESP8266 + STM32CubeMX + Keil MDK + STM32 HAL + Bosch BME280 API + Custom ESP8266 API + Node-RED

---

## OBJECTIVE

Develop an STM32-based environmental sensing application that reads compensated temperature, pressure, and humidity values from a BME280 sensor using I²C.

Transmit the sensor measurements through an ESP8266 Wi-Fi module using MQTT and visualize the received information in Node-RED.

---

## 1. Circuit Diagram

### Hardware Components

- STM32F401RE Nucleo Development Board
- BME280 Environmental Sensor
- Wemos D1 Mini ESP8266
- ST-LINK Programmer/Debugger
- Wi-Fi Access Point
- Connecting Wires
- Power Supply

### BME280 Connections

| BME280 | STM32F401RE | Function |
|--------|-------------|----------|
| VCC | 3.3V | Power |
| GND | GND | Ground |
| SCL | PB8 | I2C1 Clock |
| SDA | PB9 | I2C1 Data |

### ESP8266 Connections

| ESP8266 | STM32F401RE |
|---------|-------------|
| RX | PA9 (USART1_TX) |
| TX | PA10 (USART1_RX) |
| GND | GND |
| Power | Appropriate regulated supply |

### Peripheral Configuration

| Parameter | Configuration |
|-----------|---------------|
| Microcontroller | STM32F401RET6 |
| System Clock | 84 MHz |
| I²C Peripheral | I2C1 |
| I²C Speed | 100 kHz |
| BME280 Address | 0x76 (0x77 fallback in source) |
| UART Peripheral | USART1 |
| UART Baud Rate | 115200 |
| MQTT Broker | broker.emqx.io |
| MQTT Port | 1883 |

The I²C lines require suitable pull-up resistors, and the ESP8266 UART signals use 3.3V logic.

**Circuit Diagram:** To be added.

---

## 2. Core Logic / Pseudocode / Code Base

### Working Principle

The STM32 reads temperature, humidity, and pressure measurements from the BME280 sensor using I²C.

The Bosch Sensortec BME280 API performs sensor initialization, configuration, raw measurement processing, and compensation.

The STM32 constructs a JSON payload containing the compensated measurements.

The ESP8266 module connects to a Wi-Fi access point and establishes a TCP connection with the MQTT broker.

The STM32 publishes the JSON payload through the custom ESP8266 MQTT library.

Node-RED subscribes to the MQTT topic and processes the received sensor data.

---

## Step 1: Integrate the Driver Files

### Bosch BME280 Sensor API

Required files:

- `bme280.c`
- `bme280.h`
- `bme280_defs.h`

### Custom ESP8266 Library

Required files:

- `ESPLib.c`
- `ESPLib.h`

### Directory Structure

```text
Core/
├── Inc/
│   ├── bme280.h
│   ├── bme280_defs.h
│   ├── ESPLib.h
│   └── main.h
└── Src/
    ├── bme280.c
    ├── ESPLib.c
    └── main.c
```

Add `bme280.c` and `ESPLib.c` to the Keil application project.

Verify that the corresponding header files are available through the compiler include paths.

---

## Step 2: Initialize the BME280 Sensor

The STM32 initializes the I²C peripheral.

The Bosch API functions are configured to use STM32 HAL communication functions.

### Interface Functions

- `HAL_I2C_Mem_Read()` - Read sensor registers.
- `HAL_I2C_Mem_Write()` - Write sensor registers.
- `HAL_Delay()` - Provide delay intervals.

### Sensor Initialization

```c
dev.intf = BME280_I2C_INTF;
dev.intf_ptr = &dev_addr;

dev.read = user_i2c_read;
dev.write = user_i2c_write;
dev.delay_us = user_delay_us;

rslt = bme280_init(&dev);
```

### Sensor Configuration

| Parameter | Value |
|-----------|-------|
| Temperature Oversampling | 1X |
| Pressure Oversampling | 1X |
| Humidity Oversampling | 1X |
| Filter | OFF |
| Standby Time | 1000 ms |
| Power Mode | Normal |

The sensor is configured for continuous environmental measurements.

---

## Step 3: Initialize ESP8266 and MQTT

The STM32 initializes the ESP8266 through USART1.

The module connects to a Wi-Fi network and then establishes a TCP connection with the MQTT broker.

### MQTT Configuration

| Parameter | Value |
|-----------|-------|
| Broker | broker.emqx.io |
| Port | 1883 |
| Client ID | Tharak01 |
| Keep Alive | 60 seconds |
| Connect Flag | CleanSession |
| Publish QoS | QoS0 |

### MQTT Initialization

```c
ESP8266_Init(StationMode, huart1);

ESP8266_wifiConnect("YOUR_SSID", "YOUR_PASSWORD");

ESP8266_portConnect("TCP", "broker.emqx.io", "1883");

MQTT_InitTypeDef_t mqttSetting = {0};

mqttSetting.keepAlive = 60;
mqttSetting.connectFlag = CleanSession;
mqttSetting.clientID = "Tharak01";

MQTT_connectBroker(&mqttSetting);
```

The Wi-Fi credentials shown above are placeholders. Private credentials must not be published to GitHub.

---

## Step 4: Read Sensor Data

The sensor data is retrieved using the Bosch API.

```c
rslt = bme280_get_sensor_data(
    BME280_ALL,
    &comp_data,
    &dev
);
```

On successful data acquisition, the compensated values are converted to the required engineering units.

```c
if (rslt == BME280_OK)
{
    temperature = (float)comp_data.temperature;
    humidity = (float)comp_data.humidity;
    pressure = (float)(comp_data.pressure / 100.0);
}
```

### Measurement Units

| Variable | Description | Unit |
|----------|-------------|------|
| temperature | Temperature | °C |
| humidity | Relative Humidity | %RH |
| pressure | Atmospheric Pressure | hPa |

---

## Step 5: Construct JSON Payload

The STM32 combines the three sensor measurements into a single JSON message.

### JSON Format

```json
{
  "temp": 28.45,
  "hum": 62.30,
  "press": 1008.72
}
```

These are illustrative values, not recorded hardware measurements.

### JSON Construction

```c
snprintf(
    payload,
    sizeof(payload),
    "{\"temp\":%.2f,\"hum\":%.2f,\"press\":%.2f}",
    temperature,
    humidity,
    pressure
);
```

The payload contains all three environmental measurements under a single MQTT topic.

---

## Step 6: Publish Sensor Measurements Through MQTT

The STM32 publishes the JSON payload using the custom ESP8266 MQTT API.

**MQTT Topic:**

```text
tharak/bme280/data
```

**Publishing Function:**

```c
MQTT_publishTopic(
    "tharak/bme280/data",
    payload,
    QoS0
);
```

The main program reads the BME280 measurements and publishes valid readings periodically.

### Publishing Interval

The application uses a 1000 ms delay between measurement cycles.

The actual message timing also depends on execution and network communication delays.

### Expected Operation

```text
STM32
   |
   v
BME280 Sensor Read
   |
   v
Compensated Measurements
   |
   v
JSON Payload
   |
   v
ESP8266 / Wi-Fi
   |
   v
MQTT Broker
   |
   v
Node-RED
```

---

## Step 7: MQTT Subscription

The official CAT13 document also demonstrates MQTT subscription using the custom ESP8266 library.

### Important Functions

- `MQTT_connectBroker()` - Establish MQTT client connection.
- `MQTT_publishTopic()` - Publish MQTT messages.
- `MQTT_subscribeTopic()` - Subscribe to a topic.
- `MQTTDataHandler()` - Handle incoming MQTT data.
- `MQTTTimer()` - Support MQTT timing.

The example supplied in the question paper includes interrupt-driven UART reception and MQTT message handling.

The identified sensor project implements MQTT publishing. A separate subscription application is not included in this project.

---

## Step 8: Node-RED Sensor Data Visualization

### Objective

Receive the MQTT JSON messages in Node-RED and visualize temperature, humidity, and pressure.

### Node-RED Flow

```text
MQTT In
    |
    v
JSON
    |
    v
Sensor Data Processing
    |
    +----> Temperature
    |
    +----> Humidity
    |
    +----> Pressure
```

### MQTT Configuration

| Parameter | Value |
|-----------|-------|
| Broker | broker.emqx.io |
| Port | 1883 |
| Topic | tharak/bme280/data |
| QoS | 0 |

### Procedure

1. Open the Node-RED editor.
2. Add an MQTT In node.
3. Configure the MQTT broker.
4. Subscribe to `tharak/bme280/data`.
5. Connect the MQTT In node to a JSON node.
6. Add a Debug node to verify the received payload.
7. Extract temperature, humidity, and pressure values.
8. Connect the values to suitable dashboard widgets if a dashboard is installed.
9. Deploy the flow.
10. Observe the incoming sensor measurements.

### Expected Payload

```json
{
  "temp": 28.45,
  "hum": 62.30,
  "press": 1008.72
}
```

The actual values change depending on environmental conditions.

**Node-RED Verification:** Pending.

---

## 3. Complete Application Pseudocode

1. Initialize the STM32 HAL library.
2. Configure the system clock.
3. Initialize GPIO, I2C1, and USART1.
4. Configure the Bosch BME280 API.
5. Initialize the sensor.
6. Configure sensor oversampling and power mode.
7. Initialize the ESP8266 Wi-Fi module.
8. Connect the ESP8266 to a Wi-Fi network.
9. Establish a TCP connection with the MQTT broker.
10. Configure the MQTT client parameters.
11. Connect the MQTT client to the broker.
12. Enter the infinite application loop.
13. Read temperature, humidity, and pressure.
14. Convert sensor readings into engineering units.
15. Construct a JSON payload.
16. Publish the JSON payload to the MQTT topic.
17. Repeat the measurement and publishing process.
18. Receive and visualize MQTT data using Node-RED.

---

## 4. Project Files

**Matching Original Project:**

`FIOT/i2c/fianl`

### Required Components

- `fianl.ioc` - STM32CubeMX configuration
- `Core/Src/main.c` - Main STM32 application
- `Core/Src/bme280.c` - Bosch sensor driver
- `Core/Src/ESPLib.c` - ESP8266 communication library
- `Core/Inc/bme280.h` - BME280 driver header
- `Core/Inc/bme280_defs.h` - BME280 definitions
- `Core/Inc/ESPLib.h` - ESP8266 library header
- `Drivers/` - STM32 HAL and CMSIS dependencies
- `MDK-ARM/fianl.uvprojx` - Keil project configuration
- Required startup and STM32 system files

---

## 5. Inference

The STM32F401RE microcontroller can interface with a BME280 environmental sensor through the I²C protocol to obtain compensated temperature, pressure, and humidity values.

The ESP8266 Wi-Fi module enables transmission of the measurements to an MQTT broker using the custom ESP8266 API.

The readings are combined into a JSON payload and published through a single MQTT topic.

Node-RED can subscribe to the topic and display the environmental measurements.

Actual hardware measurements and Node-RED results require verification.

---

## EXPERIMENT STATUS

- BME280 I²C interface code: Available
- Bosch sensor driver: Available
- Temperature measurement: Implemented in source
- Pressure measurement: Implemented in source
- Humidity measurement: Implemented in source
- ESP8266 Wi-Fi connection code: Available
- MQTT connection code: Available
- MQTT JSON publishing: Implemented in source
- MQTT subscription: Example in question paper; not implemented in identified project
- Node-RED dashboard: Pending verification
- Circuit diagram: To be added
- Hardware results: Pending verification
