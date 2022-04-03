#define private public	// To be able to test private methods

#include <cstring>
#include "evaluation.hpp"
#include "mavlink_encoder/MavlinkEncoder.hpp"

using mavlink_encoder::DigestType;

bool
checksum_isok(const DigestType & digest, unsigned char * desired_crc)
{
	mavlink_encoder::MavlinkEncoder *encoder =
		new mavlink_encoder::MavlinkEncoder(1, 0);

	uint16_t checksum = encoder->checksum(digest, status_text::CrcExtra);

	unsigned char check[2];
	memcpy(check, &checksum, 2);

	free(encoder);
	return check[0] == desired_crc[0] && check[1] == desired_crc[1];

}

int
main(int argc, char ** argv)
{
	// Test 'checksum'
	DigestType digest;
	unsigned char arr[] = {0xfe, 0x33, 0x8c, 0xff, 0x00, 0xfd, 0x06,
		0x48, 0x65, 0x6c, 0x6c, 0x6f};

	digest.len = 57;

	memcpy(digest.digest, arr, sizeof(arr));
	memset(&digest.digest[sizeof(arr)], 0x00, 45);

	unsigned char desired_crc[2];
	desired_crc[0] = 0x51;
	desired_crc[1] = 0x15;

	IS_TRUE(checksum_isok(digest, desired_crc));

	exit(EXIT_SUCCESS);
}