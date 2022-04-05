
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
#include "status_text/StatusTextEncoder.hpp"

#ifndef MAVLINK_ENCODER__MAVLINK_ENCODER_CPP
#define MAVLINK_ENCODER__MAVLINK_ENCODER_CPP

namespace mavlink_encoder
{

enum MsgsIds {
	StatusText = 253,
};

struct StatusTextEncodeException : public std::exception
{
	const char * what() const throw()
	{
		return "[statusTextMsg] Status text encoding failed!";
	}
};

typedef struct DigestMsgType DigestMsgType;
struct DigestMsgType {
	MsgsIds msg_type;
	DigestType header;
	DigestType payload;
	uint16_t checksum;
};

class MavlinkEncoder
{
public:
	/*
	 * Constructor
	 *
	 * @param sys_id System ID (given by flight controller). Default: 1
	 * @param sys_id Component ID (given by flight controller). Default: 0
	 */
  MavlinkEncoder(int sys_id, int comp_id);

  /* Returns a digest with full statustext message encoded following mavlink
	 * packages specification
	 *
	 * @param msg Message to be sended (50 chars maximum)
	 * @param severity Severity of the statustext message
	 * 
	 * @return DigestType that contains the full message encoded and ready
	 * to be sended to a Pixhawk/Autopilot
	 * 
	 * @throws mavlink_encoder::StatusTextEncodeException Thrown
	 * if the message is larger than 50 bytes
	 */
  DigestType statusTextMsg(const std::string & msg, 
    const status_text::StatusSeverity & severity);

	/*
	 * Returns if the specified Mavlinkv1 package is not malformed
	 *
	 * @param full_pkg DigestType conteining the package's digest
	 * 
	 * @return true if package is correct. false if it is malformed
	 */
	bool msgIntegrityIsOk(const DigestType & full_pkg);

	/*
	 * Decode specified Mavlinkv1 package
	 *
	 * @param digest DigestType that represents a Mavlinkv1 raw package
	 * @param decoded_msg Output decoded message
	 * 
	 * @return true if the package was succesfully decoded. false, otherwise
	 */
	bool decodePkg(const DigestType & digest, DigestMsgType * decoded_msg);

	/*
	 * Increase in one the sequence number. It will be encoded in the next package
	 * 	bytes calculated
	 */
	void increaseSeqN();

	/*
	 * Set specific sequence number. It will be encoded in the next package
	 * 	bytes calculated
	 * 
	 * @param seq sequence numbr to set
	 */
	void setSeqN(int seq);

private:
	/*
	 * Check if a package header is correct based on the full package data
	 *
	 * @param header DigestType containing the header's digest
	 * @param full_pkg DigestType containing the full Mavlinkv1 package
	 * 
	 * @return true if the header is correct. false otherwise
	 */
	bool headerIsOk(const DigestType & header, const DigestType & full_pkg);

	/*
	 * Check the integrity of a message
	 * @param digest Input message
	 * @param crc_extra crc_extra. It depends on the type of message
	 * 
	 * @return true if the checksum is correct. false, otherwise
	 */
	bool crcIsOk(const DigestType & digest, uint8_t crc_extra);

	/*
	 * Returns the checksum of a given mavlink package
	 * @param digest digest with the full mavlink package
	 * 	data (header + payload)
	 * @param crc_extra additional byte to be used as extra seed for
	 * 	the crc calculation. It depends on the message type
	 */
  uint16_t checksum(const mavlink_encoder::DigestType & digest,
		uint8_t crc_extra);

	/*
	 * Get the crc_extra given the message id
	 *
	 * @param id message id obtained from Mavlinkv1 package bytes
	 * @param crc_extra Here the crc_extra is stored
	 */
	void getCrcExtra(uint8_t id, uint8_t * crc_extra);

  int seq_n_;  // packet sequence number
  int sys_id_, comp_id_;
};
} // end namespace mavlink_encoder

#endif