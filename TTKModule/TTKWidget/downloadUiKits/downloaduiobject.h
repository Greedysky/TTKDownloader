#ifndef DOWNLOADUIOBJECT_H
#define DOWNLOADUIOBJECT_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2023 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "ttkglobal.h"

/*! @brief The namespace of the application ui object.
 * @author Greedysky <greedysky@163.com>
 */
namespace TTK
{
    namespace UI
    {
		///Color
        static const QString ColorStyle01 = " \
            color:rgb(230, 115, 0);";

        static const QString ColorStyle02 = " \
            color:#888888;";

        static const QString ColorStyle03 = " \
            color:#80B7F1;";

		///Background
        static const QString BackgroundStyle01 = " \
            background-color:transparent;"
#ifdef Q_OS_UNIX
            + QString(" border-style:falt;")
#endif
            ;

		///ToolButton
        static const QString ToolButtonStyle01 = " \
            QToolButton{ background-color:transparent;}";

        static const QString ToolButtonStyle02 = " \
            QToolButton{ border:none;}";

        static const QString ToolButtonStyle03 = ToolButtonStyle01 + ToolButtonStyle02 + " \
            QToolButton::hover{ background-color:rgba(255, 255, 255, 20);}";

        static const QString ToolButtonStyle04 = ToolButtonStyle01 + " \
            QToolButton::menu-indicator{ image:None;}";

        static const QString ToolButtonStyle05 = " \
            QToolButton{ border:1px solid #777777; background:#FFFFFF; color:#555555;} \
            QToolButton::hover{ border:1px solid #444444; color:#222222;} \
            QToolButton::disabled{ color:#999999;}";

		///PushButton
        static const QString PushButtonStyle01 = " \
            QPushButton{ background-color:transparent;  " +
#ifdef Q_OS_UNIX
            QString("border-style:falt;") +
#endif
            QString("}");

        static const QString PushButtonStyle02 = PushButtonStyle01 + " \
            QPushButton{ border-none;}";

        static const QString PushButtonStyle03 = " \
            QPushButton{ border:1px solid #AAAAAA; background:#FFFFFF; color:#777777;} \
            QPushButton::hover{ border:1px solid #555555; color:#444444;} \
            QPushButton::disabled{ color:#999999;}";

		///RadioButton
        static const QString RadioButtonStyle01 = " \
            QRadioButton{ background-color:transparent;} \
            QRadioButton::indicator::unchecked{ image:url(:/control/btn_radioButton_unchecked);} \
            QRadioButton::checked { color:rgb(230, 115, 0);} \
            QRadioButton::indicator:checked { image:url(:/control/btn_radiobutton_checked);}";

		///CheckBox
        static const QString CheckBoxStyle01 = " \
            QCheckBox{ background-color:transparent;} \
            QCheckBox::indicator::unchecked{ image:url(:/control/btn_checkBox_unchecked);} \
            QCheckBox::checked{ color:rgb(230, 115, 0);} \
            QCheckBox::indicator:checked { image:url(:/control/btn_checkBox_checked);}";

		///ScrollBar
        static const QString ScrollBarStyle01 = " \
            QScrollBar{ background:#FFFFFF; width:8px; padding-top:0px; padding-bottom:0px;} \
            QScrollBar::handle:vertical{ border-radius:4px; background:#CFCFCF; min-height: 30px;} \
            QScrollBar::handle:vertical::disabled{ background:#DBDBDB;} \
            QScrollBar::handle:vertical:hover{ background:#BBBBBB;} \
            QScrollBar::add-line, QScrollBar::sub-line{ background:none; border:none;} \
            QScrollBar::add-page, QScrollBar::sub-page{ background:none;}";

        static const QString ScrollBarStyle02 = ScrollBarStyle01 + " \
            QScrollBar{ background:transparent;}";

		///LineEdit
        static const QString LineEditStyle01 = " \
            QLineEdit{ font-size:12px; color:#666666; font-weight:normal; border:1px solid gray;} \
            QLineEdit::hover{ border:1px solid rgb(22, 154, 243);} \
            QLineEdit::disabled{ color:#BBBBBB;}";

		///Menu
        static const QString MenuStyle01 = " \
            QMenu{ padding:4px;} \
            QMenu::icon{ margin-left:10px;} \
            QMenu::right-arrow{ background: url(:/tiny/lb_arrow_up_normal);} \
            QMenu::item{ color:#666666; padding:5px 30px 5px 30px; border:1px solid transparent;} \
            QMenu::item:disabled{ color:#AAAAAA;} \
            QMenu::item:selected{ color:white; background: rgb(112, 56, 197);} \
            QMenu::separator{ height:1px; background:#DDDDDD; margin-top:1px; margin-bottom:1px;}" +
#if TTK_QT_VERSION_CHECK(5,12,0)
            QString("QMenu::item{ padding:6px 30px 6px 10px; } "
                    "QMenu::item::icon{ padding:6px 30px 6px 10px; }") +
#endif
            QString();

        static const QString MenuStyle02 = MenuStyle01 + " \
            QMenu{ background:rgba(255, 255, 255, 235);}";

        static const QString MenuStyle03 = MenuStyle01 + " \
            QMenu{ border:none; background:rgba(0, 0, 0, 210); border-radius:4px;} \
            QMenu::item{ color:#BBBBBB;} \
            QMenu::item:disabled{ color:#555555;} \
            QMenu::item:selected{ background:rgba(0, 0, 0, 200);} \
            QMenu::separator{ background:#BBBBBB;}";

		///Slider
        static const QString SliderStyle01 = " \
            QSlider::groove:vertical{ background: qlineargradient(x1:0, y1:0, x2:0, y2:1, \
            stop:0 #B5B4B4, stop:1 #FCFCFC); width:3px;} \
            QSlider::handle:vertical{ border-image:url(:/control/lb_slider_handle_normal); \
            height:21px; margin-left:-8px; margin-right:-8px;} \
            QSlider::handle:vertical:disabled{ border-image:url(:/control/lb_slider_disable);} \
            QSlider::handle:vertical:hover{ border-image:url(:/control/lb_slider_handle_hover); border:none;}";

		///ComboBox
        static const QString ComboBoxStyle01 = " \
            QComboBox{ border: 1px solid gray;} \
            QComboBox::hover{ border: 1px solid rgb(22, 154, 243);} \
            QComboBox::drop-down{ subcontrol-origin:padding; \
            subcontrol-position:top right; width:20px; border-left-width:1px; \
            border-left-color:darkgray; border-left-style:solid;} \
            QComboBox::down-arrow{ image:url(:/usermanager/btn_down_arrow);}";

		///TableWidget
        static const QString TableWidgetStyle01 =
#if defined Q_OS_UNIX && !TTK_QT_VERSION_CHECK(5,7,0) //Fix linux selection-background-color stylesheet bug
            "QTableWidget::item:selected{ background:rgba(20, 20, 20, 20); }";
#else
            "QTableWidget{ selection-background-color:rgba(20, 20, 20, 20); }";
#endif

		///ProgressBar
        static const QString ProgressBar01 = " \
            QProgressBar{ border:none; background:rgb(210, 225, 240); text-align:center;} \
            QProgressBar::chunk{ background:rgb(60, 140, 220);}";

		///ItemView
        static const QString ItemView01 = " \
            QAbstractItemView::item { height:20px; }";

    }
}

#endif // DOWNLOADUIOBJECT_H
