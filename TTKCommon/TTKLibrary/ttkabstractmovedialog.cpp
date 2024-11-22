#include "ttkabstractmovedialog.h"
#include "ttkglobalwrapper.h"

TTKAbstractMoveDialog::TTKAbstractMoveDialog(QWidget *parent)
    : TTKAbstractMoveDialog(true, parent)
{

}

TTKAbstractMoveDialog::TTKAbstractMoveDialog(bool transparent, QWidget *parent)
    : QDialog(parent),
      m_blockOption(false),
      m_shadowOption(true),
      m_mouseLeftPressed(false)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, transparent);
}

void TTKAbstractMoveDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    if(m_shadowOption)
    {
        QPainter painter(this);
        TTK::setBorderShadow(this, &painter);
    }
}

void TTKAbstractMoveDialog::mousePressEvent(QMouseEvent *event)
{
    QDialog::mousePressEvent(event);
    if(event->button() == Qt::LeftButton && !m_blockOption)
    {
        m_mouseLeftPressed = true;
    }

    m_mousePressedAt = QtMouseGlobalPos(event);
}

void TTKAbstractMoveDialog::mouseMoveEvent(QMouseEvent *event)
{
    QDialog::mouseMoveEvent(event);
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

void TTKAbstractMoveDialog::mouseReleaseEvent(QMouseEvent *event)
{
    QDialog::mouseReleaseEvent(event);
    m_mousePressedAt = QtMouseGlobalPos(event);
    m_mouseLeftPressed = false;
}
