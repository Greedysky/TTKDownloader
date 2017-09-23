#include "downloadleftareawidget.h"
#include "ui_downloadapplication.h"

DownloadLeftAreaWidget *DownloadLeftAreaWidget::m_instance = nullptr;

DownloadLeftAreaWidget::DownloadLeftAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    m_instance = this;
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
