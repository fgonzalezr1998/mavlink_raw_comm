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

bool
crc_isok(const DigestType & digest, uint8_t crc_extra)
{
	mavlink_encoder::MavlinkEncoder *encoder =
		new mavlink_encoder::MavlinkEncoder(1, 0);

	return encoder->crcIsOk(digest, crc_extra);
}

void
test_checksum1()
{
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
}

void
test_checksum2()
{
	DigestType digest;
	unsigned char arr[] = {0xfe, 0x33, 0x8c, 0x01, 0x00, 0xfd, 0x06,
		0x48, 0x65, 0x6c, 0x6c, 0x6f};

	digest.len = 57;

	memcpy(digest.digest, arr, sizeof(arr));
	memset(&digest.digest[sizeof(arr)], 0x00, 45);

	unsigned char desired_crc[2];
	desired_crc[0] = 0x80;
	desired_crc[1] = 0xaf;

	IS_TRUE(checksum_isok(digest, desired_crc));
}

void
test_crc_isok1()
{
	DigestType digest;
	unsigned char arr[] = {0xfe, 0x33, 0x8c, 0x01, 0x00, 0xfd, 0x06,
		0x48, 0x65, 0x6c, 0x6c, 0x6f};

	memcpy(digest.digest, arr, sizeof(arr));
	memset(&digest.digest[sizeof(arr)], 0x00, 45);

	digest.len = 59;

	digest.digest[digest.len - 2] = 0x80;
	digest.digest[digest.len - 1] = 0xaf;

	IS_TRUE(crc_isok(digest, status_text::CrcExtra));
}

int
main(int argc, char ** argv)
{
	// Test 'checksum'
	test_checksum1();
	test_checksum2();

	// Test 'crcIsOk'
	test_crc_isok1();

	exit(EXIT_SUCCESS);
}