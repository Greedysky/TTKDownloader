#ifndef TTKQTCOMPAT_H
#define TTKQTCOMPAT_H

/***************************************************************************
 * This file is part of the TTK Library Module project
 * Copyright (C) 2015 - 2024 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "ttkqtglobal.h"

/*! @brief The namespace of the qt compat function wrapper.
 * @author Greedysky <greedysky@163.com>
 */
namespace QtCompat
{
/// Font string width
#if TTK_QT_VERSION_CHECK(5,11,0)
#  define QtFontWidth(p, t) p.horizontalAdvance(t)
#else
#  define QtFontWidth(p, t) p.width(t)
#endif

/// Image byte count
#if TTK_QT_VERSION_CHECK(5,10,0)
#  define QtImageBytes(p) p.sizeInBytes()
#else
#  define QtImageBytes(p) p.byteCount()
#endif

/// Item text alignment
#if TTK_QT_VERSION_CHECK(6,4,0)
#  define QtItemSetTextAlignment(p, a) p->setTextAlignment(Qt::Alignment(a));
#else
#  define QtItemSetTextAlignment(p, a) p->setTextAlignment(a);
#endif

/// Container swap
#if TTK_QT_VERSION_CHECK(5,13,0)
#  define QtContainerSwap(p, i, j) p->swapItemsAt(i, j)
#else
#  define QtContainerSwap(p, i, j) p->swap(i, j)
#endif

/// Network error connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtNetworkErrorConnect(p, q, f, s) QObject::connect(p, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), q, s(f(QNetworkReply::NetworkError)))
#else
#  define QtNetworkErrorConnect(p, q, f, s) QObject::connect(p, SIGNAL(error(QNetworkReply::NetworkError)), q, s(f(QNetworkReply::NetworkError)))
#endif

/// Network error void connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtNetworkErrorVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), q, s(f()))
#else
#  define QtNetworkErrorVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(error(QNetworkReply::NetworkError)), q, s(f()))
#endif

/// Socket error connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtSocketErrorConnect(p, q, f, s) QObject::connect(p, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), q, s(f(QAbstractSocket::SocketError)))
#else
#  define QtSocketErrorConnect(p, q, f, s) QObject::connect(p, SIGNAL(error(QAbstractSocket::SocketError)), q, s(f(QAbstractSocket::SocketError)))
#endif

/// Socket error void connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtSocketErrorVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), q, s(f()))
#else
#  define QtSocketErrorVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(error(QAbstractSocket::SocketError)), q, s(f()))
#endif

/// Process error connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtProcessConnect(p, q, f, s) QObject::connect(p, SIGNAL(errorOccurred(QProcess::ProcessError)), q, s(f(QProcess::ProcessError)))
#else
#  define QtProcessConnect(p, q, f, s) QObject::connect(p, SIGNAL(error(QProcess::ProcessError)), q, s(f(QProcess::ProcessError)))
#endif

/// Process error void connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtProcessVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(errorOccurred(QProcess::ProcessError)), q, s(f()))
#else
#  define QtProcessVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(error(QProcess::ProcessError)), q, s(f()))
#endif

/// Button group connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtButtonGroupConnect(p, q, f, s) QObject::connect(p, SIGNAL(idClicked(int)), q, s(f(int)))
#else
#  define QtButtonGroupConnect(p, q, f, s) QObject::connect(p, SIGNAL(buttonClicked(int)), q, s(f(int)))
#endif

/// Button group void connect
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtButtonGroupVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(idClicked(int)), q, s(f()))
#else
#  define QtButtonGroupVoidConnect(p, q, f, s) QObject::connect(p, SIGNAL(buttonClicked(int)), q, s(f()))
#endif

/// Qt namespace
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtNamespace(p) Qt::p
#else
#  define QtNamespace(p) p
#endif

/// Lable pixmap
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtLablePixmap(p) p->pixmap(Qt::ReturnByValue)
#else
#  define QtLablePixmap(p) p->pixmap() ? *p->pixmap() : QPixmap();
#endif

/// String skip empty parts
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtSkipEmptyParts Qt::SkipEmptyParts
#else
#  define QtSkipEmptyParts QString::SkipEmptyParts
#endif

/// Event wheel
#if TTK_QT_VERSION_CHECK(5,15,0)
#  define QtWheelDelta(p) p->angleDelta().y()
#else
#  define QtWheelDelta(p) p->delta()
#endif

/// Event mouse
#if TTK_QT_VERSION_CHECK(6,0,0)
#  define QtMouseX(p) p->position().x()
#  define QtMouseY(p) p->position().y()
#  define QtMousePos(p) p->position()
#  define QtMouseGlobalX(p) p->globalPosition().x()
#  define QtMouseGlobalY(p) p->globalPosition().y()
#  define QtMouseGlobalPos(p) p->globalPosition().toPoint()
#else
#  define QtMouseX(p) p->x()
#  define QtMouseY(p) p->y()
#  define QtMousePos(p) p->pos()
#  define QtMouseGlobalX(p) p->globalX()
#  define QtMouseGlobalY(p) p->globalY()
#  define QtMouseGlobalPos(p) p->globalPos()
#endif

/// Event enter
#if TTK_QT_VERSION_CHECK(6,0,0)
#  define QtEnterEvent QEnterEvent
#else
#  define QtEnterEvent QEvent
#endif

/// Variant type
#if TTK_QT_VERSION_CHECK(6,0,0)
#  define QtVariantType(p) p.typeId()
#else
#  define QtVariantType(p) p.type()
#endif

/// KeySequence
#if TTK_QT_VERSION_CHECK(6,0,0)
#  define QtKeySequence(k, m) QKeySequence(QKeyCombination(m, k))
#else
#  define QtKeySequence(k, m) QKeySequence(k + m)
#endif

/// KeySequence data
#if TTK_QT_VERSION_CHECK(6,0,0)
#  define QtKeyCombine(p) p.toCombined()
#else
#  define QtKeyCombine(p) p
#endif
}

#endif // TTKQTCOMPAT_H
