#include "downloadsystemtraymenu.h"
#include "downloaduiobject.h"
#include "downloadrightareawidget.h"

DownloadSystemTrayMenu::DownloadSystemTrayMenu(QWidget *parent)
    : QMenu(parent)
{
    setStyleSheet(DownloadUIObject::MMenuStyle02);

    DownloadRightAreaWidget *w = DownloadRightAreaWidget::instance();
    addAction(QIcon(":/contextMenu/lb_new_normal"), tr("NewDownload"), w, SLOT(showNewFileDialog()));
    addAction(QIcon(":/contextMenu/lb_start_normal"), tr("Start"), w, SLOT(startToDownload()));
    addAction(QIcon(":/contextMenu/lb_stop_normal"), tr("Stop"), w, SLOT(stopToDownload()));
    addAction(tr("FloatSetting"));
    addAction(QIcon(":/contextMenu/lb_quit_normal"), tr("appClose"), parent, SLOT(quitWindowClose()));
}

DownloadSystemTrayMenu::~DownloadSystemTrayMenu()
{

}

QString DownloadSystemTrayMenu::getClassName()
{
    return staticMetaObject.className();
}
