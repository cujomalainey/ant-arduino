#include <TX/Control/ANT_ResetSystem.h>

#include <ANT_private_defines.h>


ResetSystem::ResetSystem() : AntRequest(RESET_SYSTEM) {

}

uint8_t ResetSystem::getDataLength() {
    return RESET_SYSTEM_LENGTH;
}

uint8_t ResetSystem::getData(uint8_t pos) {
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ResetSystem::execute() {
    return 0;
}

#endif // NATIVE_API_AVAILABLE