/**
 * Represents a BurstTransferData message
 */
class BurstTransferData : public AntRxDataResponse {
public:
    BurstTransferData();
    /**
     * Returns source channel
     */
    uint8_t getChanneNumber();
    /**
     * Returns sepcified byte of data from payload
     */
    uint8_t getData(uint8_t index);
    uint8_t getExtendedDataLength();
    uint8_t getExtendedData(uint8_t index);

    static const uint8_t MSG_ID = BURST_TRANSFER_DATA;
};