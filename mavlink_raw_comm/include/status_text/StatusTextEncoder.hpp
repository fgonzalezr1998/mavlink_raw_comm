#include <string>
#include "mavlink_encoder/Digest.hpp"

#ifndef STATUS_TEXT__STATUS_TEXT_ENCODER_CPP
#define STATUS_TEXT__STATUS_TEXT_ENCODER_CPP

namespace status_text
{
enum StatusSeverity
{
  Emergency = 0,
  Alert,
  Critical,
  Error,
  Warning,
  Notice,
  Info,
  Debug
};

class StatusTextEncoder
{
public:
  // Not should be clonable:

  StatusTextEncoder(StatusTextEncoder &other) = delete;

  static StatusTextEncoder* getInstance();

  // Store on 'out_digest' DigestType with the statustext Payload
	// Returns true if everything was ok. Else, returns false

  bool composePayload(const std::string & msg, 
    const StatusSeverity & severity, int seq_n,
    mavlink_encoder::DigestType * out_digest);

  // Store on 'out_digest' DigestType with the statustext Header

  void composeHeader(int len_payload, int seq_n,
    int sys_id, int comp_id, mavlink_encoder::DigestType * out_digest);

  // Not should be assignable

  void operator=(const StatusTextEncoder &) = delete;

protected:
  StatusTextEncoder();

private:
  void string2Buffer(const std::string & text, char * buff);
};

}   // end namespace status_text

#endif