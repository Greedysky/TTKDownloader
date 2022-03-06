#include "downloadclickedslider.h"

#include <QMouseEvent>

DownloadClickedSlider::DownloadClickedSlider(QWidget *parent)
    : DownloadClickedSlider(Qt::Horizontal, parent)
{

}

DownloadClickedSlider::DownloadClickedSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    m_mousePress = false;
    m_value = 0;
}

bool DownloadClickedSlider::event(QEvent *event)
{
    if(m_mousePress)
    {
        setValue(m_value);
    }
    return QSlider::event(event);
}

void DownloadClickedSlider::mousePressEvent(QMouseEvent *event)
{
    QSlider::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        m_mousePress = true;

        double pos;
        if(orientation() == Qt::Horizontal)
        {
            pos = event->pos().x()*1.0 / width();
            m_value = pos * (maximum() - minimum()) + minimum();
        }
        else
        {
            pos = event->pos().y()*1.0 / height();
            m_value = maximum() - pos * (maximum() - minimum());
        }
    }
}

void DownloadClickedSlider::mouseMoveEvent(QMouseEvent *event)
{
    QSlider::mouseMoveEvent(event);
    if(m_mousePress)
    {
        if(orientation() == Qt::Horizontal)
        {
            int x = event->pos().x();
            if((x >= 0) && (x <= width()))
            {
                double pos = event->pos().x()*1.0 / width();
                m_value = pos * (maximum() - minimum()) + minimum();
                setValue(m_value);
            }
            else if(x < 0)
            {
                m_value = minimum();
            }
            else
            {
                m_value = maximum();
            }
        }
        else
        {
            int y = event->pos().y();
            if((y >= 0) && (y <= height()))
            {
                double pos = event->pos().y()*1.0 / height();
                m_value = maximum() - pos * (maximum() - minimum());
                setValue(m_value);
            }
            else if(y < 0)
            {
                m_value = maximum();
            }
            else
            {
                m_value = minimum();
            }
        }
    }
}

void DownloadClickedSlider::mouseReleaseEvent(QMouseEvent *event)
{
    QSlider::mouseReleaseEvent(event);
    m_mousePress = false;
}
