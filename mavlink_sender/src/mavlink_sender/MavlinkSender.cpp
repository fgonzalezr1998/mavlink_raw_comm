#include "mavlink_sender/MavlinkSender.hpp"
#include <iostream>

namespace mavlink_sender
{
  MavlinkSender::MavlinkSender()
  {
    std::cout << "I'm MavlinkSender\n";
  }

  void MavlinkSender::statusTextMsg(std::string msg)
  {
    std::cout << "Status text composer\n";
  };
}