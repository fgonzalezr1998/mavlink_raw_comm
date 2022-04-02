#ifndef MAVLINK_ENCODER__DIGEST_CPP
#define MAVLINK_ENCODER__DIGEST_CPP


namespace mavlink_encoder
{
  enum {
    MAXLENDIGEST = 263,
  };

  typedef struct DigestType DigestType;
  struct DigestType
  {
	public:
    unsigned char digest[MAXLENDIGEST];
    int len;

    void print_digest()
    {
      for (int i = 0; i < len; i++)
      {
        printf("%02x", digest[i]);
      }
      printf("\n");
    }

		bool operator==(const DigestType & d)
		{
			return digest_equals(*this, d);
		}

	private:
		bool digest_equals(const DigestType & d1, const DigestType & d2)
		{
			if (d1.len != d2.len)
				return false;

			for (int i = 0; i < d1.len; i++)
			{
				if (d1.digest[i] != d2.digest[i])
				{
					return false;
				}
			}

			return true;
		}
  };
}

#endif