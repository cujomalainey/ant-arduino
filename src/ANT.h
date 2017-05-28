/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 * Updated and maintained by Curtis Malainey
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

/* Available Main Classes */
#include <MainClasses/ANT_Ant.h>

/* Available Messages */
// RX
// Data (RX)
#include <RX/Data/ANT_BroadcastData.cpp>

// Status (RX)
#include <RX/Status/ANT_AntVersion.h>
#include <RX/Status/ANT_AdvancedBurstCapabilitiesConfiguration.h>
#include <RX/Status/ANT_Capabilities.h>
#include <RX/Status/ANT_ChannelEventResponse.h>
#include <RX/Status/ANT_StartUpMessage.h>

// TX
// Config (TX)
#include <TX/Config/ANT_AssignChannel.h>
#include <TX/Config/ANT_ChannelId.h>
#include <TX/Config/ANT_ChannelPeriod.h>
#include <TX/Config/ANT_ChannelRfFrequency.h>
#include <TX/Config/ANT_SetNetworkKey.h>

// Control (TX)
#include <TX/Control/ANT_OpenChannel.h>
#include <TX/Control/ANT_RequestMessage.h>
#include <TX/Control/ANT_ResetSystem.h>

// Data (TX)
#include <TX/Data/ANT_BroadcastMsg.h>

#endif //ANT_h
