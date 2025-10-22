#include <Arduino.h>
#include <WiFiS3.h>

/**
 * Implementation to allow ease of use for connecting Arduino to WiFi. 
 * 
 * Should likely be turned into a singleton
 */
class WiFiUtils
{
public:
  /**
   * Constructor for WiFiUtils
   */
  WiFiUtils();
  /**
   * Destructor for WiFiUtils
   */
  ~WiFiUtils();
  /**
   * Connects Arduino Uno R4 WiFi to network using WiFiS3 to create an interface with the ESP32-S3 module
   * 
   * @param ssid Full name of WiFi network to connect to 
   * @param password Password for connecting to WiFi network
   */
  void connect_to_wifi(char ssid[], char password[]);
};