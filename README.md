# HttpNINA

Simple http for wifiNINA Arduino board

## Installation

Just download and put in Arduino's Libraries folder.

WIFiNINA library is required.


## Usage

```
#include <HttpNINA.h>
HttpNina http;

void setup(){
    http.init(80) //listening port
    http.start()
}

void loop(){
    if(http.listen(false)){
        Serial.println(http.method);
        Serial.println(http.path);
        Serial.print(http.getQueryValue("value"));
    }
}

```

## License
[MIT](https://choosealicense.com/licenses/mit/)