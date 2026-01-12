# data-acquisition-system:

## Project Description
This project demonstrates a **Data Acquisition System (DAS)** developed using the **8051 microcontroller**. The system reads data from various sensors (like temperature, light, gas, etc.) and displays the real-time readings on an **LCD**. It can also transmit the data to a PC using **UART (serial communication)** for further monitoring or logging.

## Features
- Reads analog/digital sensor values
- Displays real-time data on a 16x2 LCD
- Sends sensor data to PC via serial (UART)
- Efficient and modular embedded C code
- Simulated using Proteus / Tested on real 8051 hardware

## Tools & Technologies Used
- **Microcontroller**: AT89S52 / 8051 family
- **Programming Language**: Embedded C
- **IDE**: Keil uVision
- **Flashing Tool**: Flash Magic
- **Simulation**: Proteus Design Suite (optional)
- **Communication**: UART (Serial RS232)

##data-acquisition-system
├── main.c                  # Main source code
├── lcd.c / lcd.h           # LCD display driver
├── uart.c / uart.h         # UART serial communication
├── sensors.c / sensors.h   # Sensor reading logic
├── project_files/          # Keil project files
├── documentation/          # Circuit diagrams and flowcharts
└── README.md               # Project description
