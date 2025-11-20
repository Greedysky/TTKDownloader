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

cmake_minimum_required(VERSION 3.18.0)

project(TTKExtras)

set(HEADER_FILES
  qshortcut/qglobalshortcut.h
  qshortcut/qglobalshortcut_p.h
  qjson/json.h
  qjson/QJsonArray.h
  qjson/QJsonDocument.h
  qjson/QJsonDummy.h
  qjson/QJsonObject.h
  qjson/QJsonParseError.h
  qjson/QJsonValue.h
  qjson/QJsonValueRef.h
  qjson/QJsonParser.h
  qjson/QJsonRoot.h
)

set(SOURCE_FILES
  qshortcut/qglobalshortcut.cpp
  qjson/QJsonArray.cpp
  qjson/QJsonDocument.cpp
  qjson/QJsonDummy.cpp
  qjson/QJsonObject.cpp
  qjson/QJsonParseError.cpp
  qjson/QJsonValue.cpp
  qjson/QJsonValueRef.cpp
  qjson/QJsonParser.cpp
)

if(WIN32)
  list(APPEND SOURCE_FILES qshortcut/qglobalshortcut_win.cpp ${PROJECT_NAME}.rc)
elseif(APPLE)
  set(MACOS_VERSION "unknown")
  execute_process(COMMAND /usr/libexec/PlistBuddy -c "Print ProductVersion" /System/Library/CoreServices/SystemVersion.plist OUTPUT_VARIABLE MACOS_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "Detected macOS version: ${MACOS_VERSION}")

  # macOS version greater than 10.5 use qglobalshortcut_osx.cpp
  # see https://leopard-adc.pepas.com/documentation/Carbon/Reference/KeyboardLayoutServices/Reference/reference.html
  if(MACOS_VERSION VERSION_GREATER_EQUAL "10.5")
    list(APPEND SOURCE_FILES qshortcut/qglobalshortcut_osx.cpp)
  else()
    list(APPEND SOURCE_FILES qshortcut/qglobalshortcut_mac.cpp)
  endif()

  # qglobalshortcut_mac.cpp needs this.
  # Notice, it cannot work on recent macOS versions,
  # so either additional implementation is needed, using
  # modern API, or at least a dummy fallback.
  list(APPEND QT_LINK_LIBS "-framework Carbon")
else()
  list(APPEND SOURCE_FILES qshortcut/qglobalshortcut_x11.cpp)
endif()

if(TTK_QT_VERSION VERSION_EQUAL "4")
  qt4_wrap_cpp(MOC_FILES ${HEADER_FILES})

  list(APPEND QT_LINK_LIBS ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
elseif(TTK_QT_VERSION VERSION_EQUAL "5")
  qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})

  if(UNIX)
    list(APPEND QT_LINK_LIBS Qt5::X11Extras)
  endif()

  list(APPEND QT_LINK_LIBS Qt5::Core Qt5::Gui)
elseif(TTK_QT_VERSION VERSION_EQUAL "6")
  qt6_wrap_cpp(MOC_FILES ${HEADER_FILES})

  list(APPEND QT_LINK_LIBS Qt6::Core Qt6::Gui)
endif()

if(TTK_BUILD_SHARED)
  add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${MOC_FILES})
else()
  add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${MOC_FILES})
endif()
target_link_libraries(${PROJECT_NAME} ${QT_LINK_LIBS})
