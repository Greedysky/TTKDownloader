#include "downloadlistitemwidget.h"
#include "downloadnumberutils.h"
#include "downloaduiobject.h"
#include "downloadbackgroundmanager.h"
#include "ttktime.h"

#include <QLabel>
#include <QBoxLayout>
#include <QProgressBar>
#include <QFileIconProvider>

static constexpr const char *LABEL_NONE = "--";
static constexpr const char *LABEL_MAX_TIME = "99:99:99";

DownloadListItemWidget::DownloadListItemWidget(QWidget *parent)
    : QWidget(parent),
      m_currentSize(0),
      m_previousSize(0),
      m_totalSize(0)
{
    setFixedHeight(70);

    connect(&m_timer, SIGNAL(timeout()), SLOT(updateDownloadSpeed()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(9, 9, 22, 9);
    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(40, 40);
    m_iconLabel->setPixmap(QPixmap(":/image/lb_blankImage"));
    layout->addWidget(m_iconLabel);

    ///////////////////////////////////////////////////////////////////
    QWidget *fileInfoWidget = new QWidget(this);
    fileInfoWidget->setMinimumWidth(280);
    QVBoxLayout *fileInfoWidgetLayout = new QVBoxLayout(fileInfoWidget);
    m_fileNameLabel = new QLabel(tr("Unknow File"), fileInfoWidget);
    m_fileSizeLabel = new QLabel(LABEL_NONE, fileInfoWidget);
    fileInfoWidgetLayout->addWidget(m_fileNameLabel);
    fileInfoWidgetLayout->addWidget(m_fileSizeLabel);
    fileInfoWidget->setLayout(fileInfoWidgetLayout);
    layout->addWidget(fileInfoWidget);

    ///////////////////////////////////////////////////////////////////
    QWidget *speedWidget = new QWidget(this);
    speedWidget->setFixedSize(160, 70);
    QVBoxLayout *speedWidgetLayout = new QVBoxLayout(speedWidget);
    speedWidgetLayout->setSpacing(0);

    m_progressBar = new QProgressBar(speedWidget);
    m_progressBar->setFixedHeight(13);
    m_progressBar->setMaximum(100);
    speedWidgetLayout->addWidget(m_progressBar);

    QWidget *speedInfoWidget = new QWidget(speedWidget);
    QHBoxLayout *speedInfoWidgetLayout = new QHBoxLayout(speedInfoWidget);
    speedInfoWidgetLayout->setContentsMargins(0, 9, 0, 9);
    m_speedTimeLabel = new QLabel(LABEL_MAX_TIME, speedInfoWidget);
    m_speedLabel = new QLabel(LABEL_NONE, speedInfoWidget);
    speedInfoWidgetLayout->addWidget(m_speedTimeLabel);
    speedInfoWidgetLayout->addStretch(1);
    speedInfoWidgetLayout->addWidget(m_speedLabel);
    speedInfoWidget->setLayout(speedInfoWidgetLayout);
    speedWidgetLayout->addWidget(speedInfoWidget);
    speedWidget->setLayout(speedWidgetLayout);
    layout->addWidget(speedWidget);

    ///////////////////////////////////////////////////////////////////
    m_stateLabel = new QLabel(this);
    m_stateLabel->setFixedSize(60, 30);
    layout->addWidget(m_stateLabel);
    setLayout(layout);

    backgroundChanged();
    G_BACKGROUND_PTR->addObserver(this);
}

DownloadListItemWidget::~DownloadListItemWidget()
{
    G_BACKGROUND_PTR->removeObserver(this);
    delete m_iconLabel;
    delete m_fileNameLabel;
    delete m_fileSizeLabel;
    delete m_progressBar;
    delete m_speedTimeLabel;
    delete m_speedLabel;
    delete m_stateLabel;
}

float DownloadListItemWidget::percent() const
{
    return m_progressBar->value();
}

void DownloadListItemWidget::backgroundChanged()
{
    if(m_progressBar)
    {
        m_progressBar->setStyleSheet(TTK::UI::ProgressBar01 +
                                     QString("QProgressBar::chunk{ background:%1; }").arg(
                                     G_BACKGROUND_PTR->backgroundColor().name()));
    }
}

void DownloadListItemWidget::progressChanged(qint64 current, qint64 total)
{
    if(total < 0)
    {
        return;
    }

    m_currentSize = current;
    m_progressBar->setValue(current * 100.0f / total);
}

void DownloadListItemWidget::updateFileInfoChanged(const QString &name, qint64 size)
{
    m_fileNameLabel->setText(name);
    m_fileSizeLabel->setText(TTK::Number::sizeByteToLabel(m_totalSize = size));

    QFileIconProvider provider;
    QPixmap pix(provider.icon(QFileInfo(name)).pixmap(40, 40));
    if(pix.isNull())
    {
        pix.load(":/image/lb_blankImage");
    }
    m_iconLabel->setPixmap(pix);
}

void DownloadListItemWidget::stateChanged(const QString &state)
{
    if(state == tr("D_Download"))
    {
        m_timer.start(TTK_DN_S2MS / 2);
    }
    else
    {
        m_timer.stop();
        m_speedTimeLabel->setText(LABEL_MAX_TIME);
        m_speedLabel->setText(LABEL_NONE);
    }

    m_stateLabel->setText(state);
}

void DownloadListItemWidget::updateDownloadSpeed()
{
    const int delta = (m_currentSize - m_previousSize) * 2;
    m_previousSize = m_currentSize;
    m_speedLabel->setText(TTK::Number::speedByteToLabel(delta));

    m_speedTimeLabel->setText(delta == 0 ? LABEL_MAX_TIME : timeStandardization((m_totalSize - m_previousSize)/delta + 1));
}

QString DownloadListItemWidget::timeStandardization(qint64 time)
{
    TTKTime t(time * 1000);
    return QString("%1:%2:%3").arg(QString::number(t.hour()).rightJustified(2, '0'),
                                   QString::number(t.minute()).rightJustified(2, '0'),
                                   QString::number(t.second()).rightJustified(2, '0'));
}
