#include <StreamClient.h>

#include "Proto/dataExchange.pb.h"
WiFiClient wifi_client; 

StreamClient::StreamClient(const char *server_ip, const int server_port)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("WiFi not connected!");
        return;
    }
    if (!wifi_client.connected())
    {
        if (!wifi_client.connect(server_ip, server_port))
        {
            Serial.print("Failed to connect to server");
            return;
        }
        Serial.print("Connected to server");
    }
}

bool StreamClient::write_raw_data(pb_ostream_t *stream, const pb_field_t *field, void *const *arg)
{
    const uint32_t *data = (const uint32_t *)*arg;
    for (size_t i = 0; i < 3; i++)
    { // Using fixed size of 3 for test data
        if (!pb_encode_tag_for_field(stream, field))
        {
            return false;
        }
        if (!pb_encode_varint(stream, data[i]))
        {
            return false;
        }
    }
    return true;
}

bool StreamClient::greetings()
{
    static ekg_proto_v1_ClientConnectionBlip msg = ekg_proto_v1_ClientConnectionBlip_init_zero;
    static uint8_t buffer[16];

    memset(buffer, 0, sizeof(buffer));

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    // bool hi = true;
    msg.hello = true;

    if (!pb_encode(&stream, ekg_proto_v1_ClientConnectionBlip_fields, &msg)) {
        Serial.print("Error encoding Greeting to server.");
        return false;
    }

    uint32_t size = stream.bytes_written;
    wifi_client.write((uint8_t*)&size, sizeof(size));

    // Send encoded message
    Serial.print("SENT hello");
    wifi_client.write(buffer, size);
    wifi_client.flush();

    return true;
    // send buffer[0..stream.bytes_written)
}