#include "mavlink_encoder/MavlinkEncoder.hpp"

int
main(int argc, char ** argv)
{
  mavlink_encoder::MavlinkEncoder * encoder = new mavlink_encoder::MavlinkEncoder();

  encoder->statusTextMsg("Hello World", status_text::StatusSeverity::Critical);

  free(encoder);

  exit(EXIT_SUCCESS);
}