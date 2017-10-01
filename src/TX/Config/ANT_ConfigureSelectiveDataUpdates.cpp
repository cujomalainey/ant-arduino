#include <TX/Config/ANT_ConfigureSelectiveDataUpdates.h>

#include <ANT_private_defines.h>
ConfigureSelectiveDataUpdates::ConfigureSelectiveDataUpdates() : AntRequest(CONFIGURE_SELECTIVE_DATA_UPDATES) {

}

ConfigureSelectiveDataUpdates::ConfigureSelectiveDataUpdates(uint8_t channel) : AntRequest(CONFIGURE_SELECTIVE_DATA_UPDATES) {
    setChannelNumber(channel);
}

void ConfigureSelectiveDataUpdates::setChannelNumber(uint8_t channel) {
    _channel = channel;
}

void ConfigureSelectiveDataUpdates::setSDUMaskNumer(uint8_t maskNo) {
    _selectedData = (maskNo << 7) | (_selectedData & ~CONFIGURE_SELECTIVE_DATA_UPDATES_SDU_NUMBER_MASK);
}

void ConfigureSelectiveDataUpdates::setFilterAcknowledged(uint8_t filterBit) {
    _selectedData = (filterBit & CONFIGURE_SELECTIVE_DATA_UPDATES_FILTER_BIT_MASK) | (_selectedData & ~CONFIGURE_SELECTIVE_DATA_UPDATES_FILTER_BIT_MASK);
}

void ConfigureSelectiveDataUpdates::setDisableSDUOnChannel() {
    _selectedData = CONFIGURE_SELECTIVE_DATA_UPDATES_SDU_DISABLE;
}

uint8_t ConfigureSelectiveDataUpdates::getChannelNumber() {
    return _channel;
}

uint8_t ConfigureSelectiveDataUpdates::getSDUMaskNumer() {
    return _selectedData & CONFIGURE_SELECTIVE_DATA_UPDATES_SDU_NUMBER_MASK;
}

uint8_t ConfigureSelectiveDataUpdates::getFilterAcknowledged() {
    return _selectedData >> 7;
}

uint8_t ConfigureSelectiveDataUpdates::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else {
        return _selectedData;
    }
}

uint8_t ConfigureSelectiveDataUpdates::getDataLength() {
    return CONFIGURE_SELECTIVE_DATA_UPDATES_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE