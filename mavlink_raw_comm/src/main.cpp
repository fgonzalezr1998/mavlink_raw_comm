/*********************************************************************
*  Software License Agreement (BSD License)
*
*   Copyright (c) 2022
*   All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions
*   are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above
*      copyright notice, this list of conditions and the following
*      disclaimer in the documentation and/or other materials provided
*      with the distribution.
*    * Neither the name of the author nor the names of its
*      contributors may be used to endorse or promote products derived
*      from this software without specific prior written permission.
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*   COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*   POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Fernando Gonzalez fergonzaramos@yahoo.es  */

#include <iostream>
#include "mavlink_encoder/MavlinkEncoder.hpp"

int
main(int argc, char ** argv)
{
  mavlink_encoder::MavlinkEncoder * encoder = new mavlink_encoder::MavlinkEncoder(1, 0);

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

	mavlink_encoder::DigestMsgType decoded;
	encoder->decodePkg(digest, &decoded);

  free(encoder);

  exit(EXIT_SUCCESS);
}