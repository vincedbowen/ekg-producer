#include <WiFiUtils.h>

// TODO: Add error handling around this entire file

WiFiUtils::WiFiUtils()
{
    if (WiFi.status() == WL_NO_MODULE)
    {
        Serial.print("Cannot connect to Arduino UNO R4 via WiFi module.");
        return;
    }
    if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION)
    {
        Serial.print("Cannot connect. Please update firmware.");
        return;
    }
}

WiFiUtils::~WiFiUtils()
{
    int disconnection_status = WiFi.disconnect();
    if (disconnection_status == 1)
    {
        Serial.print("Successfully disconnected from network.");
        return;
    }
    Serial.print("Could not disconnect from network!!");
}

bool WiFiUtils::connect_to_wifi(char ssid[], char password[])
{
    Serial.print("Attempting to connect to: ");
    Serial.println(ssid);
    int connection_status = WiFi.begin(ssid, password);
    if (connection_status == 3)
    {
        Serial.print("Successfully connected to WiFi.");
        return true;
    }
    Serial.print("Connection to WiFi failed.");
    return false;
}