#include "downloadabstractmovewidget.h"
#include "downloadbackgroundmanager.h"
#include "downloadbackgroundconfigmanager.h"
#include "downloadextractwrapper.h"

#include <QPainter>
#include <QBoxLayout>

#define WIDTH  4
#define HEIGHT 4

DownloadAbstractMoveWidget::DownloadAbstractMoveWidget(QWidget *parent)
    : DownloadAbstractMoveWidget(true, parent)
{

}

DownloadAbstractMoveWidget::DownloadAbstractMoveWidget(bool transparent, QWidget *parent)
    : QWidget(parent),
      m_moveOption(false),
      m_showShadow(true),
      m_leftButtonPress(false),
      m_background(nullptr)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, transparent);

    G_BACKGROUND_PTR->addObserver(this);
}

DownloadAbstractMoveWidget::~DownloadAbstractMoveWidget()
{
    G_BACKGROUND_PTR->removeObserver(this);
}

void DownloadAbstractMoveWidget::backgroundChanged()
{
    if(m_background)
    {
        setBackgroundPixmap(size());
    }
}

void DownloadAbstractMoveWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_showShadow)
    {
        QPainter painter(this);

        painter.drawPixmap(0, 0, WIDTH, HEIGHT, QPixmap(":/shadow/lb_left_top"));
        painter.drawPixmap(width() - WIDTH, 0, WIDTH, HEIGHT, QPixmap(":/shadow/lb_right_top"));
        painter.drawPixmap(0, height() - HEIGHT, WIDTH, HEIGHT, QPixmap(":/shadow/lb_left_bottom"));
        painter.drawPixmap(width() - WIDTH, height() - HEIGHT, WIDTH, HEIGHT, QPixmap(":/shadow/lb_right_bottom"));

        painter.drawPixmap(0, WIDTH, HEIGHT, height() - 2 * WIDTH, QPixmap(":/shadow/lb_left").scaled(WIDTH, height() - 2 * HEIGHT));
        painter.drawPixmap(width() - WIDTH, WIDTH, HEIGHT, height() - 2 * HEIGHT, QPixmap(":/shadow/lb_right").scaled(WIDTH, height() - 2 * HEIGHT));
        painter.drawPixmap(HEIGHT, 0, width() - 2 * WIDTH, HEIGHT, QPixmap(":/shadow/lb_top").scaled(width() - 2 * WIDTH, HEIGHT));
        painter.drawPixmap(WIDTH, height() - HEIGHT, width() - 2 * WIDTH, HEIGHT, QPixmap(":/shadow/lb_bottom").scaled(width() - 2 * WIDTH, HEIGHT));
    }
}

void DownloadAbstractMoveWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if(event->button() == Qt::LeftButton && !m_moveOption)
    {
        m_leftButtonPress = true;
    }

    m_pressAt = QtMouseEventGlobalPos(event);
}

void DownloadAbstractMoveWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(!m_leftButtonPress)
    {
        event->ignore();
        return;
    }

    const int xpos = QtMouseEventGlobalX(event) - m_pressAt.x();
    const int ypos = QtMouseEventGlobalY(event) - m_pressAt.y();
    m_pressAt = QtMouseEventGlobalPos(event);
    move(x() + xpos, y() + ypos);
}

void DownloadAbstractMoveWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    m_pressAt = QtMouseEventGlobalPos(event);
    m_leftButtonPress = false;
}

void DownloadAbstractMoveWidget::setBackgroundPixmap(QLabel *label, const QSize &size)
{
    m_background = label;
    setBackgroundPixmap(size);
}

void DownloadAbstractMoveWidget::setBackgroundPixmap(const QSize &size)
{
    DownloadBackgroundImage image;
    if(DownloadExtractWrapper::outputSkin(&image, G_BACKGROUND_PTR->background()))
    {
        m_background->setPixmap(image.m_pix.scaled(size));
    }
    else
    {
        m_background->setPixmap(QPixmap(G_BACKGROUND_PTR->background()).scaled(size));
    }
}


DownloadAbstractMoveSingleWidget::DownloadAbstractMoveSingleWidget(QWidget *parent)
    : DownloadAbstractMoveSingleWidget(true, parent)
{

}

DownloadAbstractMoveSingleWidget::DownloadAbstractMoveSingleWidget(bool transparent, QWidget *parent)
    : DownloadAbstractMoveWidget(transparent, parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->setContentsMargins(WIDTH, HEIGHT, WIDTH, HEIGHT);
    l->setSpacing(0);

    m_container = new QWidget(this);
    l->addWidget(m_container);
    setLayout(l);
}

DownloadAbstractMoveSingleWidget::~DownloadAbstractMoveSingleWidget()
{
    delete m_container;
}
