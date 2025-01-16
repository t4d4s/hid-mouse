# ESP32 and Arduino Leonardo R3 USB Host Shield Integration

This repository contains code for integrating an ESP32 and Arduino Leonardo R3 with a USB Host Shield. The ESP32 acts as a server that listens for HTTP POST requests to trigger a signal, while the Arduino Leonardo interprets the signal and controls mouse movements or button clicks.

---

## Features

### ESP32 Server
- Connects to a Wi-Fi network and starts a web server.
- Listens for HTTP POST requests to activate a signal pin for a specified duration.
- Sends a response back to the client with the signal status.

### Arduino Leonardo R3
- Interprets signals from the ESP32 to simulate mouse clicks.
- Reads input from a USB mouse connected to the USB Host Shield and replicates its movements and button actions.
- Supports left, right, and middle mouse buttons.

---

## Requirements

### Hardware
1. **ESP32 Development Board**
2. **Arduino Leonardo R3**
3. **USB Host Shield**
4. **Wi-Fi Network**

### Software
1. Arduino IDE with required libraries:
   - `Mouse.h`
   - `USBHIDBootMouse` (for USB Host Shield functionality)

---

## Setup Instructions

### ESP32 Setup
1. Connect the ESP32 to your computer and upload the `ESP32` code.
2. Replace the placeholders in the code:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. Open the Serial Monitor to get the ESP32's IP address after uploading the code.

### Arduino Leonardo R3 Setup
1. Install the required libraries for USB Host Shield support:
   - `USBHIDBootMouse`
2. Connect the USB Host Shield to the Arduino Leonardo.
3. Upload the `Leonardo R3` code to the board.

---

## How to Use

### 1. Power and Connect the Boards
- Power both the ESP32 and Arduino Leonardo.
- Ensure the USB mouse is connected to the USB Host Shield on the Leonardo.

### 2. Trigger Mouse Actions
- Use an HTTP client (e.g., Postman or a browser extension) to send a POST request to the ESP32 server's IP address.
  ```
  POST http://<ESP32_IP_ADDRESS>/
  ```
  This triggers the `signalPin` on the ESP32, activating a mouse click on the Arduino Leonardo.

### 3. Mouse Movement and Button Presses
- Move the connected USB mouse to observe movement replication.
- Click buttons on the USB mouse to see corresponding actions on the system the Arduino Leonardo is connected to.

---

## Example HTTP Request
```bash
curl -X POST http://<ESP32_IP_ADDRESS>/
```

---

## Troubleshooting

### ESP32
1. Ensure the correct Wi-Fi credentials are entered.
2. Check the Serial Monitor for IP address and connection status.

### Arduino Leonardo
1. Ensure the USB Host Shield is securely connected.
2. Verify that the USB mouse is recognized by the system.

---

## Customization
- Adjust the signal duration by modifying the `signalDuration` variable in the ESP32 code.
- Change the pin configurations for `signalPin` if using different hardware setups.

---

## License
This project is open-source under the MIT License. Feel free to modify and use it for personal or commercial purposes.

---

## Contributions
Contributions are welcome! Please open an issue or submit a pull request with your enhancements.

---

## Author
This project was created to demonstrate the integration of ESP32 and Arduino Leonardo with USB Host Shield for mouse control functionality.
