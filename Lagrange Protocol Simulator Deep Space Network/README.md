# Lagrange Protocol Simulator: Deep Space Network

[![Platform: Vanilla JS](https://img.shields.io/badge/Platform-Vanilla%20JS-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
[![Graphics: HTML5 Canvas](https://img.shields.io/badge/Graphics-HTML5%20Canvas-E34F26?style=for-the-badge&logo=html5&logoColor=white)](https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API)
[![Style: Galactic Dark CSS](https://img.shields.io/badge/Style-Galactic%20Dark%20CSS-1572B6?style=for-the-badge&logo=css3&logoColor=white)](#)
[![Math: Lagrange Interpolation](https://img.shields.io/badge/Math-Lagrange%20Interpolation-success?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

Secure and reconstruct data packets across hostile deep-space environments. This simulation models a space communication link between an Earth Station and a Mars Rover. By encoding digital payloads onto continuous algebraic curves rather than broadcasting them as raw, fragile bitstreams, the network ensures flawless data recovery even under severe solar radiation and packet erasure conditions.

The interactive dashboard is built using zero-framework HTML5 Canvas, Vanilla CSS3, and standard JavaScript, rendering real-time physics-based packet travel, cosmic dust backgrounds, and mathematical curve interpolation.

---

## Deep Space & ECE Nomenclature Dictionary

This simulation maps its visual space-themed elements directly to standard telemetry encoding, channel models, and mathematical interpolation terminology:

| UI / Visual Element | ECE / Space Communications Term | Description |
| :--- | :--- | :--- |
| **Earth Station** | Data Encoder & Polynomial Transmitter | The source node where user text is serialized and mapped onto a carrier polynomial before broadcast. |
| **Mars Rover** | Lagrange Reconstruction Unit | The receiver/sink node responsible for capturing incoming coordinates, evaluating algebraic thresholds, and solving the polynomial. |
| **Space Channel** | Noisy Electromagnetic / Erasure Channel | The propagation medium between the transceiver nodes, subject to thermal noise, scattering, and solar radiation interference. |
| **Solar Interference Level** | Channel Packet Erasure Probability | A probability threshold ($0\%$ to $80\%$) modeling the likelihood that an individual telemetry coordinate packet is corrupted/lost in transit. |
| **Secret Message Input** | Source Payload Information Vector | The raw string payload (up to 6 characters) containing the data to be securely transmitted. |
| **Waveform Shape (a, b)** | Quadratic Carrier Coefficients | Configurable mathematical parameters that alter the shape and slope of the transmission carrier curve. |
| **Visual Dots (Orange/Red/Green)** | Coordinate Packet Telemetry Frames | Discrete coordinates representing data frames. Orange indicates active transmission, fading red denotes packets destroyed by radiation, and green indicates frames successfully registered by the receiver. |
| **Traced Curve** | Interpolated Carrier Waveform Trajectory | The continuous algebraic path reconstructed by the receiver from isolated coordinate samples. |

---

## Engineering Core & Mathematical Model

### 1. Polynomial Carrier Encoding
In standard digital communication, cosmic ray strikes can corrupt bits, rendering raw streams unreadable. This simulator uses an algebraic redundancy protocol inspired by Reed-Solomon coding:

1.  **Payload Serialization:** A text input (e.g., `"HELLO"`) is converted into a single integer payload ($S$) by summing the ASCII values of its characters:
    
    $$S = \sum_{i=1}^{L} \text{ASCII}(c_i)$$

2.  **Carrier Curve Definition:** This integer payload is embedded as the Y-intercept ($x=0$, $f(0) = S$) of a quadratic polynomial:
    
    $$f(x) = a x^2 + b x + S$$
    
    *   Where $a$ and $b$ are user-defined waveform shape parameters.

3.  **Coordinate Packet Generation:** Instead of transmitting the secret value $S$ directly, the Earth Station calculates $N = 10$ discrete coordinate points along the curve for $x \in \{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4\}$. Each point $(x_i, f(x_i))$ is wrapped in a telemetry packet frame.

### 2. Noisy Space Transmission Channel (Packet Erasure Model)
During transit through the space channel, packets are subjected to simulated solar radiation. The **Solar Interference Level** slider represents the packet erasure probability ($p$). 

For each of the $10$ generated coordinate packets, a random value is drawn. If $\text{rand}() < p$, the packet is vaporized (visualized as a dispersing red explosion) and fails to reach the destination.

### 3. Lagrange Reconstruction Mathematics
To reconstruct a polynomial of degree $k$, a receiver requires at least $k + 1$ coordinate points. Since our carrier polynomial $f(x)$ is a quadratic equation ($k = 2$), the Mars Rover must capture a minimum threshold of:

$$N_{\text{min}} = k + 1 = 3\text{ packets}$$

If fewer than 3 packets arrive, the Mars Rover registers a **Critical Connection Failure** due to insufficient coordinate constraints. 

If $\ge 3$ packets survive, the Mars Rover uses the **Lagrange Interpolation Algorithm** to reconstruct the entire continuous curve. Using a subset of three received coordinates $\{(x_0, y_0), (x_1, y_1), (x_2, y_2)\}$, the reconstructed polynomial $L(x)$ is defined as:

$$L(x) = \sum_{j=0}^{2} y_j \cdot \ell_j(x)$$

Where the Lagrange basis polynomials $\ell_j(x)$ are calculated as:

$$\ell_j(x) = \prod_{\substack{m=0 \\ m \neq j}}^{2} \frac{x - x_m}{x_j - x_m}$$

Expanding this for the three target points yields:

$$L(x) = y_0 \frac{(x - x_1)(x - x_2)}{(x_0 - x_1)(x_0 - x_2)} + y_1 \frac{(x - x_0)(x - x_2)}{(x_1 - x_0)(x_1 - x_2)} + y_2 \frac{(x - x_0)(x - x_1)}{(x_2 - x_0)(x_2 - x_1)}$$

Once the curve trajectory $L(x)$ is interpolated, the Mars Rover evaluates the polynomial at the y-axis intercept ($x = 0$):

$$\text{Payload} = L(0)$$

By calculating $L(0)$, the receiver extracts the original summed integer payload ($S$). It verifies this value, successfully reconstructing the secret message.

---

## Workspace & Browser Requirements

### Software & Environment
*   **Operating System:** Platform-agnostic (Windows, macOS, Linux, ChromeOS).
*   **Web Browser:** Any modern web browser supporting the HTML5 Canvas API and modern CSS (Google Chrome, Mozilla Firefox, Microsoft Edge, Safari, Opera).
*   **Dependencies:** None. The application is written in raw HTML, CSS, and JS. It requires no background compilers, bundlers, or servers.

---

## Step-by-Step Execution Guide

### Step 1: Payload Encoding & Grid Graphing
1.  Open [index.html](file:///C:/Users/alokm/Downloads/AI-Projects-main/AI-Projects-main/Lagrange%20Protocol%20Simulator%20Deep%20Space%20Network/index.html) in your browser.
2.  In the **Earth Station** card:
    *   Enter a message in the **Secret Message** input (e.g., `HELLO` - maximum 6 characters).
    *   Adjust the **Waveform Shape** coefficients ($a$ and $b$) to modify the steepness and shift of the parabolic trajectory.
3.  Click the **Generate Data Stream** button. The console will serialize your message to a sum, compute the coordinates, and draw the blue carrier curve with 10 orange packet coordinates.

### Step 2: Channel Path Tuning & Launch
1.  Locate the central **Space Channel** slider.
2.  Set the **Solar Interference Level** (e.g., $30\%$ packet loss). Higher values will vaporize more packets during transit.
3.  Click **Initiate Launch**. The orange packets will travel downwards through the space channel. If a packet collides with radiation, it explodes in red; surviving packets land safely at the Mars Rover.

### Step 3: Payload Decoding
1.  Check the **Mars Rover** console log:
    *   If fewer than 3 packets arrive: The log displays `CRITICAL: Need 3 to reconstruct` and the reconstruction button is deactivated. Go back to Step 1 and reduce the solar interference.
    *   If 3 or more packets arrive: The log displays `Sufficient data for Lagrange Algo`.
2.  Click **Attempt Data Reconstruction**.
3.  Watch the green line trace the Lagrange polynomial path in real-time. Once the curve is completed, the Y-intercept is evaluated, and the original message is successfully recovered.
