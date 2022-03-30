#include <string>

#ifndef MAVLINK_SENDER_CPP
#define MAVLINK_SENDER_CPP

namespace mavlink_sender
{
class MavlinkSender
{
public:
  MavlinkSender();

  void statusTextMsg(std::string msg);
};
} // end namespace mavlink_sender

#endif