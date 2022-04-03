#define private public
#include <cstring>
#include "evaluation.hpp"
#include "status_text/StatusTextEncoder.hpp"
#include "mavlink_encoder/Digest.hpp"

using status_text::StatusTextEncoder;
using mavlink_encoder::DigestType;

bool
statustext_header_isok(int payload_len, int seq_n,
	int sys_id, int comp_id, const DigestType & desired_result)
{
	StatusTextEncoder *encoder = StatusTextEncoder::getInstance();

	DigestType digest;
	encoder->composeHeader(payload_len, seq_n, sys_id, comp_id, &digest);

	return digest == desired_result;
}

int
main(int argc, char ** argv)
{
	DigestType digest;

	digest.digest[0] = 0xFE;
	digest.digest[1] = 0x36;
	digest.digest[2] = 0x00;
	digest.digest[3] = 0x01;
	digest.digest[4] = 0x00;
	digest.digest[5] = 0xfd;
	digest.len = 6;

	// Check 'composeHeader'
	IS_TRUE(statustext_header_isok(54, 0, 1, 0, digest));
}