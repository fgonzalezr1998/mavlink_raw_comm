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

#include <string>
#include "mavlink_encoder/Digest.hpp"

#ifndef STATUS_TEXT__STATUS_TEXT_ENCODER_CPP
#define STATUS_TEXT__STATUS_TEXT_ENCODER_CPP

namespace status_text
{
enum {
	CrcExtra = 83,
};

enum StatusSeverity
{
  Emergency = 0,
  Alert,
  Critical,
  Error,
  Warning,
  Notice,
  Info,
  Debug
};

class StatusTextEncoder
{
public:
  // Not should be clonable:
  StatusTextEncoder(StatusTextEncoder &other) = delete;

  static StatusTextEncoder* getInstance();

	/*
	 * Store on 'out_digest' DigestType with the statustext Payload
	 *
	 * @param msg Message to be encoded
	 * @param severity Statustext severity
	 * @param out_digest DigestType where the calculated payload will be stored
	 */
  bool composePayload(const std::string & msg, 
    const StatusSeverity & severity,
    mavlink_encoder::DigestType * out_digest);

	/*
	 * Store on 'out_digest' the DigestType with the statustext Header
	 *
	 * @param len_payload Lenght of the message's payload
	 * @param seq_n Sequence number
	 * @param sys_id System ID (Given by flight controller)
	 * @param comp_id Component ID (Given by flight controller)
	 * @param out_digest DigestType where the calculated header will be stored
	 */
  void composeHeader(int len_payload, int seq_n,
    int sys_id, int comp_id, mavlink_encoder::DigestType * out_digest);

  // Not should be assignable
  void operator=(const StatusTextEncoder &) = delete;

protected:
  StatusTextEncoder(){};

private:
	/*
	 * Converts std string to char array (without null termination)
	 *
	 * @param text Input string
	 * @param buff Output char array
	 */
  void string2Buffer(const std::string & text, char * buff);
};

}   // end namespace status_text

#endif