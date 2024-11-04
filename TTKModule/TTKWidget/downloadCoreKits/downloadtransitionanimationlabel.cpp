#include "downloadtransitionanimationlabel.h"

#include <QPainter>
#include <QPropertyAnimation>

DownloadTransitionAnimationLabel::DownloadTransitionAnimationLabel(QWidget *parent)
    : QLabel(parent),
      m_isAnimating(false),
      m_currentValue(0),
      m_animationEnabled(true)
{
    m_animation = new QPropertyAnimation(this, {});
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::Linear);
    m_animation->setStartValue(0);
    m_animation->setEndValue(101);

    connect(m_animation, SIGNAL(valueChanged(QVariant)), SLOT(valueChanged(QVariant)));
    connect(m_animation, SIGNAL(finished()), SLOT(animationFinished()));
}

DownloadTransitionAnimationLabel::~DownloadTransitionAnimationLabel()
{
    delete m_animation;
}

const QPixmap& DownloadTransitionAnimationLabel::renderPixmap() const
{
    return m_renderPixmap;
}

void DownloadTransitionAnimationLabel::start()
{
    stop();
    m_isAnimating = true;
    m_animation->start();
}

void DownloadTransitionAnimationLabel::stop()
{
    if(isRunning())
    {
        m_animation->stop();
        animationFinished();
    }
}

bool DownloadTransitionAnimationLabel::isRunning() const
{
    return m_animation->state() == QPropertyAnimation::Running;
}

void DownloadTransitionAnimationLabel::setPixmap(const QPixmap &pix)
{
    if(pix.isNull())
    {
        return;
    }

    const QPixmap &pixmap = QtLablePixmap(this);
    if(!m_animationEnabled || pixmap.isNull())
    {
        m_renderPixmap = pix;
        QLabel::setPixmap(pix);
        return;
    }

    m_previousPixmap = pixmap;
    m_currentPixmap = pix;
    m_isAnimating = true;
    m_animation->start();
}

void DownloadTransitionAnimationLabel::valueChanged(const QVariant &value)
{
    m_currentValue = value.toFloat();
    update();
}

void DownloadTransitionAnimationLabel::animationFinished()
{
    m_currentValue = 0;
    m_isAnimating = false;
    m_renderPixmap = m_currentPixmap;
    QLabel::setPixmap(m_renderPixmap);
}

void DownloadTransitionAnimationLabel::paintEvent(QPaintEvent *event)
{
    if(m_isAnimating)
    {
        QPainter painter(this);
        painter.drawPixmap(rect(), m_previousPixmap);

        QPixmap pix(size());
        pix.fill(Qt::transparent);
        QPainter paint(&pix);
        paint.fillRect(rect(), QColor(0xFF, 0xFF, 0xFF, 2.55 * m_currentValue));
        paint.setCompositionMode(QPainter::CompositionMode_SourceIn);
        paint.drawPixmap(rect(), m_currentPixmap);

        m_renderPixmap = pix;
        painter.drawPixmap(rect(), pix);
    }
    else
    {
        QLabel::paintEvent(event);
    }
}
