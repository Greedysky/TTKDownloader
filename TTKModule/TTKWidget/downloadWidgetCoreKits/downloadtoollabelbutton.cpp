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
