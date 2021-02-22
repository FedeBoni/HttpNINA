# HttpNINA

Simple http for WiFiNINA Arduino board (like Arduino Uno WiFi Rev. 2)

## Installation

Just download and put in Arduino's Libraries folder.

WIFiNINA library is required.


## Usage

```c++
#include <WiFiNINA.h>
#include <HttpNINA.h>

WifiNINA wifi;
HttpNina http;

void setup(){
    wifi.config("192.168.1.2", "8.8.8.8", "192.168.1.1", "255.255.255.0"); // replace with your net config
    wifi.begin("my_ssid", "my_password");
    http.init(80); //listening port
    http.start();
}

void loop(){
    http.listen();  // by default listen is blocking until new connection will be received
    Serial.println(http.method);
    Serial.println(http.path);
    Serial.println(http.getQueryValue("value"));
    http.sendHeader(200); // OK code
    http.sendResponce("Hello word!");
    http.endResponce;
}

```

## License
[MIT](https://choosealicense.com/licenses/mit/)