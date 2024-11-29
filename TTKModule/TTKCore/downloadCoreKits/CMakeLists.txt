# ***************************************************************************
# * This file is part of the TTK Downloader project
# * Copyright (C) 2015 - 2024 Greedysky Studio
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

set_property(GLOBAL PROPERTY TTK_CORE_KITS_HEADER_FILES
  ${TTK_CORE_DIR}/downloadbackgroundconfigmanager.h
  ${TTK_CORE_DIR}/downloadbackgroundmanager.h
  ${TTK_CORE_DIR}/downloadbreakpointconfigmanager.h
  ${TTK_CORE_DIR}/downloadconfigmanager.h
  ${TTK_CORE_DIR}/downloadextractwrapper.h
  ${TTK_CORE_DIR}/downloadhotkeymanager.h
  ${TTK_CORE_DIR}/downloadlistconfigmanager.h
  ${TTK_CORE_DIR}/downloadobject.h
  ${TTK_CORE_DIR}/downloadotherdefine.h
  ${TTK_CORE_DIR}/downloadrecordconfigmanager.h
  ${TTK_CORE_DIR}/downloadruntimemanager.h
  ${TTK_CORE_DIR}/downloadsettingmanager.h
)

set_property(GLOBAL PROPERTY TTK_CORE_KITS_SOURCE_FILES
  ${TTK_CORE_DIR}/downloadbackgroundconfigmanager.cpp
  ${TTK_CORE_DIR}/downloadbackgroundmanager.cpp
  ${TTK_CORE_DIR}/downloadbreakpointconfigmanager.cpp
  ${TTK_CORE_DIR}/downloadconfigmanager.cpp
  ${TTK_CORE_DIR}/downloadextractwrapper.cpp
  ${TTK_CORE_DIR}/downloadhotkeymanager.cpp
  ${TTK_CORE_DIR}/downloadlistconfigmanager.cpp
  ${TTK_CORE_DIR}/downloadrecordconfigmanager.cpp
  ${TTK_CORE_DIR}/downloadruntimemanager.cpp
)
