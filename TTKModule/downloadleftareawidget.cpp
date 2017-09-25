#include "downloadleftareawidget.h"
#include "ui_downloadapplication.h"
#include "downloadsettingwidget.h"
#include "downloadhotkeymanager.h"

DownloadLeftAreaWidget *DownloadLeftAreaWidget::m_instance = nullptr;

DownloadLeftAreaWidget::DownloadLeftAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    m_instance = this;

    M_HOTKEY_PTR->connectParentObject(this, "Ctrl+O", SLOT(showSettingWidget()));

}

DownloadLeftAreaWidget::~DownloadLeftAreaWidget()
{

}

QString DownloadLeftAreaWidget::getClassName()
{
    return staticMetaObject.className();
}

DownloadLeftAreaWidget *DownloadLeftAreaWidget::instance()
{
    return m_instance;
}

void DownloadLeftAreaWidget::setupUi(Ui::DownloadApplication* ui)
{
    m_ui = ui;
}

void DownloadLeftAreaWidget::showSettingWidget()
{
    DownloadSettingWidget setting;
    setting.initControllerParameter();
    setting.exec();
}
