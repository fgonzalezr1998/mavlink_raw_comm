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

  mavlink_encoder::DigestType statusTextMsg(const std::string & msg, 
    const status_text::StatusSeverity & severity);

private:

  void composeHeader();

  int seq_n_;  // packet sequence number
};
} // end namespace mavlink_encoder

#endif