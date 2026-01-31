#include "downloadbottomareawidget.h"
#include "ui_downloadapplication.h"
#include "downloadapplication.h"
#include "downloadsystemtraymenu.h"
#include "downloadnumberutils.h"
#include "downloadnetworkspeedthread.h"
#include "downloaduiobject.h"
#include "downloadimageutils.h"
#include "downloadbackgroundmanager.h"
#include "downloadsettingmanager.h"
#include "downloadrightareawidget.h"

DownloadBottomAreaWidget *DownloadBottomAreaWidget::m_instance = nullptr;

DownloadBottomAreaWidget::DownloadBottomAreaWidget(QWidget *parent)
    : QWidget(parent),
      m_isAvailable(false),
      m_systemCloseConfig(false),
      m_expandMode(false),
      m_toolPopupMenu(nullptr)
{
    m_instance = this;

    createSystemTrayIcon();

    m_speedThread = new DownloadNetworkSpeedThread(this);
    connect(m_speedThread, SIGNAL(networkData(ulong,ulong)), SLOT(updateNetworkData(ulong,ulong)));
}

DownloadBottomAreaWidget::~DownloadBottomAreaWidget()
{
    m_speedThread->stop();
    delete m_toolPopupMenu;
    delete m_systemTrayMenu;
    delete m_systemTray;
    delete m_speedThread;
}

DownloadBottomAreaWidget *DownloadBottomAreaWidget::instance()
{
    return m_instance;
}

void DownloadBottomAreaWidget::setupUi(Ui::DownloadApplication *ui)
{
    m_ui = ui;
    m_speedThread->start();

    ui->resizeLabelWidget->setPixmap(QPixmap(":/tiny/lb_resize_normal"));

    ui->expandButton->setLabelIcon(":/functions/lb_left");

    ui->downloadSettingButton->setLabelText(tr("Download"));
    ui->downloadSettingButton->setLabelIcon(":/functions/lb_order");

    ui->downloadPlanButton->setLabelText(tr("Plan"));
    ui->downloadPlanButton->setLabelIcon(":/functions/lb_plan");

    ui->downloadSpeedButton->setLabelText("--", "--");

    connect(ui->downloadSettingButton, SIGNAL(mouseClicked()), SLOT(settingButtonClicked()));
    connect(ui->downloadPlanButton, SIGNAL(mouseClicked()), SLOT(planButtonClicked()));
    connect(ui->expandButton, SIGNAL(clicked()), SLOT(expandButtonClicked()));
}

void DownloadBottomAreaWidget::showMessage(const QString &title, const QString &text)
{
    m_systemTray->showMessage(title, text);
}

void DownloadBottomAreaWidget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::DoubleClick:
            break;
        case QSystemTrayIcon::Trigger:
            {
                DownloadApplication *w = DownloadApplication::instance();
                if(w->isMinimized() || w->isHidden())
                {
                    w->showNormal();
                    w->activateWindow();
                }
                break;
            }
        default:
            break;
    }
}

void DownloadBottomAreaWidget::updateNetworkData(ulong upload, ulong download)
{
    const QString &up = TTK::Number::speedByteToLabel(upload);
    const QString &down = TTK::Number::speedByteToLabel(download);
    m_ui->downloadSpeedButton->setLabelText(up, down);
}

void DownloadBottomAreaWidget::settingButtonClicked()
{
    delete m_toolPopupMenu;
    m_toolPopupMenu = new QMenu(this);
    m_toolPopupMenu->setStyleSheet(TTK::UI::MenuStyle02);

    QPixmap pix(17, 17);
    pix.fill(G_BACKGROUND_PTR->backgroundColor());
    TTK::Image::fusionPixmap(pix, QPixmap(":/contextMenu/lb_protection"), QPoint(2, 2));
    m_toolPopupMenu->addAction(QIcon(pix), tr("Speed Protection"));

    pix.fill(G_BACKGROUND_PTR->backgroundColor());
    TTK::Image::fusionPixmap(pix, QPixmap(":/contextMenu/lb_custom"), QPoint(2, 2));
    m_toolPopupMenu->addAction(QIcon(pix), tr("Custom Speed Limit"));
    m_toolPopupMenu->addSeparator();

    pix.fill(G_BACKGROUND_PTR->backgroundColor());
    TTK::Image::fusionPixmap(pix, QPixmap(":/contextMenu/lb_setting"), QPoint(2, 2));
    m_toolPopupMenu->addAction(QIcon(pix), tr("More Setting..."));

    m_ui->downloadSettingButton->setMenu(m_toolPopupMenu);
    m_ui->downloadSettingButton->setPopupMode(QToolButton::InstantPopup);
}

void DownloadBottomAreaWidget::planButtonClicked()
{
    delete m_toolPopupMenu;
    m_toolPopupMenu = new QMenu(this);
    m_toolPopupMenu->setStyleSheet(TTK::UI::MenuStyle02);
    m_toolPopupMenu->addAction(tr("Spare"));
    m_toolPopupMenu->addAction(tr("Add Plan"));
    m_toolPopupMenu->addAction(tr("Delete Plan"))->setEnabled(false);

    QMenu *downloadMenu = m_toolPopupMenu->addMenu(tr("Downloaded"));
    downloadMenu->addAction(tr("Close"));
    downloadMenu->addAction(tr("Locked"));
    downloadMenu->addAction(tr("Sleep"));
    downloadMenu->addAction(tr("Quit"));

    m_ui->downloadPlanButton->setMenu(m_toolPopupMenu);
    m_ui->downloadPlanButton->setPopupMode(QToolButton::InstantPopup);
}

void DownloadBottomAreaWidget::expandButtonClicked()
{
    if(m_expandMode)
    {
        G_SETTING_PTR->setValue(DownloadSettingManager::ExpandMode, 0);
        m_ui->leftWidget->setMinimumWidth(205);
        m_ui->leftWidget->setMaximumWidth(205);
        m_ui->expandButton->setLabelIcon(":/functions/lb_left");
        m_ui->fucntionListWidget->resizeMode(false);

    }
    else
    {
        G_SETTING_PTR->setValue(DownloadSettingManager::ExpandMode, 135);
        m_ui->leftWidget->setMinimumWidth(70);
        m_ui->leftWidget->setMaximumWidth(70);
        m_ui->expandButton->setLabelIcon(":/functions/lb_right");
        m_ui->fucntionListWidget->resizeMode(true);
    }

    m_expandMode = !m_expandMode;
    DownloadRightAreaWidget::instance()->resizeWidgetGeometry();
}

void DownloadBottomAreaWidget::createSystemTrayIcon()
{
    m_isAvailable = QSystemTrayIcon::isSystemTrayAvailable();
    m_systemTray = new QSystemTrayIcon(DownloadApplication::instance());
    m_systemTray->setIcon(QIcon(":/image/lb_app_logo"));
    m_systemTray->setToolTip(tr("TTKDownloader"));

    m_systemTrayMenu = new DownloadSystemTrayMenu(DownloadApplication::instance());

    if(m_isAvailable)
    {
        m_systemTray->setContextMenu(m_systemTrayMenu);
        m_systemTray->show();
    }
    else
    {
        TTK_INFO_STREAM("Current no systemtray available");
    }

    connect(m_systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}
