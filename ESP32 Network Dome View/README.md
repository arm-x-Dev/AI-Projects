# 🛰️ ESP32 3D RF Propagation Grid & Signal Localization Dashboard

[![Hardware: ESP32](https://img.shields.io/badge/Hardware-ESP32-red?style=for-the-badge&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![Firmware: C++](https://img.shields.io/badge/Firmware-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Graphics: Three.js](https://img.shields.io/badge/Graphics-Three.js-black?style=for-the-badge&logo=three.js&logoColor=white)](https://threejs.org/)
[![Protocol: WebSerial & JSON](https://img.shields.io/badge/Protocol-WebSerial%20%26%20JSON-orange?style=for-the-badge&logo=javascript&logoColor=white)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

Visualize the invisible electromagnetic oceans swirling around your room in real-time. This project couples a custom ESP32 firmware probe with a cutting-edge, zero-server browser dashboard. The ESP32 continuously sweeps local $2.4\text{ GHz}$ radio frequencies, applies a dynamic lookup matrix of Kalman filters to isolate and smooth signal fluctuations, and streams structured telemetry over USB Serial. 

The frontend—built with vanilla JavaScript, WebGL via Three.js, and the native Web Serial API—intercepts this stream, models signal propagation using the Log-Distance Path Loss model, and plots active transceivers as glowing, color-coded nodes inside an interactive 3D spherical coordinate envelope.

---

## 🧭 ECE Nomenclature Dictionary

To align the cyberpunk, high-glow visual interface with authentic Electronics and Communications Engineering (ECE) principles, the following design terminology is mapped directly to standard RF propagation and receiver concepts:

| UI / Visual Element | ECE / Engineering Term | Description |
| :--- | :--- | :--- |
| **Central Reactor Core** | ESP32 Origin Base Station Node $(0,0,0)$ | The coordinate origin representing the physical location of the ESP32 receiver acting as the RF probe. |
| **Solar Dome Structure** | Spherical EM Propagation Envelope Grid | A radial coordinate grid modeling the limits of free-space electromagnetic wave propagation around the receiver. |
| **Heatmap Node Thermal Gradients** | Filtered RSSI Signal Power Bounds | Spectral visualization of signal intensity. Yellow/white represents high Signal-to-Noise Ratio (SNR), orange indicates moderate path attenuation, and red/purple marks the noise floor threshold. |
| **Target Locking Beam** | Direct Path Alignment Vector Indicator | A visual vector line constructed via raycasting to indicate the line-of-sight (LOS) path alignment between the base station and the target transceiver. |
| **Data Intercept Tracking Box** | Telemetry Channel Diagnostics Sidebar Panel | A persistent hardware register displaying real-time MAC address mapping (SSID/BSSID), exact RSSI values, estimated path distance, and coordinates. |

---

## 🧠 Engineering Core

### 1. Dynamic Kalman Filter Matrix
Indoor environments are notoriously harsh for RF signals due to multipath propagation, fading, reflections, and shadowing. Raw RSSI (Received Signal Strength Indicator) values fluctuate erratically. To resolve this, the ESP32 microcontroller runs an inline matrix of 1D Kalman Filters.

Since the ESP32 intercepts packets from dozens of dynamic transceivers (BSSIDs) simultaneously, the firmware maintains a tracked registry of up to 30 unique devices. When a packet is intercepted:
1. The ESP32 scans its BSSID lookup registry.
2. If it is a newly discovered device, it dynamically allocates a fresh `KalmanFilter1D` class instance.
3. If the registry limit is reached, it drops the oldest inactive node to free memory.
4. The raw RSSI measurement is fed into the state transition model:

$$\text{Prediction: } P^-_{k} = P_{k-1} + Q$$

$$\text{Kalman Gain: } K_k = \frac{P^-_{k}}{P^-_{k} + R}$$

$$\text{State Update: } X_k = X_{k-1} + K_k \left( Z_k - X_{k-1} \right)$$

$$\text{Error Covariance Update: } P_k = (1 - K_k) P^-_{k}$$

*   **Process Variance ($Q$):** Set to `0.5` to account for dynamic physical movements of transceivers.
*   **Measurement Variance ($R$):** Set to `2.0` to filter high-frequency indoor scattering and multipath spikes.

This mathematical processing yields a smooth, lag-free signal stream, preventing erratic, erratic "node-jumping" on the 3D map.

### 2. RF Distance Estimation (Log-Distance Path Loss Model)
To map the transceivers onto the 3D grid, the signal power attenuation is converted into physical distance in meters. This is accomplished using a custom implementation of the Log-Distance Path Loss model:

$$\text{RSSI} = A - 10n \log_{10}(d)$$

Rearranging the formula to solve for the estimated physical distance $d$ yields:

$$d = 10^{\left( \frac{A - \text{RSSI}}{10n} \right)}$$

Where:
*   **$d$:** Estimated distance in meters from the base station receiver.
*   **$\text{RSSI}$:** The Kalman-smoothed signal power in dBm.
*   **$A$:** Calibrated reference RSSI at a distance of 1 meter. In this implementation, $A$ is calibrated to $-30\text{ dBm}$ representing close-proximity signal transmission.
*   **$n$:** The path loss exponent. Modeling a typical indoor environment with walls, clutter, and human interference, $n$ is calibrated to $2.7$.

---

## 🛠️ Hardware & Workspace Requirements

### Hardware Components
1.  **Microcontroller:** Any ESP32 development board (e.g., ESP32-WROOM-32D / 32E or ESP32-S3).
2.  **USB Cable:** High-quality, data-capable Micro-USB or USB-C cable (essential for serial data stream transmission; power-only charging cables will not work).
3.  **Host Machine:** A PC or Mac equipped with a USB port.

### Software Prerequisites
1.  **Arduino IDE 2.x:** Installed with ESP32 board support.
    *   *Board Manager URL:* `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2.  **Web Browser:** A modern browser supporting the Web Serial API (specifically Google Chrome or Microsoft Edge, version 89 or newer). Firefox and Safari are not supported due to native Web Serial API limitations.

---

## 🚀 Step-by-Step Installation & Deployment

### Step 1: Flashing the ESP32 Probe
1.  Connect your ESP32 board to your computer using the data-capable USB cable.
2.  Launch **Arduino IDE 2.x** and open the firmware file: [ESP32_Code.ino](file:///C:/Users/alokm/Downloads/AI-Projects-main/AI-Projects-main/ESP32%20Network%20Dome%20View/ESP32_Code.ino).
3.  Navigate to **Tools > Board > esp32** and select your specific board module (e.g., *ESP32 Dev Module*).
4.  Navigate to **Tools > Port** and select the active COM port assigned to the ESP32.
5.  Click the **Upload** button (right-arrow icon) to compile and flash the firmware.
6.  Once the terminal states `Done uploading`, verify the device is operating. 
7.  > [!IMPORTANT]
    > **Close the Arduino IDE Serial Monitor.** The Web Serial API in the browser requires exclusive control of the USB COM port. If the Arduino IDE Serial Monitor remains open, it will lock the port and prevent the web dashboard from connecting.

### Step 2: Running the 3D Web Dashboard
1.  Locate the HTML5 dashboard file: [radar.html](file:///C:/Users/alokm/Downloads/AI-Projects-main/AI-Projects-main/ESP32%20Network%20Dome%20View/radar.html).
2.  Open `radar.html` directly in your Chrome or Edge browser. There is no need for local servers, node modules, or npm setups. The app runs directly from your file system.
3.  Click the high-glow amber button in the upper-left corner: **Initialize Base Station Link**.
4.  A browser prompt will display a list of active serial devices. Select the COM port corresponding to your ESP32 and click **Connect**.
5.  Upon coupling, the button state updates to **BUS LINK COUPLED**. Real-time Wi-Fi signals in your room will begin populating the translucent coordinate sphere in real-time.

### Step 3: Interactive Dashboard Controls
*   **Viewport Navigation:** 
    *   *Rotate Scene:* Click and drag the left mouse button.
    *   *Pan View:* Click and drag the right mouse button.
    *   *Zoom:* Use the scroll wheel. The camera's far clipping plane is optimized at `500000` units with overridden bounding geometries (`computeBoundingSphere()`) to guarantee viewport stability during infinite zooms.
*   **Node Diagnostics:**
    *   Click on any floating network sphere to cast a yellow alignment laser from origin $(0,0,0)$ to the selected transceiver.
    *   The persistent **Telemetry Channel Diagnostics** panel on the right side will freeze and update with real-time metrics including SSID, BSSID, filtered RSSI power levels, estimated distance in meters, and $(X,Y,Z)$ spatial coordinates.
