# Temperature-sensor-with-RNBD451-Bluetooth-module

Sensor application over low-energy settings using RNBD451 Bluetooth module. The sensor will read the temperature via I2C, the host will process it in decimal values and send it over BLE to the phone running MBD. The user will be able to see it in Smart Dicover in real time.
Both host and module will run in the lowest power consumption setting.

The sensor value will be read by the MCU and and sent to RNBD451 via UART. From the bluetooth module, the data is sent to the phone via Bluetooth Low Energy.

![image](https://github.com/VladManoleCAE/Temperature-sensor-with-RNBD451-Bluetooth-module/assets/133333286/54a0ee32-cd6f-4555-8088-ea82c1a1d199)
