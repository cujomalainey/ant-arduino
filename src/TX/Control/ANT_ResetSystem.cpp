#include <TX/Control/ANT_ResetSystem.h>

#include <ANT_defines.h>

#define RESET_SYSTEM_LENGTH  0x01

ResetSystem::ResetSystem() : AntRequest(RESET_SYSTEM) {

}

uint8_t ResetSystem::getDataLength() {
    return RESET_SYSTEM_LENGTH;
}

uint8_t ResetSystem::getData(uint8_t pos) {
    return 0;
}