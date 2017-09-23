#include "downloadrightareawidget.h"
#include "ui_downloadapplication.h"
#include "downloadfunctionuiobject.h"
#include "downloadnewfiledialog.h"
#include "downloadlistwidgets.h"

DownloadRightAreaWidget *DownloadRightAreaWidget::m_instance = nullptr;

DownloadRightAreaWidget::DownloadRightAreaWidget(QWidget *parent)
    : QWidget(parent)
{
    m_instance = this;

    m_listWidget = new DownloadListWidgets(this);
    connect(m_listWidget, SIGNAL(downloadStateChanged(bool)), SLOT(downloadStateChanged(bool)));
}

DownloadRightAreaWidget::~DownloadRightAreaWidget()
{
    delete m_listWidget;
}

QString DownloadRightAreaWidget::getClassName()
{
    return staticMetaObject.className();
}

DownloadRightAreaWidget *DownloadRightAreaWidget::instance()
{
    return m_instance;
}

void DownloadRightAreaWidget::setupUi(Ui::DownloadApplication* ui)
{
    m_ui = ui;

    ui->newDownloadButton->setStyleSheet(DownloadUIObject::MTHDNewDownload);
    ui->newDownloadButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->newDownloadButton->setToolTip(tr("NewDownload"));
    connect(ui->newDownloadButton, SIGNAL(clicked()), SLOT(showNewFileDialog()));

    ui->startDownloadButton->setStyleSheet(DownloadUIObject::MTHDStartDownload);
    ui->startDownloadButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->startDownloadButton->setToolTip(tr("Start"));
    connect(ui->startDownloadButton, SIGNAL(clicked()), m_listWidget, SLOT(start()));

    ui->pauseDownloadButton->setStyleSheet(DownloadUIObject::MTHDStopDownload);
    ui->pauseDownloadButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pauseDownloadButton->setToolTip(tr("Stop"));
    connect(ui->pauseDownloadButton, SIGNAL(clicked()), m_listWidget, SLOT(pause()));

    ui->deleteDownloadButton->setStyleSheet(DownloadUIObject::MTHDDeleteDownload);
    ui->deleteDownloadButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->deleteDownloadButton->setToolTip(tr("Delete"));
    connect(ui->deleteDownloadButton, SIGNAL(clicked()), m_listWidget, SLOT(deleteItemFromList()));

    ui->settingButton->setStyleSheet(DownloadUIObject::MTHDSetting);
    ui->settingButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->settingButton->setToolTip(tr("Setting"));

    ui->centerStackedWidget->addWidget(m_listWidget);
    ui->centerStackedWidget->setCurrentIndex(0);

    ui->startDownloadButton->setEnabled(false);
    ui->pauseDownloadButton->setEnabled(false);
}

void DownloadRightAreaWidget::resizeWindow()
{
    m_listWidget->resizeWindow();
}

void DownloadRightAreaWidget::downloadStateChanged(bool state)
{
    m_ui->startDownloadButton->setEnabled(state);
    m_ui->pauseDownloadButton->setEnabled(!state);
}

void DownloadRightAreaWidget::showNewFileDialog()
{
    DownloadNewFileDialog fileDialog;
    connect(&fileDialog, SIGNAL(setDownloadPath(QStringList)), m_listWidget, SLOT(addItemToList(QStringList)));
    fileDialog.exec();
}

void DownloadRightAreaWidget::startToDownload()
{
    m_listWidget->selectAll();
    m_listWidget->start();
}

void DownloadRightAreaWidget::stopToDownload()
{
    m_listWidget->selectAll();
    m_listWidget->pause();
}
