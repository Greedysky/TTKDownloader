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

set_property(GLOBAL PROPERTY TTK_WIDGET_KITS_HEADER_FILES
  ${TTK_WIDGET_DIR}/downloadbackgroundlistwidget.h
  ${TTK_WIDGET_DIR}/downloadbackgroundpopwidget.h
  ${TTK_WIDGET_DIR}/downloadbackgroundremotewidget.h
  ${TTK_WIDGET_DIR}/downloadbackgroundskindialog.h
  ${TTK_WIDGET_DIR}/downloadfunctionlistwidget.h
  ${TTK_WIDGET_DIR}/downloadfuntionanimationwidget.h
  ${TTK_WIDGET_DIR}/downloadglobalhotkeyedit.h
  ${TTK_WIDGET_DIR}/downloadhistoryrecordwidget.h
  ${TTK_WIDGET_DIR}/downloadlistitemwidget.h
  ${TTK_WIDGET_DIR}/downloadlistwidgets.h
  ${TTK_WIDGET_DIR}/downloadmessageaboutdialog.h
  ${TTK_WIDGET_DIR}/downloadnewfiledialog.h
  ${TTK_WIDGET_DIR}/downloadsettingwidget.h
  ${TTK_WIDGET_DIR}/downloadsystemtraymenu.h
  ${TTK_WIDGET_DIR}/downloadunits.h
)

set_property(GLOBAL PROPERTY TTK_WIDGET_KITS_SOURCE_FILES
  ${TTK_WIDGET_DIR}/downloadbackgroundlistwidget.cpp
  ${TTK_WIDGET_DIR}/downloadbackgroundpopwidget.cpp
  ${TTK_WIDGET_DIR}/downloadbackgroundremotewidget.cpp
  ${TTK_WIDGET_DIR}/downloadbackgroundskindialog.cpp
  ${TTK_WIDGET_DIR}/downloadfunctionlistwidget.cpp
  ${TTK_WIDGET_DIR}/downloadfuntionanimationwidget.cpp
  ${TTK_WIDGET_DIR}/downloadglobalhotkeyedit.cpp
  ${TTK_WIDGET_DIR}/downloadhistoryrecordwidget.cpp
  ${TTK_WIDGET_DIR}/downloadlistitemwidget.cpp
  ${TTK_WIDGET_DIR}/downloadlistwidgets.cpp
  ${TTK_WIDGET_DIR}/downloadmessageaboutdialog.cpp
  ${TTK_WIDGET_DIR}/downloadnewfiledialog.cpp
  ${TTK_WIDGET_DIR}/downloadsettingwidget.cpp
  ${TTK_WIDGET_DIR}/downloadsystemtraymenu.cpp
  ${TTK_WIDGET_DIR}/downloadunits.cpp
)
