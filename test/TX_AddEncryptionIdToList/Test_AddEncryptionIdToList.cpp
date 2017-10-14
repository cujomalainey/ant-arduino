#include "unity.h"
#include "ANT.h"
#include "Util/Testing.h"

#ifdef UNIT_TEST

const uint8_t expectedOut[] = {0xA4, 6, 0x59, 1, 0x78, 0x56, 0x34, 0x12, 3, 241};
Stream mock_stream = Stream(NULL, expectedOut);
AntWithCallbacks ant = AntWithCallbacks();
AddEncryptionIdToList msg;

void test_constructors(void) {
    msg = AddEncryptionIdToList(1, 0x12345678, 3);
    TEST_ASSERT_EQUAL_UINT8(1, msg.getChannel());
    TEST_ASSERT_EQUAL_UINT32(0x12345678, msg.getEncryptionId());
    TEST_ASSERT_EQUAL_UINT8(3, msg.getListIndex());
}

void test_setChannel(void) {
    msg.setChannel(3);
    TEST_ASSERT_EQUAL_UINT8(3, msg.getChannel());
}

void test_setEncryptionId(void) {
    msg.setEncryptionId(0x11223344);
    TEST_ASSERT_EQUAL_UINT16(0x11223344, msg.getEncryptionId());
}

void test_getDataLength(void) {
    TEST_ASSERT_EQUAL_UINT8(6, msg.getDataLength());
}

void test_serialize(void) {
    // Asserts are in mock stream
    ant.begin(mock_stream);
    msg = AddEncryptionIdToList(1, 0x12345678, 3);
    ant.send(msg);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_constructors);
    RUN_TEST(test_setEncryptionId);
    RUN_TEST(test_getDataLength);
    RUN_TEST(test_serialize);
    UNITY_END();

    return 0;
}

#endif // UNIT_TEST