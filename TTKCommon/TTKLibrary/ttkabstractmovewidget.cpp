#include "ttkabstractmovewidget.h"
#include "ttkglobalhelper.h"

TTKAbstractMoveWidget::TTKAbstractMoveWidget(QWidget *parent)
    : TTKAbstractMoveWidget(true, parent)
{

}

TTKAbstractMoveWidget::TTKAbstractMoveWidget(bool transparent, QWidget *parent)
    : QWidget(parent),
      m_blockOption(false),
      m_shadowOption(true),
      m_mouseLeftPressed(false)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, transparent);
}

void TTKAbstractMoveWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_shadowOption)
    {
        QPainter painter(this);
        TTK::setBorderShadow(this, &painter);
    }
}

void TTKAbstractMoveWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if(event->button() == Qt::LeftButton && !m_blockOption)
    {
        m_mouseLeftPressed = true;
    }

    m_mousePressedAt = QtMouseGlobalPos(event);
}

void TTKAbstractMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(!m_mouseLeftPressed)
    {
        event->ignore();
        return;
    }

    const int xpos = QtMouseGlobalX(event) - m_mousePressedAt.x();
    const int ypos = QtMouseGlobalY(event) - m_mousePressedAt.y();
    m_mousePressedAt = QtMouseGlobalPos(event);
    move(x() + xpos, y() + ypos);
}

void TTKAbstractMoveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    m_mousePressedAt = QtMouseGlobalPos(event);
    m_mouseLeftPressed = false;
}
