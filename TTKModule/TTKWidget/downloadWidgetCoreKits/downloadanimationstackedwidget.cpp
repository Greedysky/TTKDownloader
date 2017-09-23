#include "downloadanimationstackedwidget.h"
#include "downloadnumberdefine.h"

#include <QPixmap>

DownloadAnimationStackedWidget::DownloadAnimationStackedWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    m_isAnimating = false;
    m_currentValue = 0;
    m_currentIndex = 0;
    m_previousIndex = 0;

    m_animation = new QPropertyAnimation(this, QByteArray(), this);
    m_animation->setDuration(120*MT_MS);
    m_animation->setEasingCurve(QEasingCurve::Linear);
    m_animation->setStartValue(0);
    m_animation->setEndValue(0);
    connect(m_animation, SIGNAL(valueChanged(QVariant)), SLOT(valueChanged(QVariant)));
    connect(m_animation, SIGNAL(finished()), SLOT(animationFinished()));
}

DownloadAnimationStackedWidget::~DownloadAnimationStackedWidget()
{
    delete m_animation;
}

QString DownloadAnimationStackedWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadAnimationStackedWidget::paintEvent(QPaintEvent * event)
{
    if(m_isAnimating)
    {
        QPainter painter(this);
        renderCurrentWidget(painter);
        renderPreviousWidget(painter);
    }
    else
    {
        QWidget::paintEvent(event);
    }
}

void DownloadAnimationStackedWidget::renderPreviousWidget(QPainter &painter)
{
    QWidget *w = widget(m_previousIndex);
    QPixmap pixmap( w->size() );
    pixmap.fill(Qt::transparent);
    w->setAttribute(Qt::WA_TranslucentBackground, true);
    w->render(&pixmap);
    w->setAttribute(Qt::WA_TranslucentBackground, false);

    switch(m_type)
    {
        case BottomToTop :
                {
                    painter.drawPixmap(0, height()/2, pixmap);
                    break;
                }
        case TopToBottom :
                {
                    painter.drawPixmap(0, -height()/2, pixmap);
                    break;
                }
        case LeftToRight :
                {
                    painter.drawPixmap(width()/2, 0, pixmap);
                    break;
                }
        case RightToLeft :
                {
                    painter.drawPixmap(-width()/2, 0, pixmap);
                    break;
                }
        default: break;
    }
}

void DownloadAnimationStackedWidget::renderCurrentWidget(QPainter &painter)
{
    QWidget *w = widget(m_currentIndex);
    QPixmap pixmap( w->size() );
    pixmap.fill(Qt::transparent);
    w->setAttribute(Qt::WA_TranslucentBackground, true);
    w->render(&pixmap);
    w->setAttribute(Qt::WA_TranslucentBackground, false);

    switch(m_type)
    {
        case BottomToTop :
                {
                    painter.translate(0, m_currentValue);
                    painter.drawPixmap(0, -height()/2, pixmap);
                    break;
                }
        case TopToBottom :
                {
                    painter.translate(0, m_currentValue);
                    painter.drawPixmap(0, height()/2, pixmap);
                    break;
                }
        case LeftToRight :
                {
                    painter.translate(m_currentValue, 0);
                    painter.drawPixmap(-width()/2, 0, pixmap);
                    break;
                }
        case RightToLeft :
                {
                    painter.translate(m_currentValue, 0);
                    painter.drawPixmap(width()/2, 0, pixmap);
                    break;
                }
        default: break;
    }
}

void DownloadAnimationStackedWidget::start(int index)
{
    if(m_isAnimating)
    {
        return;
    }
    m_previousIndex = m_currentIndex;
    m_currentIndex = index;

    int offsetx = frameRect().width();
    int offsety = frameRect().height();
    widget(m_currentIndex)->setGeometry(0, 0, offsetx, offsety);

    currentWidget()->hide();
    m_isAnimating = true;
    m_animation->start();
}

void DownloadAnimationStackedWidget::setIndex(int previous, int current)
{
    m_currentIndex = current;
    m_previousIndex = previous;
}

void DownloadAnimationStackedWidget::setLength(int length, AnimationType type)
{
    switch(m_type = type)
    {
        case BottomToTop :
        case LeftToRight :
                {
                    m_animation->setStartValue(-length/2);
                    m_animation->setEndValue(length/2);
                    break;
                }
        case TopToBottom :
        case RightToLeft :
                {
                    m_animation->setStartValue(length/2);
                    m_animation->setEndValue(-length/2);
                    break;
                }
        default: break;
    }
}

int DownloadAnimationStackedWidget::getPreviousIndex() const
{
    return m_previousIndex;
}

int DownloadAnimationStackedWidget::getCurrentIndex() const
{
    return m_currentIndex;
}

void DownloadAnimationStackedWidget::setDuration(int duration)
{
    m_animation->setDuration(duration);
}

int DownloadAnimationStackedWidget::getDuration() const
{
    return m_animation->duration();
}

void DownloadAnimationStackedWidget::valueChanged(const QVariant &value)
{
    m_currentValue = value.toFloat();
    update();
}

void DownloadAnimationStackedWidget::animationFinished()
{
    m_currentValue = 0;
    m_isAnimating = false;

    QWidget *w = widget(m_currentIndex);
    w->show();
    w->raise();

    setCurrentWidget( w );
    update();
}
