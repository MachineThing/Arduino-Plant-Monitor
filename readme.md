# Arduino Plant Monitor

Arduino Board used: [NodeMCU](https://www.amazon.com/gp/product/B081CSJV2V/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
Website: TBA

## How to setup

**Note: Your Wifi needs to be 2.4GHz for this to work as the NodeMCU does not support 5GHz!**

You will need:
- The [NodeMCU](https://www.amazon.com/gp/product/B081CSJV2V/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1) board
- [DHT11 humidity and temperature measure](https://www.amazon.com/dp/B01DKC2GQ0?tag=duckduckgo-ffab-20&linkCode=osi&th=1&psc=1)
- [Hygrometer](https://www.amazon.com/Cylewet-Moisture-Humidity-Detection-2-36inches/dp/B01N7NA3HP/ref=sr_1_12?dchild=1&keywords=arduino+soil+moisture+sensor&qid=1591502485&sr=8-12)
- A house plant

1. Connect the DHT11 to pin D1 and the hygrometer to pin A0

2. Make a new file in the `plant` directory called `ssid.h` and put this in the file:
```
extern const char* ssid="Your WiFi SSID";
extern const char* password="Your WiFi password";
```

3. In the Arduino IDE preferences add `https://arduino.esp8266.com/stable/package_esp8266com_index.json` to `Additional Boards Manager URLs`.
4. In the Library Manager (Under `Tools, Manage Libraries...`) install `DHT sensor library for ESPx` by `beegee_tokyo`.
5. And in the Board Manager (Unser `Tools, Board, Boards Manager...`) install `esp8266` by `ESP8266 Community` and select `NodeMCU 1.0 (ESP-12E Module)`

6. Then compile and upload.
