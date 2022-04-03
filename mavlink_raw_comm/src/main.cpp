#include <iostream>
#include "mavlink_encoder/MavlinkEncoder.hpp"

int
main(int argc, char ** argv)
{
  mavlink_encoder::MavlinkEncoder * encoder = new mavlink_encoder::MavlinkEncoder(255, 0);

	mavlink_encoder::DigestType digest;
	try
	{
		encoder->setSeqN(140);
  	digest = encoder->statusTextMsg("Hello", status_text::StatusSeverity::Info);
	}
	catch(const std::exception & e)
	{
		std::cout << e.what() << std::endl;
		free(encoder);
		exit(EXIT_FAILURE);
	}


  digest.print_digest();

  free(encoder);

  exit(EXIT_SUCCESS);
}