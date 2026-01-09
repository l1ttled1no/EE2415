# EE2415 Project - People Counting System with Environmental Monitoring

A real-time embedded system that counts people entering a room using ultrasonic sensors while monitoring environmental conditions. Built using FreeRTOS on ESP32-S3 microcontroller with multiple sensor inputs and visual/audio feedback.

## Project Overview

This system detects and counts people entering a defined area using an ultrasonic distance sensor. It simultaneously monitors temperature and humidity levels, displays real-time information on an LCD screen, and provides visual (LED) and audio (buzzer) alerts based on occupancy levels.

## Hardware Components

### Microcontroller
- **Board**: Ohstem Yolo Uno ESP32-S3-N16R8
- **Platform**: ESP32-S3 with 16MB Flash, 8MB RAM
- **Framework**: Arduino

### Sensors
- **DHT20**: Digital I2C temperature and humidity sensor
  - I2C Address: 0x38 (default)
  - Provides temperature in Celsius and relative humidity percentage
  
- **HC-SR04**: Ultrasonic distance sensor
  - Detection range: 2-100 cm
  - Used for people detection
  - Trigger Pin: GPIO 6 (D3)
  - Echo Pin: GPIO 7 (D4)

### Output Devices
- **LCD Display**: 16x2 I2C LCD
  - I2C Address: 0x21
  - Displays people count, temperature, and humidity
  
- **NeoPixel LED**: RGB LED Strip (4 LEDs)
  - Pin: GPIO 8 (D5)
  - Color-coded alerts based on occupancy level
  
- **Buzzer**: Active buzzer
  - Pin: GPIO 9 (D6)
  - Audio alerts when person is detected

### Power
- External Power Supply: 5-12V Power Adapter

## Pin Configuration

| Component | Pin Number | GPIO | Description |
|-----------|-----------|------|-------------|
| DHT20 SDA | - | GPIO 11 | I2C Data Line |
| DHT20 SCL | - | GPIO 12 | I2C Clock Line |
| LCD SDA | - | GPIO 11 | I2C Data Line (shared) |
| LCD SCL | - | GPIO 12 | I2C Clock Line (shared) |
| Ultrasonic Trigger | D3 | GPIO 6 | Trigger pulse output |
| Ultrasonic Echo | D4 | GPIO 7 | Echo pulse input |
| NeoPixel Data | D5 | GPIO 8 | LED data signal |
| Buzzer | D6 | GPIO 9 | Buzzer control |

## System Architecture

The system uses FreeRTOS to manage five concurrent tasks:

### Task 1: DHT20 Sensor Reading
- **Priority**: 1
- **Stack Size**: 4096 bytes
- **Function**: Continuously reads temperature and humidity data every 2 seconds
- **Output**: Updates global variables `glb_temp` and `glb_humid`

### Task 2: Ultrasonic Distance Measurement
- **Priority**: 1
- **Stack Size**: 4096 bytes
- **Function**: 
  - Measures distance every 50ms
  - Detects people in range (2-100 cm)
  - Implements tick counting (8 consecutive readings) to avoid false positives
  - Increments people count when sustained detection occurs
- **Output**: Updates `glb_motionCount` and `glb_alert` flag

### Task 3: LED Control
- **Priority**: 1
- **Stack Size**: 4096 bytes
- **Function**: Displays color-coded alerts based on occupancy:
  - Red: 1-2 people
  - Blue: 3-4 people
  - Yellow: 5-6 people
  - Green: 7-10 people
  - White: 11+ people
- **Behavior**: LEDs flash for 500ms when alert is triggered

### Task 4: LCD Display
- **Priority**: 1
- **Stack Size**: 8192 bytes
- **Function**: Updates LCD display every second with:
  - Line 1: "Ppl Count: X"
  - Line 2: "T:XX.XoC H:XX.X%"
- **Display Format**: Temperature to 1 decimal, humidity to 1 decimal

### Task 5: Buzzer Alert
- **Priority**: 1
- **Stack Size**: 2048 bytes
- **Function**: Sounds buzzer when person is detected
- **Behavior**: 5 rapid beeps (50ms on, 50ms off) when `glb_alert` is true

## Global State Variables

The system uses shared global variables for inter-task communication:

```cpp
uint8_t glb_totalCount;    // Total people count (reserved for future use)
int glb_motionCount;       // Current detected motion count
bool glb_alert;            // Alert flag for detection events
float glb_temp;            // Current temperature (Celsius)
float glb_humid;           // Current humidity (percentage)
```

## Detection Algorithm

The ultrasonic sensor implements a sophisticated detection algorithm:

1. **Distance Measurement**: Measures distance using pulse timing (speed of sound)
2. **Range Filtering**: Only considers distances between 2-100 cm
3. **Tick Counting**: Requires 8 consecutive valid readings (400ms total) before counting
4. **Debouncing**: Once counted, ignores further detections until person leaves range
5. **Alert Management**: Sets alert flag high during detection, low when clear

## Building and Flashing

### Prerequisites
- PlatformIO IDE or PlatformIO CLI
- USB cable for ESP32 connection

### Build Instructions

1. Clone or download this repository
2. Open project in PlatformIO
3. Build the project:
   ```bash
   pio run
   ```

4. Upload to board:
   ```bash
   pio run --target upload
   ```

5. Monitor serial output:
   ```bash
   pio device monitor -b 115200
   ```

### PlatformIO Configuration

The project uses a custom ESP32 platform with the following key settings:

- **Platform**: ESP32 (via custom platform repository)
- **Board**: yolo_uno
- **Framework**: Arduino
- **Monitor Speed**: 115200 baud
- **USB Mode**: CDC-ACM enabled on boot
- **Dependencies**: Adafruit NeoPixel library v1.15.2

## Project Structure

```
EE2415/
|-- include/              # Header files
|   |-- 0_glb.h          # Global variable declarations
|   |-- Task_1_DHT20.h   # DHT20 sensor task interface
|   |-- Task_2_Ultrasonic.h  # Ultrasonic sensor task interface
|   |-- Task_3_LED.h     # LED control task interface
|   |-- Task_4_LCD.h     # LCD display task interface
|   |-- Task_5_Buzzer.h  # Buzzer control task interface
|
|-- lib/                 # Custom libraries
|   |-- DHT20/          # DHT20 sensor driver
|   |   |-- DHT20.h
|   |   |-- DHT20.cpp
|   |
|   |-- LCD/            # LCD I2C driver
|       |-- LiquidCrystal_I2C.h
|       |-- LiquidCrystal_I2C.cpp
|
|-- src/                # Source files
|   |-- main.cpp        # Main program and RTOS task creation
|   |-- Task_1_DHT20.cpp     # DHT20 sensor implementation
|   |-- Task_2_Ultrasonic.cpp # Ultrasonic sensor implementation
|   |-- Task_3_LED.cpp       # LED control implementation
|   |-- Task_4_LCD.cpp       # LCD display implementation
|   |-- Task_5_Buzzer.cpp    # Buzzer control implementation
|
|-- platformio.ini      # PlatformIO configuration
|-- README.md          # This file
```

## Features

### Real-time Monitoring
- Continuous temperature and humidity monitoring (2-second intervals)
- Rapid ultrasonic distance sensing (50ms polling)
- Live LCD display updates (1-second refresh)

### Smart Detection
- Multi-reading validation to prevent false positives
- Automatic reset when person exits detection zone
- Configurable detection range and threshold

### Multi-modal Feedback
- Visual feedback through color-coded LED system
- Audio alerts with buzzer
- Informative LCD display with environmental data

### Robust Architecture
- FreeRTOS-based multitasking for reliable operation
- Independent task execution
- Shared state management with global variables

## Occupancy Level Thresholds

The system categorizes occupancy into five levels:

| People Count | LED Color | Description |
|--------------|-----------|-------------|
| 0-9 | Red | Very low |
| 10-19 | Blue | Low |
| 20-29 | Yellow | Medium |
| 30-39 | Green | High |
| 40+ | White | Very High |

## Technical Specifications

### Timing Parameters
- DHT20 Reading Interval: 2000ms
- Ultrasonic Polling: 50ms
- LCD Update Rate: 1000ms
- LED Flash Duration: 500ms
- Buzzer Alert Pattern: 5 beeps x (50ms on + 50ms off)

### Detection Parameters
- Minimum Distance: 2 cm
- Maximum Distance: 50 cm
- Required Tick Count: 8 consecutive readings
- Ultrasonic Timeout: 30ms

### I2C Addresses
- DHT20: 0x38
- LCD Display: 0x21

## Libraries Used

### External Dependencies
- **Adafruit NeoPixel** (v1.15.2): RGB LED control
- **Wire**: I2C communication (Arduino standard)

### Custom Libraries
- **DHT20** (v0.2.2): Based on Rob Tillaart's DHT20 library
- **LiquidCrystal_I2C**: Modified I2C LCD driver for 16x2 displays

## Serial Debug Output

The system provides debug information over serial connection (115200 baud):

```
[DEBUG - DHT] DHT20 Temperature: XX.X degC
[DEBUG - DHT] DHT20 Humidity: XX.X %
[DEBUG - ULTRASONIC] Distance: XXX.X cm
[DEBUG - ULTRASONIC] Person detected. Person count: X
[DEBUG - LED] NeoPixel Initialized
[DEBUG - LCD] LCD Initialized
[DEBUG - BUZZER] Buzzer Initialized
```

Note: Some debug messages are commented out in the code to reduce serial output.

## Troubleshooting

### LCD Not Displaying
- Verify I2C address is 0x21 (some displays use 0x27)
- Check I2C wiring (SDA to GPIO 11, SCL to GPIO 12)
- Ensure I2C pull-up resistors are present

### DHT20 Read Errors
- Check I2C connection and address (0x38)
- Verify sensor power supply (3.3V or 5V)
- Allow sensor warm-up time after power-on

### False People Detections
- Adjust MAX_TICK_COUNT value (currently 8)
- Check for obstacles in ultrasonic sensor path
- Ensure sensor is mounted stably

### NeoPixel Not Lighting
- Verify GPIO 8 connection
- Check power supply to LED strip (5V required)
- Confirm correct number of LEDs (currently set to 4)

## Future Enhancements

Potential improvements for the system:

1. **Data Logging**: SD card storage for historical data
2. **WiFi Connectivity**: Remote monitoring and control
3. **Entry/Exit Differentiation**: Dual sensors to track directional movement
4. **Adjustable Thresholds**: Runtime configuration via web interface
5. **Battery Backup**: UPS functionality for continuous operation
6. **PIR Sensor Integration**: Additional motion detection (hardware prepared on GPIO 10)

## License

This project is developed for educational purposes as part of the EE2415 course.

## Credits

### Libraries
- DHT20 Library by Rob Tillaart
- Adafruit NeoPixel Library
- LiquidCrystal I2C Library (modified)

### Hardware
- Ohstem Yolo Uno ESP32-S3 development board

## Contact

For questions or issues related to this project, please refer to course materials or contact the course instructor.

---

Last Updated: January 2026
Project Version: 1.0
