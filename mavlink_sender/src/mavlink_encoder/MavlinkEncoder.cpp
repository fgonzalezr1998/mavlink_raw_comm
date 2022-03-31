#include <iostream>
#include <memory>
#include <cstring>
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

  mavlink_encoder::DigestType MavlinkEncoder::statusTextMsg(const std::string & msg, 
    const status_text::StatusSeverity & severity)
  {
    status_text::StatusTextEncoder *textEncoder = status_text::StatusTextEncoder::getInstance();

    mavlink_encoder::DigestType digest;
    memset(digest.digest, 0, mavlink_encoder::MAXLENDIGEST);

    textEncoder->composePayload(msg, severity, seq_n_, &digest);
    seq_n_++;

    free(textEncoder);

    return digest;
  }

  /*
   * Private Methods
   */
  
  void MavlinkEncoder::composeHeader()
  {

  }
}