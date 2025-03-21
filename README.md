# EcoBin - Smart Waste Management System

Welcome to EcoBin, a smart waste bin that automates waste disposal and monitoring using ultrasonic sensors, a servo motor, and alert systems. This project promotes hygiene and efficiency in waste management.

## Features

### 1. Automated Bin Opening

- **Motion Detection**: The bin automatically opens when an object (waste) is detected within 30 cm.
- **Servo Motor Control**: A servo motor opens and closes the bin lid.

### 2. Bin Level Monitoring

- **Ultrasonic Sensors**: Measures the fill level inside the bin.
- **Full Bin Indicator**: Alerts when the bin is full using LEDs and a buzzer.

### 3. Alert System

- **Buzzer Alarm**: Triggers an alarm when the bin reaches its maximum capacity.
- **Buzzer Alarm**: Displays the bin status:
  - Green LED - Power ON Indicator
  - Blue LED - Available Space Indicator
  - Red LED - Full Bin Alert

> The components used for this project are listed [**here**](./components.md): `components.md`

## Code Structure

The project consists of a single Arduino script handling bin automation and monitoring:

- Main Code: `ecobin.ino`
- Functions:
  - `checkDistance()` - Measures distance using ultrasonic sensors.
  - `setup()` - Initializes pins and components.
  - `loop()` - Handles the logic for bin opening, level detection, and alerts

## How to Use

1. Clone the repository:

```sh
git clone https://github.com/emmanueldev247/starfield-ecobin.git
```

2. Connect the components as per the provided [**Circuit Diagram**](./ecobin-circuit-diagram.jpg).
3. Ensure necessary libraries (e.g., Servo) are installed.
4. Upload the code to your Arduino board using the Arduino IDE.
5. Power ON the system, and the bin will operate automatically.

## Contributing

We welcome contributions to improve EcoBin. Feel free to open issues, suggest new features, or create pull requests.

> Enjoy building a cleaner and smarter waste management system with EcoBin!

## Authors

<details>
    <summary>Emmanuel Ademola</summary>
    <ul>
    <li><a href="https://www.github.com/emmanueldev247">Github</a></li>
    <li><a href="https://www.twitter.com/emmanueldev247">Twitter</a></li>
    <li><a href="mailto:mailemmydee@gmail.com">E-mail</a></li>
    <li><a href="https://emmanueldev247.publicvm.com">Portfolio</a></li>
    </ul>
</details>
