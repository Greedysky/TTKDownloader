#include "downloadbackgroundpopwidget.h"
#include "downloaduiobject.h"
#include "ttkclickedslider.h"

#include <QLabel>
#include <QBoxLayout>

DownloadBackgroundPopWidget::DownloadBackgroundPopWidget(QWidget *parent)
    : DownloadToolMenuWidget(parent)
{
    initialize();
}

DownloadBackgroundPopWidget::~DownloadBackgroundPopWidget()
{
    delete m_slider;
}

void DownloadBackgroundPopWidget::setValue(int value)
{
    m_slider->setValue(value);
}

int DownloadBackgroundPopWidget::value() const
{
    return m_slider->value();
}

void DownloadBackgroundPopWidget::sliderPressed()
{
    Q_EMIT sliderStateChanged(true);
}

void DownloadBackgroundPopWidget::sliderReleased()
{
    Q_EMIT sliderStateChanged(false);
}

void DownloadBackgroundPopWidget::initialize()
{
    m_menu->setStyleSheet(TTK::UI::MenuStyle02);
    m_containWidget->setFixedSize(54, 160);

    QGridLayout *layout = new QGridLayout(m_containWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_slider = new TTKClickedSlider(Qt::Vertical, m_containWidget);
    m_slider->setStyleSheet(TTK::UI::SliderStyle01);
    m_slider->setRange(0, 100);
    m_slider->setValue(100);
    m_slider->setCursor(QCursor(Qt::PointingHandCursor));

    connect(m_slider, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)));
    connect(m_slider, SIGNAL(sliderPressed()), SLOT(sliderPressed()));
    connect(m_slider, SIGNAL(sliderReleased()), SLOT(sliderReleased()));

    QLabel *textLabel = nullptr;
    textLabel = new QLabel("100%", m_containWidget);
    textLabel->setAlignment(Qt::AlignTop);
    textLabel->setStyleSheet(TTK::UI::ColorStyle01);
    layout->addWidget(textLabel, 0, 0);

    textLabel = new QLabel("50%", m_containWidget);
    textLabel->setAlignment(Qt::AlignVCenter);
    textLabel->setStyleSheet(TTK::UI::ColorStyle01);
    layout->addWidget(textLabel, 1, 0);

    textLabel = new QLabel("0%", m_containWidget);
    textLabel->setAlignment(Qt::AlignBottom);
    textLabel->setStyleSheet(TTK::UI::ColorStyle01);
    layout->addWidget(textLabel, 2, 0);
    layout->addWidget(m_slider, 0, 1, 3, 1);

    m_containWidget->setLayout(layout);
}
