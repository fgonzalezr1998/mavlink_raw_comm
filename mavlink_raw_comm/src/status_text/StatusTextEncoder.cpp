/*********************************************************************
*  Software License Agreement (BSD License)
*
*   Copyright (c) 2022
*   All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions
*   are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above
*      copyright notice, this list of conditions and the following
*      disclaimer in the documentation and/or other materials provided
*      with the distribution.
*    * Neither the name of the author nor the names of its
*      contributors may be used to endorse or promote products derived
*      from this software without specific prior written permission.
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*   COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*   POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Fernando Gonzalez fergonzaramos@yahoo.es  */

#include <cstring>
#include <iostream>
#include "status_text/StatusTextEncoder.hpp"

#define MAXTEXTLENGHT 50
#define MINPKGLEN 8
#define MSGID 253

namespace status_text
{
	/*
	 ***********************
   *   Public Methods    *
   ***********************
	 */

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

  void
  StatusTextEncoder::decodePayload(
		const mavlink_encoder::DigestType & payload, PayloadStatusTextType * decoded_payload)
  {
    // Decode severity
    decoded_payload->severity = static_cast<StatusSeverity>(payload.digest[0]);

    // Decode text
    char *text = (char*)malloc(MAXTEXTLENGHT);
    // - Ensure not decoding more than 50 chars
    memcpy(text, (char *)&payload.digest[1], MAXTEXTLENGHT);
    decoded_payload->text = std::string(text);

    free(text);
  }

  /*
	 ***********************
   *   Private Methods   *
   ***********************
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