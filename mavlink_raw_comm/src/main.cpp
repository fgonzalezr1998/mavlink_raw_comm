#include "mavlink_encoder/MavlinkEncoder.hpp"

int
main(int argc, char ** argv)
{
  mavlink_encoder::MavlinkEncoder * encoder = new mavlink_encoder::MavlinkEncoder();

  mavlink_encoder::DigestType digest;
  digest = encoder->statusTextMsg("Hello World", status_text::StatusSeverity::Critical);

  digest.print_digest();

  free(encoder);

  exit(EXIT_SUCCESS);
}