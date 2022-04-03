#include <cstring>
#include <iostream>
#include "status_text/StatusTextEncoder.hpp"

#define MAXTEXTLENGHT 50
#define MINPKGLEN 8
#define MSGID 253

namespace status_text
{
  StatusTextEncoder::StatusTextEncoder()
  {
    std::cout << "I'm status text encoder\n";
  }

  StatusTextEncoder*
	StatusTextEncoder::getInstance()
  {
    static StatusTextEncoder *encoder = new StatusTextEncoder();
    return encoder;
  }    

  bool
	StatusTextEncoder::composePayload(
    const std::string & msg, const StatusSeverity & severity,
    mavlink_encoder::DigestType * out_digest)
  {
    int len = MAXTEXTLENGHT + 1;

    // If message is too long, it is invalid
    if (msg.size() > MAXTEXTLENGHT)
    {
      std::cout << "Message too long\n";
      return false;
    }

    // Field1 Severity
    uint8_t sev = (uint8_t)severity;

    // Field2 text as char array
    char text[MAXTEXTLENGHT];
    string2Buffer(msg, text);

    // Concatenate all fields
    unsigned char payload[len];

    payload[0] = sev; // 1
    memcpy(&payload[1], text, MAXTEXTLENGHT);  	// 1 + 2

    memcpy(out_digest->digest, payload, len);
    out_digest->len = len;

		return true;
  }

  void
	StatusTextEncoder::composeHeader(int len_payload, int seq_n,
    int sys_id, int comp_id, mavlink_encoder::DigestType * out_digest)
  {
    int len = MINPKGLEN - 2;
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

  void
	StatusTextEncoder::string2Buffer(const std::string & text, char * buff)
  {
    memset(buff, 0, MAXTEXTLENGHT);
    for (int i = 0; i < text.size(); i++)
    {
      buff[i] = text.at(i);
    }
  }
}