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
    m_menu->setStyleSheet(DownloadUIObject::MMenuStyle02);

    m_containWidget->setFixedSize(60, 160);

    QBoxLayout *hbox = new QHBoxLayout(m_containWidget);
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(0);

    QLabel *textLabel = new QLabel(m_containWidget);
    textLabel->setStyleSheet(DownloadUIObject::MColorStyle02);
    textLabel->setText("100%\n\n\n\n\n50%\n\n\n\n\n0%");

    m_slider = new TTKClickedSlider(Qt::Vertical, m_containWidget);
    m_slider->setStyleSheet(DownloadUIObject::MSliderStyle03);
    connect(m_slider, SIGNAL(valueChanged(int)), SIGNAL(valueChanged(int)));
    connect(m_slider, SIGNAL(sliderPressed()), SLOT(sliderPressed()));
    connect(m_slider, SIGNAL(sliderReleased()), SLOT(sliderReleased()));

    m_slider->setRange(0, 100);
    m_slider->setValue(100);
    m_slider->setCursor(QCursor(Qt::PointingHandCursor));

    hbox->addWidget(textLabel);
    hbox->addWidget(m_slider);

    m_containWidget->setLayout(hbox);

}
