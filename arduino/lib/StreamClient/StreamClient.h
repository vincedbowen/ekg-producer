#include <WiFiS3.h>
#include "pb_encode.h"
#include "pb_decode.h"

class StreamClient
{
private:
    /* data */
    // WiFiClient wifi_client; 
    static bool write_raw_data(pb_ostream_t *stream, const pb_field_t *field, void * const *arg);
public:
    StreamClient(const char* server_ip = "10.0.0.8", const int server_port = 8080);
    bool greetings();
};

