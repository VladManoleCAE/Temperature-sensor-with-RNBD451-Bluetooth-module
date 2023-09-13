# Temperature-sensor-with-RNBD451-Bluetooth-module

Sensor application over low-energy settings using RNBD451 Bluetooth module. The sensor will read the temperature via I2C, the host will process it in decimal values and send it over BLE to the phone running MBD. The user will be able to see it in Smart Dicover in real time.
Both host and module will run in the lowest power consumption setting.

The sensor value will be read by the MCU and and sent to RNBD451 via UART. From the bluetooth module, the data is sent to the phone via Bluetooth Low Energy.

![image](https://github.com/VladManoleCAE/Temperature-sensor-with-RNBD451-Bluetooth-module/assets/133333286/54a0ee32-cd6f-4555-8088-ea82c1a1d199)

The sensor, BLE module and the PIC MCU are in deep sleep mode until the wake up button is pressed in order to save as much energy as possible. All the sleep modes are set in software.


![image](https://github.com/VladManoleCAE/Temperature-sensor-with-RNBD451-Bluetooth-module/assets/133333286/f1fe919d-48db-4366-9909-15078e7b906a)


Some Applications where this implementation can be used are: 
Industrial monitoring:
![image](https://github.com/VladManoleCAE/Temperature-sensor-with-RNBD451-Bluetooth-module/assets/133333286/e09e019c-74ca-469a-b4a7-9fc93106b9f6)

Automotive:
![image](https://github.com/VladManoleCAE/Temperature-sensor-with-RNBD451-Bluetooth-module/assets/133333286/9d5f008e-598b-42eb-add0-92afd3e3c5e2)

IoT:
![image](https://github.com/VladManoleCAE/Temperature-sensor-with-RNBD451-Bluetooth-module/assets/133333286/deb14a95-2dfa-4faa-abe8-8126c61dd980)
