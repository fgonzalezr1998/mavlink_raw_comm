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
        unsigned char digest[MAXLENDIGEST];
        int len;

        void print_digest()
        {
            for (int i = 0; i < len; i++)
            {
                printf("0x%02X/", digest[i]);
            }
            printf("\n");
        }
    };
}

#endif