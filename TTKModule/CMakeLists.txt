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

project(TTKCore)

add_subdirectory(TTKCore)
add_subdirectory(TTKWidget)

include_directories(${TTK_COMMON_DUMPER_DIR})

get_property(TTK_CORE_KITS_HEADERS GLOBAL PROPERTY "TTK_CORE_KITS_HEADERS")
get_property(TTK_CORE_NETWORK_KITS_HEADERS GLOBAL PROPERTY "TTK_CORE_NETWORK_KITS_HEADERS")
get_property(TTK_CORE_UTILS_KITS_HEADERS GLOBAL PROPERTY "TTK_CORE_UTILS_KITS_HEADERS")
get_property(TTK_WIDGET_CORE_KITS_HEADERS GLOBAL PROPERTY "TTK_WIDGET_CORE_KITS_HEADERS")
get_property(TTK_WIDGET_REMOTE_KITS_HEADERS GLOBAL PROPERTY "TTK_WIDGET_REMOTE_KITS_HEADERS")
get_property(TTK_WIDGET_UI_KITS_HEADERS GLOBAL PROPERTY "TTK_WIDGET_UI_KITS_HEADERS")
get_property(TTK_WIDGET_KITS_HEADERS GLOBAL PROPERTY "TTK_WIDGET_KITS_HEADERS")

set(HEADER_FILES
  ${TTK_CORE_KITS_HEADERS}
  ${TTK_CORE_NETWORK_KITS_HEADERS}
  ${TTK_CORE_UTILS_KITS_HEADERS}
  ${TTK_WIDGET_CORE_KITS_HEADERS}
  ${TTK_WIDGET_REMOTE_KITS_HEADERS}
  ${TTK_WIDGET_UI_KITS_HEADERS}
  ${TTK_WIDGET_KITS_HEADERS}
  ${TTK_MODULE_DIR}/downloadapplication.h
  ${TTK_MODULE_DIR}/downloadleftareawidget.h
  ${TTK_MODULE_DIR}/downloadtopareawidget.h
  ${TTK_MODULE_DIR}/downloadrightareawidget.h
  ${TTK_MODULE_DIR}/downloadbottomareawidget.h
  ${TTK_MODULE_DIR}/downloadapplicationmodule.h
)

get_property(TTK_CORE_KITS_SOURCES GLOBAL PROPERTY "TTK_CORE_KITS_SOURCES")
get_property(TTK_CORE_NETWORK_KITS_SOURCES GLOBAL PROPERTY "TTK_CORE_NETWORK_KITS_SOURCES")
get_property(TTK_CORE_UTILS_KITS_SOURCES GLOBAL PROPERTY "TTK_CORE_UTILS_KITS_SOURCES")
get_property(TTK_WIDGET_CORE_KITS_SOURCES GLOBAL PROPERTY "TTK_WIDGET_CORE_KITS_SOURCES")
get_property(TTK_WIDGET_REMOTE_KITS_SOURCES GLOBAL PROPERTY "TTK_WIDGET_REMOTE_KITS_SOURCES")
get_property(TTK_WIDGET_UI_KITS_SOURCES GLOBAL PROPERTY "TTK_WIDGET_UI_KITS_SOURCES")
get_property(TTK_WIDGET_KITS_SOURCES GLOBAL PROPERTY "TTK_WIDGET_KITS_SOURCES")

set(SOURCE_FILES
  ${TTK_CORE_KITS_SOURCES}
  ${TTK_CORE_NETWORK_KITS_SOURCES}
  ${TTK_CORE_UTILS_KITS_SOURCES}
  ${TTK_WIDGET_CORE_KITS_SOURCES}
  ${TTK_WIDGET_REMOTE_KITS_SOURCES}
  ${TTK_WIDGET_UI_KITS_SOURCES}
  ${TTK_WIDGET_KITS_SOURCES}
  ${TTK_MODULE_DIR}/downloadapplication.cpp
  ${TTK_MODULE_DIR}/downloadleftareawidget.cpp
  ${TTK_MODULE_DIR}/downloadtopareawidget.cpp
  ${TTK_MODULE_DIR}/downloadrightareawidget.cpp
  ${TTK_MODULE_DIR}/downloadbottomareawidget.cpp
  ${TTK_MODULE_DIR}/downloadapplicationmodule.cpp
)

get_property(UI_FILES GLOBAL PROPERTY "TTK_UIS")

if(WIN32)
  list(APPEND SOURCE_FILES ${PROJECT_NAME}.rc)
endif()

if(TTK_QT_VERSION VERSION_EQUAL "4")
  qt4_wrap_ui(UIC_FILES ${UI_FILES})
  qt4_wrap_cpp(MOC_FILES ${HEADER_FILES})

  if(TTK_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${UIC_FILES} ${MOC_FILES} ${HEADER_FILES})
  else()
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${UIC_FILES} ${MOC_FILES} ${HEADER_FILES})
  endif()

  list(APPEND QT4_LIBS ${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY} TTKLibrary TTKUi TTKExtras TTKDumper ttkzip zlib)
  if(WIN32)
    list(APPEND QT4_LIBS Iphlpapi)
  endif()
  
  if(${OPENSSL_DIR})
    if(WIN32)
      list(APPEND QT5_LIBS ${OPENSSL_DIR}/lib/libssl.a)
    else(UNIX)
      list(APPEND QT5_LIBS ${OPENSSL_DIR}/lib/libssl.so)
    endif()
  endif()

  target_link_libraries(${PROJECT_NAME} ${QT4_LIBS})
elseif(TTK_QT_VERSION VERSION_EQUAL "5")
  qt5_wrap_ui(UIC_FILES ${UI_FILES})
  qt5_wrap_cpp(MOC_FILES ${HEADER_FILES})

  if(TTK_BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${UIC_FILES} ${MOC_FILES} ${HEADER_FILES})
  else()
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${UIC_FILES} ${MOC_FILES} ${HEADER_FILES})
  endif()

  list(APPEND QT5_LIBS Qt5::Core Qt5::Network Qt5::Xml Qt5::Gui Qt5::Widgets TTKLibrary TTKUi TTKExtras TTKDumper ttkzip zlib)
  if(WIN32)
    list(APPEND QT5_LIBS Iphlpapi)
  endif()

  if(${OPENSSL_DIR})
    if(WIN32)
      list(APPEND QT5_LIBS ${OPENSSL_DIR}/lib/libssl.a)
    else(UNIX)
      list(APPEND QT5_LIBS ${OPENSSL_DIR}/lib/libssl.so)
    endif()
  endif()

  target_link_libraries(${PROJECT_NAME} ${QT5_LIBS})
endif()
