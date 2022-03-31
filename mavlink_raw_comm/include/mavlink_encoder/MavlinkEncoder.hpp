#include <string>
#include "mavlink_encoder/Digest.hpp"
#include "status_text/StatusTextEncoder.hpp"

#ifndef MAVLINK_ENCODER__MAVLINK_ENCODER_CPP
#define MAVLINK_ENCODER__MAVLINK_ENCODER_CPP

namespace mavlink_encoder
{

class MavlinkEncoder
{
public:
  MavlinkEncoder();

  // Returns DigestType with full statustext message

  mavlink_encoder::DigestType statusTextMsg(const std::string & msg, 
    const status_text::StatusSeverity & severity);

private:

  uint16_t checksum(const mavlink_encoder::DigestType & digest);

  int seq_n_;  // packet sequence number
};
} // end namespace mavlink_encoder

#endif