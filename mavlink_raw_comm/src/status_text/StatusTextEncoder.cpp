#include <cstring>
#include <iostream>
#include "status_text/StatusTextEncoder.hpp"

#define MAXTEXTLENGHT 50
#define MINTEXTLENGHT 8
#define MSGID 253

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

  void StatusTextEncoder::composePayload(
    const std::string & msg, const StatusSeverity & severity,
    int seq_n, mavlink_encoder::DigestType * out_digest)
  {
    int len = msg.size() + 4;

    // If message is too long, it is invalid
    if (msg.size() > MAXTEXTLENGHT)
    {
      std::cout << "Message too long\n";
      out_digest = nullptr;
      return;
    }

    // Field1 Severity
    uint8_t sev = (uint8_t)severity;

    // Field2 text as char array
    char text[MAXTEXTLENGHT + 1];
    string2Buffer(msg, text);

    // Field3 id
    uint16_t id = 0;

    // Field4 sequence number
    uint8_t seq = (uint8_t)seq_n;

    // Concatenate all fields
    unsigned char payload[len];

    payload[0] = sev; // 1
    memcpy(&payload[1], text, msg.size());  // 1 + 2

    payload[msg.size() + 1] = id / 256;
    payload[msg.size() + 2] = id % 256; // 1 + 2 + 3
    payload[msg.size() + 3] = seq;      // 1 + 2 + 3 + 4

    memcpy(out_digest->digest, payload, len);
    out_digest->len = len;
  }

  void StatusTextEncoder::composeHeader(int len_payload, int seq_n,
    int sys_id, int comp_id, mavlink_encoder::DigestType * out_digest)
  {
    int len = MINTEXTLENGHT - 2;
    unsigned char header[len];

    // Field1 Packet start marker
    header[0] = (uint8_t)0xFE;

    // Field2 Payload lenght
    header[1] = (uint8_t)len_payload;

    // Field3 Seq number
    header[2] = (uint8_t)seq_n;

    // Field4 System ID
    header[3] = (uint8_t)sys_id;

    // Field5 Component ID
    header[4] = (uint8_t)comp_id;

    // Field6 Message ID
    header[5] = (uint8_t)MSGID;

    memcpy(out_digest->digest, header, len);
    out_digest->len = len;
  }

  /*
   * Private Methods
   */

  void StatusTextEncoder::string2Buffer(const std::string & text, char * buff)
  {
    memset(buff, 0, MAXTEXTLENGHT + 1);
    for (int i = 0; i < text.size(); i++)
    {
      buff[i] = text.at(i);
    }
  }
}