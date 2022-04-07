#include "downloadleftareawidget.h"
#include "ui_downloadapplication.h"
#include "downloadsettingwidget.h"
#include "downloadhotkeymanager.h"
#include "downloadapplication.h"

DownloadLeftAreaWidget *DownloadLeftAreaWidget::m_instance = nullptr;

DownloadLeftAreaWidget::DownloadLeftAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    m_instance = this;

    G_HOTKEY_PTR->connectParentObject(this, "Ctrl+O", SLOT(showSettingWidget()));
}

DownloadLeftAreaWidget::~DownloadLeftAreaWidget()
{

}

DownloadLeftAreaWidget *DownloadLeftAreaWidget::instance()
{
    return m_instance;
}

void DownloadLeftAreaWidget::setupUi(Ui::DownloadApplication* ui)
{
    m_ui = ui;

    connect(ui->fucntionListWidget, SIGNAL(currentIndexChanged(int)), SLOT(funcitonIndexChanged(int)));
    connect(ui->settingButton, SIGNAL(clicked()), SLOT(showSettingWidget()));
}

void DownloadLeftAreaWidget::funcitonIndexChanged(int index)
{
    m_ui->centerStackedWidget->setCurrentIndex(index);
    m_ui->startDownloadButton->setVisible(index == 0);
    m_ui->pauseDownloadButton->setVisible(index == 0);
    m_ui->deleteDownloadButton->setVisible(index == 0);
}

void DownloadLeftAreaWidget::showSettingWidget()
{
    DownloadSettingWidget setting;
    connect(&setting, SIGNAL(parameterSettingChanged()), DownloadApplication::instance(), SLOT(parameterSetting()));
    setting.initialize();
    setting.exec();
}
