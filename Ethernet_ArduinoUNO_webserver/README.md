Ethernet_ArduinoUNO_webserver: simple webserver with GET parameter parser.

MAC: 0x34:0x35:0x36:0x37:0x38:0x39
IP:  192.168.0.109

In order to test go to following URL: http://192.168.0.109/?par=5

Arduino UNO connected with "HanRun HR911105A with ENC28j60".
net/enc28j60.c to configure ports.

Current configuration is for Arduio UNO.

Arduino UNO           HanRun (ENC28j60)
 ----------            ------------
| SCK    13|----------| 6  SCK     |
| MISO   12|----------| 4  SO      |
| MOSI   11|----------| 5  SI      |
| SS     10|----------| 7  CS      |
|          |          |            |
|    +3.3V |----------| 8  RESET   |
|    +3.3V |----------| 9  Vcc     |
|    GND   |----------| 10 GND     |
 ----------            ------------

Arduino UNO supply voltage from USB cable (5V).
