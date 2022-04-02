#include <iostream>
#include <memory>
#include <cstring>
#include "mavlink_encoder/checksum.h"
#include "mavlink_encoder/MavlinkEncoder.hpp"

namespace mavlink_encoder
{
  /*
   * Public Methods
   */

  MavlinkEncoder::MavlinkEncoder(int sys_id = 1, int comp_id = 0)
  : seq_n_(0)
  {
    std::cout << "I'm Mavlink Encoder\n";
    this->sys_id_ = sys_id;
    this->comp_id_ = comp_id;
  }

  mavlink_encoder::DigestType MavlinkEncoder::statusTextMsg(
    const std::string & msg, const status_text::StatusSeverity & severity)
  {
    mavlink_encoder::DigestType out_digest;
    status_text::StatusTextEncoder *textEncoder;

    textEncoder = status_text::StatusTextEncoder::getInstance();

    // get Payload
    mavlink_encoder::DigestType payloadDigest;
    memset(payloadDigest.digest, 0, mavlink_encoder::MAXLENDIGEST);

    if (!textEncoder->composePayload(msg, severity, seq_n_, &payloadDigest))
			throw StatusTextEncodeException();
    
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
    uint16_t check = checksum(out_digest);

    out_digest.digest[out_digest.len] = check / (uint16_t)256;
    out_digest.digest[out_digest.len + 1] = check % (uint16_t)256;
    out_digest.len += 2;

    free(textEncoder);
    return out_digest;
  }

  /*
   * Private Methods
   */
  uint16_t MavlinkEncoder::checksum(const mavlink_encoder::DigestType & digest)
  {
    // Ignore the first byte (magic byte -marker-)
  
    uint16_t checksum = crc_calculate(&digest.digest[1], digest.len);

    return checksum;
  }
}