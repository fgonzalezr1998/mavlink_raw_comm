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
    StatusTextEncoder();
    // Not should be clonable:
    StatusTextEncoder(StatusTextEncoder &other) = delete;

    static StatusTextEncoder* getInstance();

    void composePayload(const std::string & msg, 
      const StatusSeverity & severity, int seq_n, mavlink_encoder::DigestType * out_digest);

    // Not should be assignable
    void operator=(const StatusTextEncoder &) = delete;
};

}   // end namespace status_text

#endif