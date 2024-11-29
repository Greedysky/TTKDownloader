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

set_property(GLOBAL PROPERTY TTK_WIDGET_CORE_KITS_HEADER_FILES
  ${TTK_WIDGET_CORE_DIR}/downloadabstractmovedialog.h
  ${TTK_WIDGET_CORE_DIR}/downloadabstractmovewidget.h
  ${TTK_WIDGET_CORE_DIR}/downloadabstracttablewidget.h
  ${TTK_WIDGET_CORE_DIR}/downloadanimationstackedwidget.h
  ${TTK_WIDGET_CORE_DIR}/downloadcolordialog.h
  ${TTK_WIDGET_CORE_DIR}/downloadmessagebox.h
  ${TTK_WIDGET_CORE_DIR}/downloadtoollabelbutton.h
  ${TTK_WIDGET_CORE_DIR}/downloadtoolmenuwidget.h
  ${TTK_WIDGET_CORE_DIR}/downloadtransitionanimationlabel.h
  ${TTK_WIDGET_CORE_DIR}/downloadwidgetrenderer.h
)

set_property(GLOBAL PROPERTY TTK_WIDGET_CORE_KITS_SOURCE_FILES
  ${TTK_WIDGET_CORE_DIR}/downloadabstractmovedialog.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadabstractmovewidget.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadabstracttablewidget.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadanimationstackedwidget.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadcolordialog.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadmessagebox.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadtoollabelbutton.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadtoolmenuwidget.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadtransitionanimationlabel.cpp
  ${TTK_WIDGET_CORE_DIR}/downloadwidgetrenderer.cpp
)
