#include <iostream>
#include "status_text/StatusTextEncoder.hpp"

namespace status_text
{
    StatusTextEncoder::StatusTextEncoder()
    {
        std::cout << "I'm status text encoder\n";
    }

    StatusTextEncoder* StatusTextEncoder::getInstance()
    {
        static StatusTextEncoder *encoder = new StatusTextEncoder();
        return encoder;
    }    

    void StatusTextEncoder::composePayload(const std::string & msg, const StatusSeverity & severity)
    {
        std::cout << "Compose Payload!\n";
    }
}