#include <TX/Config/ANT_TransmitPower.h>

#include <ANT_private_defines.h>


TransmitPower::TransmitPower() : AntRequest(TRANSMIT_POWER) {

}

TransmitPower::TransmitPower(uint8_t power) : AntRequest(TRANSMIT_POWER) {
    setTxPower(power);
}

void TransmitPower::setTxPower(uint8_t power) {
    _power = power;
}

uint8_t TransmitPower::getTxPower() {
    return _power;
}

uint8_t TransmitPower::getData(uint8_t pos) {
    if (pos == 0) {
        return 0;
    } else {
        return _power;
    }
}

uint8_t TransmitPower::getDataLength() {
    return TRANSMIT_POWER_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t TransmitPower::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE