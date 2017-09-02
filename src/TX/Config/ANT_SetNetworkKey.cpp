#include <TX/Config/ANT_SetNetworkKey.h>

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define SET_NETWORK_KEY_LENGTH  0x09

SetNetworkKey::SetNetworkKey() : AntRequest(SET_NETWORK_KEY) {
    memset(_key, 0, NETWORK_KEY_SIZE);
}

void SetNetworkKey::setNetwork(uint8_t network) {
    _network = network;
}

void SetNetworkKey::setKey(uint8_t* key) {
    memcpy(_key, key, NETWORK_KEY_SIZE);
}

void SetNetworkKey::setKeyByte(uint8_t byte, uint8_t pos) {
    _key[pos] = byte;
}

uint8_t SetNetworkKey::getNetwork() {
    return _network;
}

void SetNetworkKey::getKey(uint8_t* arr) {
    memcpy(arr, _key, NETWORK_KEY_SIZE);
}

uint8_t SetNetworkKey::getKeyByte(uint8_t pos) {
    return _key[pos];
}

uint8_t SetNetworkKey::getDataLength() {
    return SET_NETWORK_KEY_LENGTH;
}

uint8_t SetNetworkKey::getData(uint8_t pos) {
    if (pos == 0) {
        return _network;
    } else {
        return _key[pos - 1];
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t SetNetworkKey::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE