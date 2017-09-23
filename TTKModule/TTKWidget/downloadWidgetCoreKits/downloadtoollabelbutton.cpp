#include "downloadtoollabelbutton.h"
#include "downloadbackgroundmanager.h"
#include "downloaduiobject.h"

#include <QPainter>

DownloadToolLabelButton::DownloadToolLabelButton(QWidget *parent)
    : QToolButton(parent)
{
    setFixedHeight(25);
    setStyleSheet(DownloadUIObject::MToolButtonStyle03 + DownloadUIObject:: MToolButtonStyle01);

    m_enterIn = false;
}

QString DownloadToolLabelButton::getClassName()
{
    return staticMetaObject.className();
}

void DownloadToolLabelButton::setLabelText(const QString &text)
{
    m_text = text;
}

void DownloadToolLabelButton::setLabelIcon(const QString &icon)
{
    m_icon = icon;
}

void DownloadToolLabelButton::enterEvent(QEvent *event)
{
    QToolButton::enterEvent(event);
    m_enterIn = true;
    update();
}

void DownloadToolLabelButton::leaveEvent(QEvent *event)
{
    QToolButton::leaveEvent(event);
    m_enterIn = false;
    update();
}

void DownloadToolLabelButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);

    QPainter painter(this);

    if(m_enterIn)
    {
        painter.fillRect(rect(), Qt::white);
    }

    QRect rt(5, 5, 15, 15);
    painter.fillRect(rt, M_BACKGROUND_PTR->getMBackgroundColor());
    painter.drawPixmap(rt, QPixmap(m_icon));

    if(!m_text.isEmpty())
    {
        painter.drawText(QRect(25, 0, width() - 25, height()), Qt::AlignLeft | Qt::AlignVCenter, m_text);
    }
}



DownloadSpeedToolLabelButton::DownloadSpeedToolLabelButton(QWidget *parent)
    : QToolButton(parent)
{
    setFixedHeight(25);
    setStyleSheet(DownloadUIObject::MToolButtonStyle03 + DownloadUIObject:: MToolButtonStyle01);

    m_enterIn = false;
}

QString DownloadSpeedToolLabelButton::getClassName()
{
    return staticMetaObject.className();
}

void DownloadSpeedToolLabelButton::setLabelText(const QString &up, const QString &down)
{
    m_textUp = up;
    m_textDown = down;
}

void DownloadSpeedToolLabelButton::enterEvent(QEvent *event)
{
    QToolButton::enterEvent(event);
    m_enterIn = true;
    update();
}

void DownloadSpeedToolLabelButton::leaveEvent(QEvent *event)
{
    QToolButton::leaveEvent(event);
    m_enterIn = false;
    update();
}

void DownloadSpeedToolLabelButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);

    QPainter painter(this);

    if(m_enterIn)
    {
        painter.fillRect(rect(), Qt::white);
    }

    QPolygon pyup;
    pyup.append(QPoint(12, 19));
    pyup.append(QPoint(6, 13));
    pyup.append(QPoint(9, 13));
    pyup.append(QPoint(9, 6));
    pyup.append(QPoint(15, 6));
    pyup.append(QPoint(15, 13));
    pyup.append(QPoint(18, 13));

    painter.setPen(M_BACKGROUND_PTR->getMBackgroundColor());
    painter.setBrush(M_BACKGROUND_PTR->getMBackgroundColor());
    painter.drawPolygon(pyup);

    painter.setPen(Qt::black);
    if(!m_textDown.isEmpty())
    {
        painter.drawText(QRect(25, 0, width() - 25, height()), Qt::AlignLeft | Qt::AlignVCenter, m_textDown);
    }

    /////////////////////////////////////////////////////////////////////////////////
    QPolygon pydown;
    pydown.append(QPoint(97, 6));
    pydown.append(QPoint(90, 13));
    pydown.append(QPoint(94, 13));
    pydown.append(QPoint(94, 18));
    pydown.append(QPoint(100, 18));
    pydown.append(QPoint(100, 13));
    pydown.append(QPoint(104, 13));

    painter.setPen(M_BACKGROUND_PTR->getMBackgroundColor());
    painter.setBrush(M_BACKGROUND_PTR->getMBackgroundColor());
    painter.drawPolygon(pydown);

    painter.setPen(Qt::black);
    if(!m_textUp.isEmpty())
    {
        painter.drawText(QRect(110, 0, width() - 25, height()), Qt::AlignLeft | Qt::AlignVCenter, m_textUp);
    }
}
