#ifndef SimpleM2XSender_h
#define SimpleM2XSender_h

#include <Client.h>

class SimpleM2XSender
{
    Client* _client;
    const char* _key; 
public:
    SimpleM2XSender(
        Client* client,
        const char* key)
    : _client(client),
      _key(key)
    {}

    int sendFloatData(
        const char* deviceId,
        const char* streamName,
        float value
    );
private:
    void writePutHeader(
        const char* deviceId,
        const char* streamName,
        int contentLength
    );
};

#endif