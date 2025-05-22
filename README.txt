
Ultrasonic Distance Alert System Documentation 🚗🔊💡

Overview  
Hey! I built this Ultrasonic Distance Alert System that mimics a car parking sensor. It uses an ultrasonic sensor to measure distance, lights up LEDs via a shift register to visually show how close an object is, and sounds a buzzer with varying beep rates to alert me. Plus, I added a mute button to silence the buzzer when needed. I also included a serial bar indicator so I can see the distance feedback on my computer monitor. Cool, right? 😎

---

Components Used 🧰

| Component            | Quantity | Purpose                                       |
|----------------------|----------|-----------------------------------------------|
| Arduino Uno (or similar) | 1        | Main microcontroller to run the system       |
| Ultrasonic Sensor (HC-SR04) | 1        | Measures distance by sending and receiving sound waves |
| 74HC595 Shift Register | 1        | Controls 8 LEDs with just 3 Arduino pins      |
| LEDs:                 | 8        | Visual distance indicator lights              |
| - Red LEDs            | 2        | Closest warning zone                           |
| - Yellow LEDs         | 2        | Second zone                                   |
| - Blue LEDs           | 2        | Third zone                                    |
| - White LEDs          | 2        | Farthest zone                                 |
| Buzzer                | 1        | Audio alert with beep patterns                 |
| Pushbutton (mute)     | 1        | Toggles buzzer sound on/off                     |
| 10kΩ Resistor         | 1        | Pull-down resistor for the mute button          |
| Jumper wires          | Several  | For all connections                            |
| Breadboard            | 1        | For easy circuit assembly                       |
| Power supply (USB from PC or 5V adapter) | 1 | Powers the Arduino and components             |

---

How It Works ⚙️

1. Ultrasonic Sensor:  
   The sensor sends a high-frequency sound pulse (triggered via trigPin) and listens for the echo reflected by an obstacle (echoPin). The Arduino measures the time taken for the echo to return, calculates the distance using the speed of sound, and updates the distance value in centimeters.

2. Distance Zones & LED Indication:  
   The measured distance is categorized into four zones:

   - 0-30 cm: Closest zone — Red LEDs light up.
   - 31-45 cm: Yellow LEDs.
   - 46-60 cm: Blue LEDs.
   - 61-80 cm: White LEDs.

   Each zone corresponds to a specific LED pair, controlled via the shift register. This visually shows how close the obstacle is.

3. Shift Register (74HC595):  
   The Arduino uses three pins to control the 8 LEDs through the shift register:

   - Data (DS): Arduino pin 8
   - Latch (ST_CP): Arduino pin 9
   - Clock (SH_CP): Arduino pin 10

   Using shiftOut(), the Arduino sends the LED pattern to the shift register, which lights up the correct LEDs.

4. Buzzer Alerts:  
   The buzzer on Arduino pin 5 beeps with different speeds depending on the distance zone — faster beeps mean closer distance. The mute button on pin 11 lets me toggle the buzzer sound off/on. It uses an external 10kΩ pull-down resistor.

5. Serial Monitor Bar Indicator:  
   I can open the Serial Monitor (baud rate 9600) on the Arduino IDE to see a simple bar graph representing distance, which helps visualize data alongside the LEDs and buzzer.

---

Wiring Diagram 🔌

Ultrasonic Sensor (HC-SR04)

| HC-SR04 Pin | Connected to Arduino Pin | Notes                   |
|-------------|-------------------------|-------------------------|
| VCC         | 5V                      | Power                   |
| GND         | GND                     | Ground                  |
| Trig        | 7                       | Trigger pin             |
| Echo        | 6                       | Echo pin                |

Shift Register (74HC595)

| 74HC595 Pin | Connected to Arduino Pin | Notes                         |
|-------------|-------------------------|-------------------------------|
| DS (14)     | 8                       | Data pin                      |
| ST_CP (12)  | 9                       | Latch pin                     |
| SH_CP (11)  | 10                      | Clock pin                     |
| Q0 to Q7    | LEDs as described below  | Outputs to LEDs via resistors |

LEDs

| LED # | Color  | Connected to Shift Register Output Pin (Qn) |
|-------|---------|---------------------------------------------|
| 1     | Red     | Q0                                          |
| 2     | Yellow  | Q1                                          |
| 3     | Blue    | Q2                                          |
| 4     | White   | Q3                                          |
| 5     | Red     | Q4                                          |
| 6     | Yellow  | Q5                                          |
| 7     | Blue    | Q6                                          |
| 8     | White   | Q7                                          |

Each LED should have a current-limiting resistor (220Ω recommended) in series on the positive (anode) leg.

Buzzer and Mute Button

| Component   | Connected to Arduino Pin | Notes                     |
|-------------|-------------------------|---------------------------|
| Buzzer      | 5                       | Output buzzer              |
| Mute Button | 11                      | Input with 10kΩ pull-down resistor to GND |

---

Step-by-Step Wiring Instructions 🛠️

1. Connect HC-SR04 VCC to Arduino 5V, GND to Arduino GND.
2. Connect HC-SR04 Trig to Arduino pin 7.
3. Connect HC-SR04 Echo to Arduino pin 6.
4. Connect 74HC595 data pin (DS, 14) to Arduino pin 8.
5. Connect 74HC595 latch pin (ST_CP, 12) to Arduino pin 9.
6. Connect 74HC595 clock pin (SH_CP, 11) to Arduino pin 10.
7. Connect the 8 LEDs through 220Ω resistors to the 74HC595 output pins Q0 to Q7 as per the color order.
8. Connect the buzzer positive leg to Arduino pin 5, negative leg to GND.
9. Connect the mute button between Arduino pin 11 and 5V, and add a 10kΩ resistor from pin 11 to GND (pull-down).
10. Connect Arduino GND to the breadboard ground rail and power ground rail properly.

---

How to Use 🧑‍💻

1. Upload the Arduino sketch to your board.
2. Open the Serial Monitor at 9600 baud.
3. Bring an object closer to the ultrasonic sensor.
4. Watch the LEDs light up according to the distance zone.
5. Hear buzzer beeps speed up as you get closer.
6. Press the mute button to toggle buzzer sound on or off.
7. Watch the distance bar in the Serial Monitor update live.

---

Code Summary 📝

- Ultrasonic sensor triggers pulses and calculates distance.
- Shift register lights pairs of LEDs for distance zones.
- Buzzer beeps with variable frequency.
- Mute button toggles buzzer.
- Serial monitor shows a simple bar graph of distance.

---

Extra Tips 💡

- Always use current-limiting resistors with LEDs to avoid damage.
- Debounce the mute button to avoid multiple toggles on a single press.
- Keep wiring neat and double-check pin connections.
- Experiment with beep timings and LED patterns to customize feedback.

