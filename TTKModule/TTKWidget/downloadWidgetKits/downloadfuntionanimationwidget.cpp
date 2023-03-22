#include "downloadfuntionanimationwidget.h"
#include "downloadwidgetutils.h"
#include "downloaduiobject.h"

#include "qmath.h"

#include <QPainter>
#include <QBoxLayout>
#include <QToolButton>
#include <QButtonGroup>
#include <QPropertyAnimation>

DownloadAbstractAnimationWidget::DownloadAbstractAnimationWidget(QWidget *parent)
    : QWidget(parent),
      m_curIndex(0),
      m_preIndex(0),
      m_x(0),
      m_perWidth(0.0f),
      m_totalWidth(0.0f),
      m_isAnimation(true),
      m_showState(true),
      m_showLine(true)
{
    m_animation = new QPropertyAnimation(this, QByteArray());
    m_animation->setDuration(100);

    connect(m_animation, SIGNAL(valueChanged(QVariant)), SLOT(animationChanged(QVariant)));
    connect(m_animation, SIGNAL(finished()), SLOT(finished()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);

    m_buttonGroup = new QButtonGroup(this);
    QtButtonGroupConnect(m_buttonGroup, this, switchToSelectedItemStyle);
}

DownloadAbstractAnimationWidget::~DownloadAbstractAnimationWidget()
{
    qDeleteAll(m_container);
    delete m_animation;
    delete m_buttonGroup;
}

void DownloadAbstractAnimationWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_showState)
    {
        m_perWidth = m_container[0]->width() + m_container[0]->x();

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 0.1, Qt::SolidLine));

        int offset =  m_perWidth - (m_container[0]->width() + m_pix.width()) / 2;
        offset = m_isAnimation ? (offset + m_x) : (offset + m_curIndex * m_perWidth);
        if(m_showLine)
        {
            painter.drawLine(0, height(), offset, height());
            painter.drawLine(offset + m_pix.width(), height(), m_totalWidth, height());
        }
        painter.drawPixmap(offset, height() - m_pix.height(), m_pix);
    }
}

void DownloadAbstractAnimationWidget::switchToSelectedItemStyle(int index)
{
    m_isAnimation = true;
    m_preIndex = m_curIndex;
    m_curIndex = index;
    m_animation->setStartValue(m_preIndex*m_perWidth);
    m_animation->setEndValue(index*m_perWidth);
    m_animation->start();

    Q_EMIT buttonClicked(index);
}

void DownloadAbstractAnimationWidget::animationChanged(const QVariant &value)
{
    m_x = value.toInt();
    update();
}

void DownloadAbstractAnimationWidget::finished()
{
    m_isAnimation = false;
}



DownloadSkinAnimationWidget::DownloadSkinAnimationWidget(QWidget *parent)
    : DownloadAbstractAnimationWidget(parent)
{
    m_pix = QPixmap(54, 2);
    m_pix.fill(QColor(0x80, 0xB7, 0xF1));

    QHBoxLayout *ly = TTKObjectCast(QHBoxLayout*, layout());

    QStringList names;
    names << tr("Re") << tr("My") << tr("Online");
    for(int i = 0; i < names.count(); ++i)
    {
        QToolButton *btn = new QToolButton(this);
        btn->setText(names[i]);
        btn->setFixedSize(80, 30);
        ly->addWidget(btn);
        m_buttonGroup->addButton(btn, i);
        m_container << btn;
    }
    ly->addStretch(1);

    switchToSelectedItemStyle(0);
}

void DownloadSkinAnimationWidget::paintEvent(QPaintEvent *event)
{
    m_totalWidth = width();
    DownloadAbstractAnimationWidget::paintEvent(event);
}

void DownloadSkinAnimationWidget::switchToSelectedItemStyle(int index)
{
    m_container[0]->setStyleSheet(TTK::UI::ColorStyle02 + TTK::UI::BackgroundStyle01);
    m_container[1]->setStyleSheet(TTK::UI::ColorStyle02 + TTK::UI::BackgroundStyle01);
    m_container[2]->setStyleSheet(TTK::UI::ColorStyle02 + TTK::UI::BackgroundStyle01);

    switch(index)
    {
        case 0: m_container[0]->setStyleSheet(TTK::UI::ColorStyle03 + TTK::UI::BackgroundStyle01); break;
        case 1: m_container[1]->setStyleSheet(TTK::UI::ColorStyle03 + TTK::UI::BackgroundStyle01); break;
        case 2: m_container[2]->setStyleSheet(TTK::UI::ColorStyle03 + TTK::UI::BackgroundStyle01); break;
        default: break;
    }

    DownloadAbstractAnimationWidget::switchToSelectedItemStyle(index);
}
