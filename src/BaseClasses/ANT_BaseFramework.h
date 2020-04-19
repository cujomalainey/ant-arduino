#ifndef ANT_BASEFRAMEWORK_h
#define ANT_BASEFRAMEWORK_h

#ifdef UNIT_TEST
#include "Util/Testing.h"
#elif defined(ARDUINO)
#include "Arduino.h"
#elif defined(__MBED__)
#include "mbed.h"
#elif defined(__ZEPHYR__)
#include <zephyr.h>
#include <string.h>
#elif defined(ESP_PLATFORM)
#include "esp_system.h"
#include <string.h>
#endif

#endif // ANT_BASEFRAMEWORK_h
