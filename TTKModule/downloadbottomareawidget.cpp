#include "downloadbottomareawidget.h"
#include "ui_downloadapplication.h"
#include "downloadapplication.h"
#include "downloadsystemtraymenu.h"
#include "downloadwindowextras.h"
#include "downloadnumberutils.h"

DownloadBottomAreaWidget *DownloadBottomAreaWidget::m_instance = nullptr;

DownloadBottomAreaWidget::DownloadBottomAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    m_instance = this;
    m_systemCloseConfig = false;

    createSystemTrayIcon();

    m_windowExtras = new DownloadWindowExtras(parent);
}

DownloadBottomAreaWidget::~DownloadBottomAreaWidget()
{
    delete m_systemTrayMenu;
    delete m_systemTray;
    delete m_windowExtras;
}

QString DownloadBottomAreaWidget::getClassName()
{
    return staticMetaObject.className();
}

DownloadBottomAreaWidget *DownloadBottomAreaWidget::instance()
{
    return m_instance;
}

void DownloadBottomAreaWidget::setupUi(Ui::DownloadApplication* ui)
{
    m_ui = ui;
    ui->resizeLabelWidget->setPixmap(QPixmap(":/tiny/lb_resize_normal"));

    ui->expandButton->setLabelIcon(":/functions/lb_left");

    ui->downloadSettingButton->setLabelText(tr("Download"));
    ui->downloadSettingButton->setLabelIcon(":/functions/lb_order");

    ui->downloadPlanButton->setLabelText(tr("Plan"));
    ui->downloadPlanButton->setLabelIcon(":/functions/lb_plan");

    ui->downloadSpeedButton->setLabelText(DownloadUtils::Number::speed2Label(200000),
                                          DownloadUtils::Number::speed2Label(200000));
}

void DownloadBottomAreaWidget::showMessage(const QString &title, const QString &text)
{
    m_systemTray->showMessage(title, text);
}

#if defined DOWNLOAD_DEBUG && defined Q_OS_WIN && defined DOWNLOAD_WINEXTRAS
void DownloadBottomAreaWidget::setValue(int value) const
{
    m_windowExtras->setValue(value);
}

void DownloadBottomAreaWidget::setRange(int min, int max) const
{
    m_windowExtras->setRange(min, max);
}
#endif

void DownloadBottomAreaWidget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::DoubleClick:
            break;
        case QSystemTrayIcon::Trigger:
            if(DownloadApplication::instance()->isMinimized())
            {
                DownloadApplication::instance()->showNormal();
                DownloadApplication::instance()->activateWindow();
            }
            break;
        default:
            break;
    }
}

void DownloadBottomAreaWidget::createSystemTrayIcon()
{
    m_systemTray = new QSystemTrayIcon(DownloadApplication::instance());
    m_systemTray->setIcon(QIcon(":/image/lb_player_logo"));
    m_systemTray->setToolTip(tr("TTKDownloader"));

    m_systemTrayMenu = new DownloadSystemTrayMenu(DownloadApplication::instance());

    m_systemTray->setContextMenu(m_systemTrayMenu);
    m_systemTray->show();
    connect(m_systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                          SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}
