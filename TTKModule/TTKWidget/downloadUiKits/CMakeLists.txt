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

set_property(GLOBAL PROPERTY TTK_WIDGET_UI_KITS_HEADER_FILES
  ${TTK_WIDGET_UI_DIR}/downloadfunctionuiobject.h
  ${TTK_WIDGET_UI_DIR}/downloadtinyuiobject.h
  ${TTK_WIDGET_UI_DIR}/downloaduiobject.h
)

set_property(GLOBAL PROPERTY TTK_UI_FILES
  ${TTK_WIDGET_UI_DIR}/downloadapplication.ui
  ${TTK_WIDGET_UI_DIR}/downloadbackgroundskindialog.ui
  ${TTK_WIDGET_UI_DIR}/downloadcolordialog.ui
  ${TTK_WIDGET_UI_DIR}/downloadmessageaboutdialog.ui
  ${TTK_WIDGET_UI_DIR}/downloadmessagebox.ui
  ${TTK_WIDGET_UI_DIR}/downloadnewfiledialog.ui
  ${TTK_WIDGET_UI_DIR}/downloadsettingwidget.ui
)
