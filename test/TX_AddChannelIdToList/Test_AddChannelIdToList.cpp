#include "unity.h"
#include "ANT.h"
#include "Util/Testing.h"

#ifdef UNIT_TEST

const uint8_t expectedOut[] = {0xA4, 6, 0x59, 2, 0x44, 0x33, 120, 34, 2, 214};
Stream mock_stream = Stream(NULL, expectedOut);
AntWithCallbacks ant = AntWithCallbacks();
AddChannelIdToList msg;

void test_constructors(void) {
    msg = AddChannelIdToList(2, 3344, 120, 34, 2);
    TEST_ASSERT_EQUAL_UINT8(2, msg.getChannel());
    TEST_ASSERT_EQUAL_UINT16(3344, msg.getDeviceNumber());
    TEST_ASSERT_EQUAL_UINT8(120, msg.getDeviceType());
    TEST_ASSERT_EQUAL_UINT8(34, msg.getTransmissionType());
    TEST_ASSERT_EQUAL_UINT8(2, msg.getListIndex());
}

void test_setChannel(void) {
    msg.setChannel(3);
    TEST_ASSERT_EQUAL_UINT8(3, msg.getChannel());
}

void test_setDeviceNumber(void) {
    msg.setDeviceNumber(0x4455);
    TEST_ASSERT_EQUAL_UINT16(0x4455, msg.getDeviceNumber());
}

void test_setDeviceType(void) {
    msg.setDeviceType(100);
    TEST_ASSERT_EQUAL_UINT8(100, msg.getDeviceType());
}

void test_setTransmisionType(void) {
    msg.setTransmissionType(12);
    TEST_ASSERT_EQUAL_UINT8(12, msg.getTransmissionType());
}

void test_getDataLength(void) {
    TEST_ASSERT_EQUAL_UINT8(6, msg.getDataLength());
}

void test_serialize(void) {
    // Asserts are in mock stream
    ant.begin(mock_stream);
    msg = AddChannelIdToList(2, 0x3344, 120, 34, 2);
    ant.send(msg);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_constructors);
    RUN_TEST(test_setChannel);
    RUN_TEST(test_setDeviceNumber);
    RUN_TEST(test_setDeviceType);
    RUN_TEST(test_setTransmisionType);
    RUN_TEST(test_getDataLength);
    RUN_TEST(test_serialize);
    UNITY_END();

    return 0;
}

#endif // UNIT_TEST