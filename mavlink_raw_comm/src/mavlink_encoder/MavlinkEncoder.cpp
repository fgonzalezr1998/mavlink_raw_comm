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

#include <iostream>
#include <memory>
#include <cstring>
#include "mavlink_encoder/checksum.h"
#include "mavlink_encoder/MavlinkEncoder.hpp"

namespace mavlink_encoder
{
  /*
	 ***********************
   *   Public Methods    *
   ***********************
	 */

  MavlinkEncoder::MavlinkEncoder(int sys_id = 1, int comp_id = 0)
  : seq_n_(0)
  {
    this->sys_id_ = sys_id;
    this->comp_id_ = comp_id;
  }

  mavlink_encoder::DigestType
	MavlinkEncoder::statusTextMsg(
    const std::string & msg, const status_text::StatusSeverity & severity)
  {
    mavlink_encoder::DigestType out_digest;
    status_text::StatusTextEncoder *textEncoder;

    textEncoder = status_text::StatusTextEncoder::getInstance();

    // get Payload
    mavlink_encoder::DigestType payloadDigest;
    memset(payloadDigest.digest, 0, mavlink_encoder::MAXLENDIGEST);

    if (!textEncoder->composePayload(msg, severity, &payloadDigest))
		{
			free(textEncoder);
			throw StatusTextEncodeException();
		}
    
    // Get Header
    mavlink_encoder::DigestType headerDigest;
    textEncoder->composeHeader(payloadDigest.len,
			seq_n_, sys_id_, comp_id_, &headerDigest);

		// Concatenate Header + Payload
    unsigned char digest[payloadDigest.len + headerDigest.len];
    memcpy(digest, headerDigest.digest, headerDigest.len);
    memcpy(&digest[headerDigest.len], payloadDigest.digest, payloadDigest.len);

    memcpy(out_digest.digest, digest, payloadDigest.len + headerDigest.len);
    out_digest.len = payloadDigest.len + headerDigest.len;

		// Get Checksum
    uint16_t check = checksum(out_digest, status_text::CrcExtra);

		memcpy(&out_digest.digest[out_digest.len], &check, 2);
    out_digest.len += 2;

    free(textEncoder);
    return out_digest;
  }

	void
	MavlinkEncoder::increaseSeqN()
	{
		seq_n_++;
	}

	void
	MavlinkEncoder::setSeqN(int seq)
	{
		seq_n_ = seq;
	}

  /*
	 ***********************
   *   Private Methods   *
   ***********************
	 */

  uint16_t
	MavlinkEncoder::checksum(const mavlink_encoder::DigestType & digest,
		uint8_t crc_extra)
  {
    // Ignore the first byte (magic byte -marker-)
  
    uint16_t checksum = crc_calculate(&digest.digest[1], digest.len - 1);
		crc_accumulate(crc_extra, &checksum);

    return checksum;
  }
}