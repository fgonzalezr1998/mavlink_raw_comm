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
  MavlinkEncoder(int sys_id, int comp_id);

  // Returns DigestType with full statustext message

  mavlink_encoder::DigestType statusTextMsg(const std::string & msg, 
    const status_text::StatusSeverity & severity);

private:

  uint16_t checksum(const mavlink_encoder::DigestType & digest);

  int seq_n_;  // packet sequence number
  int sys_id_, comp_id_;
};
} // end namespace mavlink_encoder

#endif