# ***************************************************************************
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2025 Greedysky Studio
#
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or
# * (at your option) any later version.
#
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
#
# * You should have received a copy of the GNU General Public License along
# * with this program; If not, see <http://www.gnu.org/licenses/>.
# ***************************************************************************

cmake_minimum_required(VERSION 3.0.0)

set_property(GLOBAL PROPERTY TTK_CORE_NETWORK_KITS_HEADER_FILES
  ${TTK_CORE_NETWORK_DIR}/downloadabstractnetwork.h
  ${TTK_CORE_NETWORK_DIR}/downloadabstractrequest.h
  ${TTK_CORE_NETWORK_DIR}/downloaddatasourcerequest.h
  ${TTK_CORE_NETWORK_DIR}/downloadnetworkspeedthread.h
  ${TTK_CORE_NETWORK_DIR}/downloadnetworkthread.h
  ${TTK_CORE_NETWORK_DIR}/downloadqueuerequest.h
  ${TTK_CORE_NETWORK_DIR}/downloadthread.h
  ${TTK_CORE_NETWORK_DIR}/downloadthreadmanager.h
  ${TTK_CORE_NETWORK_DIR}/downloadthunderskinrequest.h
  ${TTK_CORE_NETWORK_DIR}/downloadurlencoder.h
)

set_property(GLOBAL PROPERTY TTK_CORE_NETWORK_KITS_SOURCE_FILES
  ${TTK_CORE_NETWORK_DIR}/downloadabstractrequest.cpp
  ${TTK_CORE_NETWORK_DIR}/downloaddatasourcerequest.cpp
  ${TTK_CORE_NETWORK_DIR}/downloadnetworkspeedthread.cpp
  ${TTK_CORE_NETWORK_DIR}/downloadnetworkthread.cpp
  ${TTK_CORE_NETWORK_DIR}/downloadqueuerequest.cpp
  ${TTK_CORE_NETWORK_DIR}/downloadthread.cpp
  ${TTK_CORE_NETWORK_DIR}/downloadthreadmanager.cpp
  ${TTK_CORE_NETWORK_DIR}/downloadthunderskinrequest.cpp
  ${TTK_CORE_NETWORK_DIR}/downloadurlencoder.cpp
)
