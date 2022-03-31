#include <cstring>
#include <iostream>
#include "status_text/StatusTextEncoder.hpp"

#define MAXTEXTLENGHT 50

namespace status_text
{
    StatusTextEncoder::StatusTextEncoder()
    {
        std::cout << "I'm status text encoder\n";
    }

    StatusTextEncoder* StatusTextEncoder::getInstance()
    {
        static StatusTextEncoder *encoder = new StatusTextEncoder();
        return encoder;
    }    

    void StatusTextEncoder::composePayload(const std::string & msg,
        const StatusSeverity & severity, int seq_n, mavlink_encoder::DigestType * out_digest)
    {
        int len = msg.size() + 4;
        // Field1 --> Severity

        uint8_t sev = severity;

        // Field2 text as char array
        char text[MAXTEXTLENGHT + 1];
        memset(text, 0, MAXTEXTLENGHT + 1);
        if (msg.size() > MAXTEXTLENGHT)
        {
            std::cout << "Message too long\n";
            return;
        }
        for (int i = 0; i < msg.size(); i++)
        {
            text[i] = msg.at(i);
        }

        // Field3 id
        uint16_t id = 0;

        // Field4 sequence number
        uint8_t seq = seq_n;

        unsigned char payload[len];

        payload[0] = sev;
        for (int i = 0; i < msg.size(); i++)
        {
            payload[i + 1] = text[i];
        }

        payload[msg.size() + 1] = id / 256;
        payload[msg.size() + 2] = id % 256;
        payload[msg.size() + 3] = seq;

        memcpy(out_digest->digest, payload, len);
        out_digest->len = len;
    }
}