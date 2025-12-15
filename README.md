# Smart Temperature Fan System

An Arduino-based intelligent temperature control system that automatically adjusts fan speed and displays visual feedback based on ambient temperature readings. 

## VIDEO DEMO:
https://github.com/user-attachments/assets/b6224273-e975-4782-9d4b-5068137daa13

## Features

### 🌡️ Temperature Monitoring
- Real-time temperature sensing using TMP36 analog temperature sensor
- Continuous monitoring with 200ms update interval
- Accurate temperature readings in Celsius

### 🌀 Adaptive Fan Control
- **OFF**: Fan disabled when temperature < 15°C
- **LOW**: 20% PWM speed when temperature 15-25°C
- **MEDIUM**: 30% PWM speed when temperature 25-50°C
- **HIGH**: 40% PWM speed when temperature ≥ 50°C

### 📺 LCD Display
- Real-time temperature display (rounded to nearest degree)
- Current fan status (OFF/LOW/MED/HIGH)
- 16x2 character LCD with clear status updates

## Hardware Components

### Required Components
- **Arduino UNO** (or compatible)
- **TMP36 Temperature Sensor** (analog temperature sensor)
- **16x2 LCD Display** (with I2C adapter or direct connection)
- **RGB LED** (common cathode or anode)
- **DC Fan** (9V compatible, with appropriate driver if needed)
- **L293D Motor Driver IC** (for fan control, if required)
- **10kΩ Potentiometer** (for LCD contrast adjustment)
- **Resistors** (220Ω for LEDs, appropriate values for fan circuit)
- **Breadboard** (for prototyping)
- **Jumper Wires** (various colors)
- **9V Battery** (or USB power supply)
- **USB Cable** (for Arduino programming and power)

### Pin Connections

| Component | Arduino Pin | Description |
|-----------|-------------|-------------|
| TMP36 Sensor | A5 | Analog temperature input |
| LCD RS | 12 | Register select |
| LCD E | 11 | Enable pin |
| LCD D4 | 5 | Data bit 4 |
| LCD D5 | 4 | Data bit 5 |
| LCD D6 | 3 | Data bit 6 |
| LCD D7 | 2 | Data bit 7 |
| RGB Red | 9 | Red LED control |
| RGB Green | 8 | Green LED control |
| RGB Blue | 7 | Blue LED control |
| Fan | 10 | PWM fan control |

**Power Connections:**
- LCD VCC → 5V
- LCD GND → GND
- TMP36 VCC → 5V
- TMP36 GND → GND
- RGB LED → Through 220Ω resistors to pins 7, 8, 9
- Fan → Through L293D motor driver (if needed) or directly to pin 10

## Circuit Diagram

The project uses a breadboard-based circuit with the following layout:
- Arduino UNO connected via USB for power and programming
- TMP36 sensor on the left side of breadboard
- L293D motor driver IC bridging the breadboard center gap
- LCD display on the right side
- RGB LED with current-limiting resistors
- Potentiometer for LCD contrast adjustment
- 9V battery for DC Fan

## Software Requirements

- **Arduino IDE** (version 1.8.0 or later)
- **LiquidCrystal Library** (included with Arduino IDE)

## Installation & Setup

### 1. Install Arduino IDE
1. Download Arduino IDE
2. Install the IDE on your computer
3. Connect your Arduino UNO via USB cable

### 2. Install Required Library
The `LiquidCrystal` library comes pre-installed with Arduino IDE. If needed:
- Go to **Sketch → Include Library → LiquidCrystal**

### 3. Upload the Code
1. Open the `smart_fan_system.ino` file in Arduino IDE
2. Select your board: **Tools → Board → Arduino Uno**
3. Select your port: **Tools → Port → [Your COM Port]**
4. Click the **Upload** button (→) or press `Ctrl+U`

### 4. Circuit Assembly
1. Place components on breadboard according to pin connections
2. Connect TMP36 sensor to analog pin A5
3. Wire LCD display to digital pins 2, 3, 4, 5, 11, 12
4. Connect RGB LED to pins 7, 8, 9 (with 220Ω resistors)
5. Connect fan to pin 10 (through L293D if needed)
6. Connect all GND pins to common ground
7. Connect all VCC pins to 5V
8. Adjust LCD contrast using potentiometer

### 5. Power On
- Connect Arduino via USB or use external 9V power supply
- System will initialize and display "Initializing..." for 2 seconds
- Temperature monitoring and fan control will begin automatically

## Usage

### Operation
Once powered on, the system operates automatically:

1. **Initialization**: LCD displays "Initializing..." for 2 seconds
2. **Continuous Monitoring**: System reads temperature every 200ms
3. **Automatic Control**: Fan speed adjusts based on temperature thresholds
4. **Visual Feedback**: RGB LED changes color to indicate temperature status
5. **Display Update**: LCD shows current temperature and fan status

### Temperature Thresholds

| Temperature Range | Fan Speed | LED Color | Status |
|-------------------|-----------|-----------|--------|
| < 15°C | OFF (0%) | Green | Cool |
| 15-25°C | LOW (20%) | Yellow | Normal |
| 25-50°C | MEDIUM (30%) | Red | Warm |
| ≥ 50°C | HIGH (40%) | Purple | Hot |

## Code Structure

### Key Functions

- `setColor(bool r, bool g, bool b)`: Controls RGB LED color based on temperature status
- `setup()`: Initializes pins, LCD, and displays startup message
- `loop()`: Main control loop that:
  - Reads temperature from TMP36 sensor
  - Converts analog reading to Celsius
  - Adjusts fan speed based on temperature
  - Updates RGB LED color
  - Displays temperature and fan status on LCD

### Temperature Calculation
```cpp
temperature = (reading * (5.0/1024.0) - 0.5) * 100.0;
```
This formula converts the analog reading (0-1023) to voltage (0-5V) and then to temperature in Celsius using the TMP36's linear relationship (10mV/°C with 500mV offset).

## Troubleshooting

### Common Issues

**LCD not displaying:**
- Check all pin connections
- Adjust potentiometer for contrast
- Verify 5V and GND connections

**Temperature readings incorrect:**
- Verify TMP36 is connected to A5
- Check sensor orientation (flat side should face you)
- Ensure sensor is not touching other components

**Fan not working:**
- Check PWM pin 10 connection
- Verify fan power requirements (may need external power)
- Test fan directly with 5V to ensure it works
- If using L293D, verify motor driver connections

**RGB LED not changing colors:**
- Verify pin connections (7, 8, 9)
- Check resistor values (220Ω recommended)
- Ensure common cathode/anode matches your LED type

**Arduino not uploading:**
- Check USB cable connection
- Verify correct COM port selected
- Try resetting Arduino during upload

## Customization

### Adjusting Temperature Thresholds
Modify the temperature values in the `loop()` function:
```cpp
if (temperature < 15) {        // Change 15 to your desired threshold
    // Fan OFF logic
}
else if (temperature < 25) {    // Change 25 to your desired threshold
    // Fan LOW logic
}
// ... and so on
```

### Changing Fan Speeds
Modify PWM values in `analogWrite()` calls:
```cpp
analogWrite(fanPin, 20);  // Change 20 (0-255) to adjust speed
```

### Adding More Status Levels
Add additional `else if` conditions in the `loop()` function to create more granular control.

### Changing Update Rate
Modify the `delay(200)` value at the end of `loop()` to change how often readings are taken (lower = more frequent, higher = less frequent).

## Author

Created as an educational and practical temperature control system.

## Acknowledgments

- Arduino community for excellent documentation
- TMP36 sensor datasheet for temperature conversion formulas
- LiquidCrystal library developers

---

**Note**: Always double-check your circuit connections before powering on. Do NOT adjust wiring and connections while the power is on.
