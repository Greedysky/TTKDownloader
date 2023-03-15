#include "ttkabstractmovewidget.h"
#include "ttkglobalhelper.h"

#include <QBoxLayout>

TTKAbstractMoveWidget::TTKAbstractMoveWidget(QWidget *parent)
    : TTKAbstractMoveWidget(true, parent)
{

}

TTKAbstractMoveWidget::TTKAbstractMoveWidget(bool transparent, QWidget *parent)
    : QWidget(parent),
      m_moveOption(false),
      m_showShadow(true),
      m_leftButtonPress(false)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, transparent);
}

void TTKAbstractMoveWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_showShadow)
    {
        QPainter painter(this);
        TTK::setBorderShadow(this, &painter);
    }
}

void TTKAbstractMoveWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if(event->button() == Qt::LeftButton && !m_moveOption)
    {
        m_leftButtonPress = true;
    }

    m_pressAt = QtMouseGlobalPos(event);
}

void TTKAbstractMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(!m_leftButtonPress )
    {
        event->ignore();
        return;
    }

    const int xpos = QtMouseGlobalX(event) - m_pressAt.x();
    const int ypos = QtMouseGlobalY(event) - m_pressAt.y();
    m_pressAt = QtMouseGlobalPos(event);
    move(x() + xpos, y() + ypos);
}

void TTKAbstractMoveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    m_pressAt = QtMouseGlobalPos(event);
    m_leftButtonPress = false;
}
