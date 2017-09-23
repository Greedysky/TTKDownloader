#include "downloadlistitemwidget.h"
#include "downloadobject.h"
#include "downloadnumberutils.h"
#include "downloadtime.h"
#include "downloaduiobject.h"
#include "downloadbackgroundmanager.h"

#include <QLabel>
#include <QBoxLayout>
#include <QProgressBar>
#include <QFileIconProvider>

DownloadListItemWidget::DownloadListItemWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(70);

    connect(&m_timer, SIGNAL(timeout()), SLOT(updateDownloadSpeed()));
    m_previousSize = 0;
    m_totalSize = 0;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(9, 9, 22, 9);
    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(40, 40);
    layout->addWidget(m_iconLabel);

    ///////////////////////////////////////////////////////////////////
    QWidget *fileInfoWidget = new QWidget(this);
    fileInfoWidget->setMinimumWidth(280);
    QVBoxLayout *fileInfoWidgetLayout = new QVBoxLayout(fileInfoWidget);
    m_fileNameLabel = new QLabel(tr("Unknow File"), fileInfoWidget);
    m_fileSizeLabel = new QLabel("--", fileInfoWidget);
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
    speedWidgetLayout->addWidget(m_progressBar);

    QWidget *speedInfoWidget = new QWidget(speedWidget);
    QHBoxLayout *speedInfoWidgetLayout = new QHBoxLayout(speedInfoWidget);
    speedInfoWidgetLayout->setContentsMargins(0, 9, 0, 9);
    m_speedTimeLabel = new QLabel("99:99:99", speedInfoWidget);
    m_speedLabel = new QLabel("--", speedInfoWidget);
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
}

DownloadListItemWidget::~DownloadListItemWidget()
{
    delete m_iconLabel;
    delete m_fileNameLabel;
    delete m_fileSizeLabel;
    delete m_progressBar;
    delete m_speedTimeLabel;
    delete m_speedLabel;
    delete m_stateLabel;
}

QString DownloadListItemWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadListItemWidget::progressChanged(qint64 current, qint64 total)
{
    m_progressBar->setRange(0, total);
    m_progressBar->setValue(current);
}

void DownloadListItemWidget::updateFileInfoChanged(const QString &name, qint64 size)
{
    m_fileNameLabel->setText(name);
    m_fileSizeLabel->setText(DownloadUtils::Number::size2Label(m_totalSize = size));
    QFileIconProvider provider;
    m_iconLabel->setPixmap(provider.icon(QFileInfo(name)).pixmap(40,40));
}

void DownloadListItemWidget::stateChanged(const QString &state)
{
    if(state == tr("D_Download"))
    {
        m_timer.start(500);
    }
    else
    {
        m_timer.stop();
    }

    m_stateLabel->setText(state);
}

void DownloadListItemWidget::updateDownloadSpeed()
{
    int delta = (m_progressBar->value() - m_previousSize)*2;
    m_previousSize = m_progressBar->value();
    m_speedLabel->setText(DownloadUtils::Number::speed2Label(delta));

    m_speedTimeLabel->setText( delta == 0 ? "99:99:99" :
                             timeStandardization((m_totalSize - m_previousSize)/delta + 1));
}

QString DownloadListItemWidget::timeStandardization(qint64 time)
{
    DownloadTime t(time, DownloadTime::All_Sec);
    return QString("%1:%2:%3").arg(QString::number(t.getHour()).rightJustified(2, '0'))
                              .arg(QString::number(t.getMinute()).rightJustified(2, '0'))
                              .arg(QString::number(t.getSecond()).rightJustified(2, '0'));
}

void DownloadListItemWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    if(m_progressBar)
    {
        m_progressBar->setStyleSheet(DownloadUIObject::MProgressBar01 +
                                     QString("QProgressBar::chunk{ background:%1; }").arg(
                                     M_BACKGROUND_PTR->getMBackgroundColor().name()));
    }
}
