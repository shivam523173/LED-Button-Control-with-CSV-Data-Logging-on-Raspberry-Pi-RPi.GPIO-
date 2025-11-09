# Experiment 2 — LED & Button Control with CSV Data Logging (Raspberry Pi)

Department of Electrical & Electronics Engineering  
Date: October 30, 2025

## Objective
Interface an LED and a push button with Raspberry Pi (RPi.GPIO) and log timestamped button/LED states to a CSV file for analysis.

---

## Hardware Connections

| Function | GPIO (BCM) | Physical Pin |
|---------|-------------|--------------|
| LED Anode (via 220Ω to GPIO) | 17 | 11 |
| Button | 27 | 13 |
| Ground (GND) | — | 6 or 9 |

**Wiring**
- LED anode → **GPIO17**; LED cathode → **220Ω** → **GND**  
- Button one side → **GPIO27**; other side → **GND** (uses internal pull-up)

---

## Requirements
- Raspberry Pi OS
- Python 3
- Libraries:
  ```bash
  pip install RPi.GPIO
