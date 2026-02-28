# HyperTronics – Workplace Safety Device
<img src="Images/Final_Product.png" width="250"/>

**EN1190: Engineering Design Project**  
Faculty of Engineering, [University of Moratuwa](https://www.mrt.ac.lk)

---

## Overview

HyperTronics is a **wearable workplace safety device** designed to improve worker safety in mining environments in Sri Lanka. The device detects:

- Worker falls  
- Hazardous gas exposure  
- Sends real-time SMS alerts with GPS location  

This solution is lightweight, battery-powered, and portable, specifically designed for mining sites in Sri Lanka with limited internet connectivity.

---

## Problem Statement

Mining remains one of the most hazardous industries in Sri Lanka. Workers are exposed to:

- Falls  
- Toxic gas accumulation  
- Limited communication  
- Delayed emergency response  

Existing solutions are often expensive, non-portable, or dependent on internet connectivity.

---

## Solution

Our wearable device:

- Monitors worker motion and gas levels in real-time  
- Detects falls and hazardous gas exposure  
- Sends instant SMS alerts with GPS location to safety officers  
- Includes a manual tactile switch to cancel false alerts  

This ensures **immediate detection** and **rapid emergency response**.

---

## System Architecture

### Core Components

| Component | Function |
|-----------|---------|
| STM32F411 Microcontroller | Processes sensor data, controls alerts and GPS/GPRS module |
| MPU-6050 Accelerometer | Detects sudden falls |
| MQ-5 Gas Sensor | Detects hazardous gases such as methane, LPG, and butane |
| GPS/GPRS Module | Sends SMS alerts with live location |
| 3.7V 1600mAh LiPo Battery | Power supply with TP4056 charging module |
| TPS61022 Boost Converter | Stable power regulation |
| Buzzer & LED Indicators | Immediate local alert signaling |

### How It Works

1. Sensors continuously monitor motion and gas levels  
2. STM32 processes signals using threshold algorithms  
3. If a fall or hazard is detected:
   - Buzzer & LED activate locally  
   - SMS alert sent with GPS location  
4. User can cancel false alerts with the tactile switch


<img src="Images/System_Algorithm_Flowchart.png" width="500"/>
---

## Technical Specifications

- **Device Type:** Wearable Safety Device  
- **Key Functions:** Fall detection, Gas detection, GPS-based SMS alerts  
- **Communication:** GPRS/GSM (no internet required)  
- **Battery Life:** Up to 24 hours  
- **Dimensions:** 45 × 78.24 × 40.89 mm  
- **Enclosure Material:** 3D printed PETG  
- **Power Consumption:** ~247 mW average  

---

## Product Cost

- **Component cost:** Rs. 7,709.34  
- **Overhead (15%):** Rs. 1,156.40  
- **Profit Margin (20%):** Rs. 1,773.15  
- **Final Selling Price:** Rs. 10,640/unit  

---

## Future Improvements

- Integration of an Oxygen (O₂) sensor  
- Improved gas calibration algorithms  
- Extended battery optimization  
- IoT dashboard integration for remote monitoring  

---

## Team Members

| Name | Role |
|------|------|
| Bandara W.D.A.C. | Enclosure Design |
| Upekshani T.S. | Enclosure Design |
| Wijesekara W.A.G.S. | PCB Layout & Design |
| Wijesinghe U.G.S.K.D. | Prototyping & STM32 Programming |

---

## Market Strategy

- Pilot deployment in small and medium-scale mining sites  
- Direct collaboration with mining officers  
- Target: Sri Lankan mining & construction sectors  
- Planned product website with demo, pricing, and contact info  

---

<img src="Images/Final_Product.jpg" width="200"/>

---

## Conclusion

HyperTronics provides an **affordable, portable, and reliable safety solution** for mining environments. By combining fall detection, gas sensing, and real-time SMS alerts, it reduces emergency response times and enhances worker protection.
