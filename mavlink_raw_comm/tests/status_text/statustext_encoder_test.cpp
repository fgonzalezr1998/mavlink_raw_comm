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

bool
payload_isok(const std::string & msg,
	const status_text::StatusSeverity & sev, const DigestType & desired_result)
{
	DigestType digest;
	StatusTextEncoder *encoder = StatusTextEncoder::getInstance();

	encoder->composePayload(msg, status_text::StatusSeverity::Critical, &digest);

	return digest == desired_result;
}

int
main(int argc, char ** argv)
{
	DigestType digest;

	// Check 'composeHeader'

	digest.digest[0] = 0xFE;
	digest.digest[1] = 0x33;
	digest.digest[2] = 0x00;
	digest.digest[3] = 0x01;
	digest.digest[4] = 0x00;
	digest.digest[5] = 0xfd;
	digest.len = 6;

	IS_TRUE(statustext_header_isok(51, 0, 1, 0, digest));

	//Check 'composePayload'

	digest.digest[0] = 0x02;
	digest.digest[1] = 0x48;
	digest.digest[2] = 0x65;
	digest.digest[3] = 0x6c;
	digest.digest[4] = 0x6c;
	digest.digest[5] = 0x6f;
	memset(&digest.digest[6], 0x00, 45);
	digest.len = 51;

	IS_TRUE(payload_isok("Hello", status_text::Critical, digest));
}