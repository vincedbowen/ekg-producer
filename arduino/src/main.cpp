#include <cstdlib>

#include <WiFiUtils.h>
#include <LedBitmap.h>
#include <StreamClient.h>

#include "Arduino_LED_Matrix.h"

void setup()
{
  LedBitmap led;
  led.display_bitmap(&LedBitmap::build_hi);

  Serial.begin(9600);
  WiFiUtils wifi;
  bool wifi_status = wifi.connect_to_wifi(getenv("SSID"), getenv("PASSWORD"));
  if (wifi_status)
  {
    led.display_bitmap(&LedBitmap::set_wifi_success, 5000);
  }
  else
  {
    led.display_bitmap(&LedBitmap::set_wifi_fail, false);
    exit(1);
  }
  StreamClient client;
  client.greetings();
  delay(5000);
}

void loop()
{
  // if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
  //   Serial.println('!');
  // }
  // else{
  //   // send the value of analog input 0:
  //     Serial.println(analogRead(A0));
  // }
  // //Wait for a bit to keep serial data from saturating
  // delay(1);
}