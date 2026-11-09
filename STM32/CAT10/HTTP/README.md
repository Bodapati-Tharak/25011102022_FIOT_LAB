
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS LAB EVALUATION 10C

**DATE:** 12/10/2026

**NAME OF EXP:** HTTP Server - STM32–Wemos Wi-Fi Modem Using AT Commands

**HARDWARE SETUP / PLATFORM:** STM32F401RE Nucleo Development Board + Wemos D1 Mini ESP8266 + STM32CubeMX + Keil MDK + STM32 HAL Libraries + Node-RED

---

## OBJECTIVE

Develop an STM32-based HTTP sensor node that communicates with an ESP8266/Wemos module using UART AT commands.

The STM32 must configure the ESP8266 as a TCP server, receive HTTP requests through `+IPD` notifications, construct an HTTP response, and transmit the response to a web browser and Node-RED.

The supplied exercise demonstrates a static HTML response. Dynamic sensor-data transmission is not implemented in the identified project.

---

## TASK 10C: Configure ESP8266 as a TCP Server

### 1. Circuit Diagram

The STM32 communicates with the Wemos ESP8266 module using UART.

The ESP8266 provides Wi-Fi connectivity and operates as a TCP server on port 80.

**Hardware Components:**

- STM32F401RE Nucleo Development Board
- Wemos D1 Mini ESP8266
- USB Connection
- PC Serial Terminal
- Wi-Fi Access Point
- Connecting Wires

**UART Configuration:**

| STM32 Pin | Function | Connection |
|-----------|----------|------------|
| PA9 | USART1_TX | ESP8266 RX |
| PA10 | USART1_RX | ESP8266 TX |
| PA2 | USART2_TX | PC Debug/Serial Interface |
| PA3 | USART2_RX | PC Debug/Serial Interface |
| GND | Common Ground | ESP8266 GND |

**Configuration:**

- Microcontroller: STM32F401RET6
- USART1: ESP8266 Communication
- USART2: PC Debugging
- Baud Rate: 115200
- System Clock: 84 MHz
- Communication Protocol: UART
- Server Port: 80

The UART signals use 3.3V logic. The Wemos module must be powered through an appropriate power input.

**Circuit Diagram:** To be added.

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Configure the ESP8266 Wi-Fi modem to operate as a TCP server using AT commands transmitted from the STM32.

**Required AT Commands:**

```text
AT

AT+CIPMUX=1

AT+CIPSERVER=1,80
```

**Command Descriptions:**

| Command | Purpose |
|---------|---------|
| `AT` | Verify modem communication |
| `AT+CIPMUX=1` | Enable multiple TCP connections |
| `AT+CIPSERVER=1,80` | Start TCP server on port 80 |

### Working Principle

The STM32 initializes UART communication with the ESP8266.

After the modem connects to a Wi-Fi network, the STM32 configures the ESP8266 for multiple TCP connections.

The ESP8266 then starts listening for incoming TCP connections on port 80.

A browser connected to the same accessible network can send an HTTP request to the ESP8266 IP address.

### Pseudocode

1. Initialize the STM32 HAL library.
2. Configure the system clock.
3. Initialize USART1 and USART2.
4. Initialize the ESP8266 module.
5. Connect the ESP8266 to the Wi-Fi network.
6. Send `AT` to verify communication.
7. Send `AT+CIPMUX=1`.
8. Check the modem response.
9. Send `AT+CIPSERVER=1,80`.
10. Verify that the TCP server has started.
11. Wait for incoming network connections.

### Code Base

The available `FIOT/WEMOS/HTTP` project contains the required TCP server configuration.

The application uses STM32 HAL UART functions and the ESP8266 library.

**Important Functions:**

- `HAL_UART_Transmit()`
- `HAL_UART_Receive()`
- `HAL_UARTEx_ReceiveToIdle()`
- `ESP8266_Init()`
- `ESP8266_wifiConnect()`

**Implementation Status:** TCP server initialization code is available. Hardware operation requires verification.

### 3. Inference

The ESP8266 AT-command interface allows the STM32 to configure the Wi-Fi module as a TCP server.

The expected result is a TCP server listening for HTTP connections on port 80.

Actual server operation is pending verification.

---

## TASK 10d: Observe the HTTP Request

### 1. Circuit Diagram

The same STM32–ESP8266 UART circuit is used.

The ESP8266 receives HTTP requests from a connected web browser and forwards the received network data to the STM32 through UART.

**Circuit Diagram:** To be added.

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Observe the HTTP request received by the ESP8266 and construct a static HTTP response that can be displayed in a web browser.

### Working Principle

When a browser accesses the ESP8266 IP address, it sends an HTTP GET request.

The ESP8266 forwards the incoming request to the STM32 using a `+IPD` notification.

**Example Request:**

```text
+IPD,0,XXX:GET / HTTP/1.1
Host: 192.168.1.105
```

**Explanation:**

- `+IPD` indicates incoming network data.
- `0` represents an example TCP connection ID.
- `XXX` represents the received data length.
- `GET / HTTP/1.1` represents the HTTP request.

The STM32 must identify the connection and construct the required HTTP response.

---

### 3. Construct a Static HTTP Response

The HTTP response contains:

1. Status line
2. HTTP headers
3. Blank line
4. HTML body

**Expected HTTP Response:**

```http
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 52

<html><body><h1>STM32 IoT Node</h1></body></html>
```

The displayed `Content-Length` must equal the actual HTML body length in bytes.

**HTTP Response Components:**

| Component | Purpose |
|-----------|---------|
| `HTTP/1.1 200 OK` | Indicates successful request processing |
| `Content-Type: text/html` | Identifies HTML content |
| `Content-Length` | Specifies HTML body length |
| Blank line | Separates headers and body |
| HTML body | Contains the displayed webpage |

**Expected Browser Display:**

# STM32 IoT Node

---

### 4. Send HTTP Response Using AT+CIPSEND

The HTTP response is transmitted through the ESP8266 TCP connection.

The operation is divided into two steps.

**Step 1: Send the CIPSEND Command**

```c
sprintf(cmd, "AT+CIPSEND=%d,%d\r\n",
        link_id, data_length);
```

`link_id` represents the active TCP connection.

`data_length` represents the total number of HTTP response bytes to be transmitted, including headers and body.

The ESP8266 responds with the transmission prompt:

```text
>
```

**Step 2: Transmit HTTP Response**

Construct the response:

```c
sprintf(response,
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "<html><body><h1>STM32 IoT Node</h1></body></html>",
    body_length);
```

The STM32 transmits the response through UART after receiving the `>` prompt.

### Pseudocode

1. Initialize the STM32 and ESP8266.
2. Configure the ESP8266 as a TCP server.
3. Wait for an incoming HTTP request.
4. Receive UART data from the ESP8266.
5. Identify the `+IPD` notification.
6. Obtain the TCP connection ID.
7. Identify the received HTTP request.
8. Construct the static HTML response.
9. Calculate the HTML body length.
10. Construct the complete HTTP response.
11. Calculate the complete response length.
12. Send the `AT+CIPSEND` command.
13. Wait for the `>` prompt.
14. Transmit the HTTP response.
15. Verify the ESP8266 transmission result.
16. Close the connection when appropriate.
17. Continue listening for new requests.

### Code Base

The available `FIOT/WEMOS/HTTP` source code implements the basic HTTP server response flow.

**Features Present:**

- UART Reception
- Detection of `+IPD` Data
- Static HTML Response Construction
- `AT+CIPSEND` Command Generation
- Transmission of HTTP Response
- TCP Connection Closing

**Current Limitations:**

- HTTP request parsing requires further verification.
- Handling of partial UART frames is not fully robust.
- Response and transmission status checks require validation.
- Actual browser communication has not been verified from the repository files.

### 5. Inference

HTTP communication allows a browser to request data from the ESP8266 TCP server.

The STM32 can process the incoming request and prepare an HTTP response.

The expected result is a webpage displaying the message "STM32 IoT Node".

Browser testing is pending.

---

## TASK 10E: Node-RED as a Second HTTP Client of STM32/ESP8266 HTTP Server

### 1. Circuit Diagram

Node-RED communicates with the ESP8266 HTTP server through a network connection.

The STM32 continues to communicate with the ESP8266 using UART.

**Circuit Diagram:** To be added.

### 2. Core Logic / Pseudocode / Code Base

**Problem Statement:**

Configure Node-RED as a second HTTP client that sends requests to the ESP8266 HTTP server and displays the received response.

### Node-RED Flow

```text
+--------+     +--------------+     +-------+
| Inject | --> | HTTP Request | --> | Debug |
+--------+     +--------------+     +-------+
```

**Node Descriptions:**

| Node | Purpose |
|------|---------|
| Inject | Triggers the HTTP request |
| HTTP Request | Sends a GET request to ESP8266 |
| Debug | Displays the received HTTP response |

### HTTP Request Configuration

**Method:** GET

**URL:**

```text
http://<ESP8266_IP>/
```

Replace `<ESP8266_IP>` with the IP address assigned to the Wemos ESP8266.

The Node-RED system must have network access to the ESP8266.

### Working Principle

The Inject node triggers an HTTP request.

The HTTP Request node communicates with the ESP8266 TCP server.

The ESP8266 forwards the HTTP request to the STM32 using UART.

The STM32 constructs the HTTP response.

The ESP8266 transmits the response back to Node-RED.

The Debug node displays the received message.

### Pseudocode

1. Start the STM32/ESP8266 HTTP server.
2. Verify the ESP8266 IP address.
3. Open the Node-RED editor.
4. Add an Inject node.
5. Add an HTTP Request node.
6. Add a Debug node.
7. Connect the nodes in sequence.
8. Configure the HTTP Request node with the ESP8266 IP address.
9. Select the GET request method.
10. Deploy the flow.
11. Trigger the Inject node.
12. Observe the response in the Debug panel.

### Expected Response

```html
<html>
<body>
<h1>STM32 IoT Node</h1>
</body>
</html>
```

### Code Base

The HTTP server firmware is provided by the STM32 project.

Node-RED is configured using:

- Inject Node
- HTTP Request Node
- Debug Node

**Node-RED Flow Status:** Configuration and actual response verification pending.

### 3. Inference

Node-RED can act as a second HTTP client for the STM32/ESP8266 HTTP server.

The expected result is successful reception of the STM32-generated HTML response in the Node-RED Debug panel.

Actual Node-RED testing is pending.

---

## PROJECT FILES

**Matching Original Project:**

`FIOT/WEMOS/HTTP`

**Hardware:**

- STM32F401RE Nucleo Board
- Wemos D1 Mini ESP8266
- UART Communication
- Wi-Fi Network

**Required Project Components:**

- `HTTP.ioc` - STM32CubeMX Configuration
- `Core/Src` - Application Source Code
- `Core/Inc` - Application Headers
- `ESPLib.c` and `ESPLib.h` - ESP8266 Library
- `Drivers` - STM32F4 HAL and CMSIS Dependencies
- `MDK-ARM` - Keil Project Configuration
- Startup Assembly File
- Circuit Diagram

**Pending:**

- Removal of private Wi-Fi credentials before publication
- Circuit Diagram
- HTTP Browser Test Results
- Node-RED Flow Verification
- Hardware Verification

---

## EXPERIMENT STATUS

**TASK 10C:** TCP server configuration implemented in source; hardware verification pending.

**TASK 10d:** Basic HTTP request handling and response transmission implemented; reliability and browser results pending.

**TASK 10E:** Node-RED client flow specified; configuration and actual testing pending.

---

## FINAL INFERENCE

This experiment demonstrates how an STM32 microcontroller can use an ESP8266 Wi-Fi modem to implement a basic HTTP server through UART AT commands.

The application configures TCP communication, receives HTTP requests through `+IPD` notifications, constructs a static HTML response and sends that response using `AT+CIPSEND`.

Node-RED provides a second HTTP client for accessing the server.

The final experimental observations will be documented after hardware and network verification.

