#include "SimpleM2XSender.h"

#include <stdio.h>

static const char* M2X_HOST = "api-m2x.att.com";
static const int M2X_PORT = 80;
static const int BUF_SIZE = 32;
static char buf[BUF_SIZE];

int SimpleM2XSender::sendFloatData(
    const char* deviceId,
    const char* streamName,
    float value
)
{
    if (_client->connect(M2X_HOST, M2X_PORT))
    {
        String valueString =
            String("{\"value\":\"") +
            String(value) + 
            String("\"}");
        writePutHeader(deviceId, streamName, valueString.length());
        _client->println(valueString);
    }
    else
    {
        return -1;
    }
    String response = _client->readString();
    return 0;
}

void SimpleM2XSender::writePutHeader(
    const char* deviceId,
    const char* streamName,
    int contentLength
)
{
    _client->print("PUT /v2/devices/");
    _client->print(deviceId);
    _client->print("/streams/");
    _client->print(streamName);
    _client->println("/value HTTP/1.0");
    _client->print("Host: ");
    _client->println(M2X_HOST);
    _client->println("User-Agent: curl/7.43.0");
    _client->print("X-M2X-KEY: ");
    _client->println(_key);
    _client->println("Content-Type: application/json");
    _client->println("Content-Length: " + contentLength);
    _client->println();
}
