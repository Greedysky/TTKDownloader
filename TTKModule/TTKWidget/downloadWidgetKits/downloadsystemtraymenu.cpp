#include "downloadsystemtraymenu.h"
#include "downloaduiobject.h"
#include "downloadrightareawidget.h"
#include "downloadtopareawidget.h"
#include "downloadsettingmanager.h"

DownloadSystemTrayMenu::DownloadSystemTrayMenu(QWidget *parent)
    : QMenu(parent)
{
    setStyleSheet(DownloadUIObject::MMenuStyle02);

    DownloadRightAreaWidget *rw = DownloadRightAreaWidget::instance();
    addAction(QIcon(":/contextMenu/lb_new_normal"), tr("NewDownload(N)"), rw, SLOT(showNewFileDialog()));
    addAction(QIcon(":/contextMenu/lb_start_normal"), tr("Start"), rw, SLOT(startToDownload()));
    addAction(QIcon(":/contextMenu/lb_stop_normal"), tr("Stop"), rw, SLOT(stopToDownload()));

    DownloadTopAreaWidget *tw = DownloadTopAreaWidget::instance();
    m_floatMenu = new QMenu(tr("FloatSetting"), this);
    m_floatMenu->addAction(tr("Show"), tw, SLOT(showRemoteSpeedWidget()));
    m_floatMenu->addAction(tr("Hide"), tw, SLOT(closeRemoteSpeedWidget()));
    addMenu(m_floatMenu);

    addAction(QIcon(":/contextMenu/lb_quit_normal"), tr("appClose(X)"), parent, SLOT(quitWindowClose()));
}

DownloadSystemTrayMenu::~DownloadSystemTrayMenu()
{
    delete m_floatMenu;
}

void DownloadSystemTrayMenu::showEvent(QShowEvent *event)
{
    QMenu::showEvent(event);
    if(m_floatMenu)
    {
        bool ishow = G_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionChoiced).toBool();
        QList<QAction*> acts = m_floatMenu->actions();
        if(acts.count() >= 2)
        {
            acts[0]->setIcon(QIcon(ishow ? ":/contextMenu/lb_selected" : QString()));
            acts[1]->setIcon(QIcon(!ishow ? ":/contextMenu/lb_selected" : QString()));
        }
    }
}
