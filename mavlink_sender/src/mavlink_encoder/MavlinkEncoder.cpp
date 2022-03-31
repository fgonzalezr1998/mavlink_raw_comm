#include <iostream>
#include <memory>
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

  void MavlinkEncoder::statusTextMsg(const std::string & msg, const status_text::StatusSeverity & severity)
  {
    status_text::StatusTextEncoder *textEncoder = status_text::StatusTextEncoder::getInstance();

    textEncoder->composePayload(msg, severity);

    free(textEncoder);
  }

  /*
   * Private Methods
   */
  
  void MavlinkEncoder::composeHeader()
  {

  }
}