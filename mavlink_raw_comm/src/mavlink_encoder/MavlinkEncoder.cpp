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

  MavlinkEncoder::MavlinkEncoder()
  : seq_n_(0)
  {
    std::cout << "I'm Mavlink Encoder\n";
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

    textEncoder->composePayload(msg, severity, seq_n_, &payloadDigest);
    
    // Get Header
    mavlink_encoder::DigestType headerDigest;
    textEncoder->composeHeader(payloadDigest.len, seq_n_, 1, 12, &headerDigest);

    unsigned char digest[payloadDigest.len + headerDigest.len];
    memcpy(digest, headerDigest.digest, headerDigest.len);
    memcpy(&digest[headerDigest.len], payloadDigest.digest, payloadDigest.len);

    memcpy(out_digest.digest, digest, payloadDigest.len + headerDigest.len);
    out_digest.len = payloadDigest.len + headerDigest.len;

    seq_n_++;
    free(textEncoder);
    return out_digest;
  }

  /*
   * Private Methods
   */
  uint16_t MavlinkEncoder::checksum(const mavlink_encoder::DigestType & digest)
  {
    // CODE THIS!
    return 0;
  }
}