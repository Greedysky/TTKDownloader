#include "downloadabstractmovedialog.h"
#include "downloadbackgroundmanager.h"
#include "downloadbackgroundconfigmanager.h"
#include "downloadextractwrapper.h"

#include <QMouseEvent>
#include <QPainter>

#define WIDTH  4
#define HEIGHT 4

DownloadAbstractMoveDialog::DownloadAbstractMoveDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(true, parent)
{

}

DownloadAbstractMoveDialog::DownloadAbstractMoveDialog(bool transparent, QWidget *parent)
    : QDialog(parent)
{
    ///Remove the title bar
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, transparent);

    m_moveOption = false;
    m_leftButtonPress = false;
    m_showShadow = true;
    m_background = nullptr;

    M_BACKGROUND_PTR->addObserver(this);
}

DownloadAbstractMoveDialog::~DownloadAbstractMoveDialog()
{
    M_BACKGROUND_PTR->removeObserver(this);
}

void DownloadAbstractMoveDialog::backgroundChanged()
{
    if(m_background)
    {
        setBackgroundPixmap(size());
    }
}

void DownloadAbstractMoveDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);

    if(m_showShadow)
    {
        QPainter painter(this);

        painter.drawPixmap(0, 0, WIDTH, HEIGHT, QPixmap(":/shadow/lb_left_top"));
        painter.drawPixmap(width() - WIDTH, 0, WIDTH, HEIGHT, QPixmap(":/shadow/lb_right_top"));
        painter.drawPixmap(0, height() - HEIGHT, WIDTH, HEIGHT, QPixmap(":/shadow/lb_left_bottom"));
        painter.drawPixmap(width() - WIDTH, height() - HEIGHT, WIDTH, HEIGHT, QPixmap(":/shadow/lb_right_bottom"));

        painter.drawPixmap(0, WIDTH, HEIGHT, height() - 2*WIDTH,
                           QPixmap(":/shadow/lb_left").scaled(WIDTH, height() - 2*HEIGHT));
        painter.drawPixmap(width() - WIDTH, WIDTH, HEIGHT, height() - 2*HEIGHT,
                           QPixmap(":/shadow/lb_right").scaled(WIDTH, height() - 2*HEIGHT));
        painter.drawPixmap(HEIGHT, 0, width() - 2*WIDTH, HEIGHT,
                           QPixmap(":/shadow/lb_top").scaled(width() - 2*WIDTH, HEIGHT));
        painter.drawPixmap(WIDTH, height() - HEIGHT, width() - 2*WIDTH, HEIGHT,
                           QPixmap(":/shadow/lb_bottom").scaled(width() - 2*WIDTH, HEIGHT));
    }
}

void DownloadAbstractMoveDialog::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if(event->button() == Qt::LeftButton && !m_moveOption)///Press the left key
    {
        m_leftButtonPress = true;
    }
#if TTK_QT_VERSION_CHECK(6,0,0)
    m_pressAt = event->globalPosition().toPoint();
#else
    m_pressAt = event->globalPos();
#endif
}

void DownloadAbstractMoveDialog::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(!m_leftButtonPress)///Not press the left key
    {
        event->ignore();
        return;
    }
#if TTK_QT_VERSION_CHECK(6,0,0)
    const int xpos = event->globalPosition().x() - m_pressAt.x();
    const int ypos = event->globalPosition().y() - m_pressAt.y();
    m_pressAt = event->globalPosition().toPoint();
#else
    const int xpos = event->globalX() - m_pressAt.x();
    const int ypos = event->globalY() - m_pressAt.y();
    m_pressAt = event->globalPos();
#endif
    move(x() + xpos, y() + ypos);
}

void DownloadAbstractMoveDialog::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
#if TTK_QT_VERSION_CHECK(6,0,0)
    m_pressAt = event->globalPosition().toPoint();
#else
    m_pressAt = event->globalPos();
#endif
    m_leftButtonPress = false;
}

void DownloadAbstractMoveDialog::setBackgroundPixmap(QLabel *label, const QSize &size)
{
    m_background = label;
    setBackgroundPixmap(size);
}

void DownloadAbstractMoveDialog::setBackgroundPixmap(const QSize &size)
{
    QLabel *label = TTKStatic_cast(QLabel*, m_background);
    DownloadBackgroundImage image;
    if(DownloadExtractWrapper::outputSkin(&image, M_BACKGROUND_PTR->getMBackground()))
    {
        label->setPixmap(image.m_pix.scaled(size));
    }
    else
    {
        label->setPixmap(QPixmap(M_BACKGROUND_PTR->getMBackground()).scaled(size));
    }
}
