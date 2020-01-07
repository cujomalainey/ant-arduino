/**
 * Copyright (c) 2017 Curtis Malainey. All rights reserved.
 *
 * This file is part of Ant-Arduino.
 *
 * Ant-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ant-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ant-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ANT_h
#define ANT_h

/* Arbitrary Data Definitions */
#include <ANT_defines.h>

/* Available Main Classes */
#include <MainClasses/ANT_ArduinoAnt.h>
#include <MainClasses/ANT_ArduinoAntWithCallbacks.h>
#include <MainClasses/ANT_MbedSerialAnt.h>
#include <MainClasses/ANT_MbedSerialAntWithCallbacks.h>
// #include <MainClasses/ANT_NativeAnt.h>
// #include <MainClasses/ANT_NativeAntWithCallbacks.h>

/* Messages */
#include <TX/ANT_messages.h>
#include <RX/ANT_messages.h>

#endif // ANT_h
