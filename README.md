| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# IoT based Solar Tracking & Monitoring System

The system incorporates a solar tracking mechanism that adjusts the orientation of solar panels to follow the sun's path throughout the day. Solar trackers come in various types, such as single-axis or dual-axis, and they ensure that solar panels receive maximum sunlight exposure, thereby increasing energy production.


### Platforms used for developing the project

    * ESP-IDF
    * VS code Extension for Espressif IDF

### Interfacing the OLED Display
![oled_display](https://github.com/bjd20/IoT-based-Solar-Tracking-Monitoring-System/assets/106448613/60c89d77-127c-4ffb-bb40-ca4ed47f0149)

![display_code](https://github.com/bjd20/IoT-based-Solar-Tracking-Monitoring-System/assets/106448613/85a000b8-fc37-43d0-8d0b-9774596a8e6a)

### Configure the project

Open the project configuration menu (`idf.py menuconfig`).

Optional: If you need, change the other options according to your requirements.

### Build and Flash

Build the project and flash it to the board, then run the monitor tool to view the serial output:

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for all the steps to configure and use the ESP-IDF to build projects.

* [ESP-IDF Getting Started Guide on ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)
* [ESP-IDF Getting Started Guide on ESP32-S2](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/index.html)
* [ESP-IDF Getting Started Guide on ESP32-C3](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/get-started/index.html)
