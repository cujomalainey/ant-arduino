#ifndef ANT_STARTUPMESSAGE_h
#define ANT_STARTUPMESSAGE_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Startup message
 */
class StartUpMessage : public AntResponse {
public:
    StartUpMessage();
    uint8_t getMessage();

    static const uint8_t MSG_ID = START_UP_MESSAGE;
};

#endif // ANT_STARTUPMESSAGE_h