#include "mavlink_sender/MavlinkSender.hpp"

int
main(int argc, char ** argv)
{
  mavlink_sender::MavlinkSender * sender = new mavlink_sender::MavlinkSender();

  sender->statusTextMsg("Hello World");


  free(sender);
  exit(EXIT_SUCCESS);
}