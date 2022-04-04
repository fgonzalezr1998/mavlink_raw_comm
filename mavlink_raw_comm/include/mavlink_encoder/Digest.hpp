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

#ifndef MAVLINK_ENCODER__DIGEST_CPP
#define MAVLINK_ENCODER__DIGEST_CPP


namespace mavlink_encoder
{
  enum {
    MAXLENDIGEST = 263,
  };

	/*
	 * @brief Struct to manage array of bytes that represent data of a
	 *	mavlink package encoded
	 */
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