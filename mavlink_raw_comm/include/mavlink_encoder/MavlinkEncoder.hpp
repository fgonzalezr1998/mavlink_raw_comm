#include <string>
#include "mavlink_encoder/Digest.hpp"
#include "status_text/StatusTextEncoder.hpp"

#ifndef MAVLINK_ENCODER__MAVLINK_ENCODER_CPP
#define MAVLINK_ENCODER__MAVLINK_ENCODER_CPP

namespace mavlink_encoder
{

struct StatusTextEncodeException : public std::exception
{
	const char * what() const throw()
	{
		return "[statusTextMsg] Status text encoding failed!";
	}
};

class MavlinkEncoder
{
public:
  MavlinkEncoder(int sys_id, int comp_id);

  // Returns DigestType with full statustext message

  mavlink_encoder::DigestType statusTextMsg(const std::string & msg, 
    const status_text::StatusSeverity & severity);

	void increaseSeqN();
	void setSeqN(int seq);

private:

  uint16_t checksum(const mavlink_encoder::DigestType & digest);

  int seq_n_;  // packet sequence number
  int sys_id_, comp_id_;
};
} // end namespace mavlink_encoder

#endif