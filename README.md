# Master AI & Technical Hobby Lab

Welcome to my centralized digital sandbox—a dedicated hub for independent engineering experiments, mathematical simulations, hardware-to-software pipelines, and interactive 3D WebGL dashboards.

This repository serves as a playground for writing raw, zero-framework logic, practicing ECE signal modeling, and tracking complex computer science implementations in clean, isolated modules.

---

## The Global Tech Stack

[![Language: JavaScript](https://img.shields.io/badge/Language-JavaScript-yellow?style=for-the-badge&logo=javascript&logoColor=black)](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
[![Firmware: C++](https://img.shields.io/badge/Firmware-C%2B%2B-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Graphics: Three.js](https://img.shields.io/badge/Graphics-Three.js-black?style=for-the-badge&logo=three.js&logoColor=white)](https://threejs.org/)
[![Graphics: HTML5 Canvas](https://img.shields.io/badge/Graphics-HTML5%20Canvas-orange?style=for-the-badge&logo=html5&logoColor=white)](https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API)
[![API: Web Serial](https://img.shields.io/badge/API-Web%20Serial-orange?style=for-the-badge&logo=google-chrome&logoColor=white)](#)
[![Lab Status: Active](https://img.shields.io/badge/Lab%20Status-Active%20%26%20Calibrated-brightgreen?style=for-the-badge)](#)

---

## Active Laboratory Modules

| Experiment Module | Description | Primary Tech Stack | Workspace Link |
| :--- | :--- | :--- | :--- |
| **Lagrange Simulator** | A Deep Space Network telemetry simulation utilizing algebraic Lagrange Interpolation curves to reconstruct lost data packets vaporized by solar radiation in a noisy channel. | HTML5 Canvas, JavaScript, CSS3 | [Open Module](./Lagrange%20Protocol%20Simulator%20Deep%20Space%20Network/) |
| **ESP32 Network Dome** | An environmental RF probe converting an ESP32 into a wireless scanner that streams Kalman-smoothed RSSI telemetry into a high-glow 3D Three.js WebGL dome via Web Serial. | ESP32 (C++), Web Serial, Three.js | [Open Module](./ESP32%20Network%20Dome%20View/) |

---

## Monorepo Architecture & Principles

Every module inside this laboratory is designed with clean architectural separation in mind:

*   **Isolated Sandboxing:** Each folder contains its own self-sufficient logic, graphics handlers, and styling. No overlapping database dependencies or global build scripts are required.
*   **Mathematical & ECE Core:** Focuses on implementing core mathematical concepts from scratch (such as 1D Kalman Filters for noise reduction and the Log-Distance Path Loss model for RF distance approximations).
*   **Zero-Server Execution:** All frontend interfaces are written in vanilla HTML5, CSS3, and client-side JavaScript, allowing them to run directly from local storage (`file:///` path) in any modern web browser.

---

## Getting Started Locally

To step inside the lab and run these simulations locally:

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/your-username/master-ai-hobby-lab.git
    cd master-ai-hobby-lab
    ```

2.  **Run the Lagrange Simulator:**
    *   Navigate into `Lagrange Protocol Simulator Deep Space Network`.
    *   Open `index.html` in any browser.

3.  **Run the ESP32 Network Dome:**
    *   Flash the `ESP32_Code.ino` firmware inside the `ESP32 Network Dome View` folder onto your ESP32 board using Arduino IDE 2.x.
    *   Ensure the Arduino Serial Monitor is closed to avoid serial port conflict.
    *   Open `radar.html` in Google Chrome or Microsoft Edge, click **Initialize Base Station Link**, and select your ESP32's COM port.
