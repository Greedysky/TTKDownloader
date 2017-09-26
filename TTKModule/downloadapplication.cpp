#include "downloadapplication.h"
#include "ui_downloadapplication.h"
#include "downloadbottomareawidget.h"
#include "downloadtopareawidget.h"
#include "downloadrightareawidget.h"
#include "downloadleftareawidget.h"
#include "downloadapplicationobject.h"
#include "downloadsettingmanager.h"
#include "downloadsysconfigmanager.h"
#include "downloadhotkeymanager.h"
#include "downloaduiobject.h"
#include "downloadversion.h"

#include <QResizeEvent>

DownloadApplication *DownloadApplication::m_instance = nullptr;

DownloadApplication::DownloadApplication(QWidget *parent)
    : DownloadAbstractMoveResizeWidget(parent),
      m_ui(new Ui::DownloadApplication)
{
    m_instance = this;
//#ifdef DOWNLOAD_GREATER_NEW
    setAttribute(Qt::WA_TranslucentBackground, false);
//#endif

    m_applicationObject = new DownloadApplicationObject(this);
    m_topAreaWidget = new DownloadTopAreaWidget(this);
    m_rightAreaWidget = new DownloadRightAreaWidget(this);
    m_leftAreaWidget = new DownloadLeftAreaWidget(this);
    m_bottomAreaWidget = new DownloadBottomAreaWidget(this);
    ////////////////////////////////////////////////
    m_ui->setupUi(this);
    QSize size = M_SETTING_PTR->value(DownloadSettingManager::ScreenSize).toSize();
    setMinimumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    setMaximumSize(size.width(), size.height());
    ////////////////////////////////////////////////
    m_bottomAreaWidget->setupUi(m_ui);
    m_topAreaWidget->setupUi(m_ui);
    m_rightAreaWidget->setupUi(m_ui);
    m_leftAreaWidget->setupUi(m_ui);
    m_topAreaWidget->backgroundSliderStateChanged(false);

    m_quitWindowClose = false;

    M_HOTKEY_PTR->connectParentObject(this, "Ctrl+X", SLOT(quitWindowClose()));

    /////////// Mouse tracking
    foreach(QObject *obj, foreachWidget(this))
    {
        QWidget *w = MStatic_cast(QWidget*, obj);
        w->installEventFilter(this);
        w->setMouseTracking(true);
    }

    readXMLConfigFromText();

    m_rightAreaWidget->init();
}

DownloadApplication::~DownloadApplication()
{
    delete m_applicationObject;
    delete m_bottomAreaWidget;
    delete m_topAreaWidget;
    delete m_rightAreaWidget;
    delete m_leftAreaWidget;
    delete m_ui;
}

QString DownloadApplication::getClassName()
{
    return staticMetaObject.className();
}

DownloadApplication *DownloadApplication::instance()
{
    return m_instance;
}

void DownloadApplication::quitWindowClose()
{
    //Write configuration files
    writeXMLConfigToText();
    m_quitWindowClose = true;
    m_applicationObject->windowCloseAnimation();
}

void DownloadApplication::appCreateRightMenu()
{
    QMenu rightClickMenu(this);
    rightClickMenu.setStyleSheet(DownloadUIObject::MMenuStyle02);

    rightClickMenu.addAction(tr("NewDownload(N)"), DownloadRightAreaWidget::instance(), SLOT(showNewFileDialog()));
    rightClickMenu.addSeparator();
    rightClickMenu.addAction(tr("File(F)"));
    rightClickMenu.addAction(tr("Edit(E)"));
    rightClickMenu.addAction(tr("Plan"));
    rightClickMenu.addSeparator();
    rightClickMenu.addAction(tr("ResetWindow"), m_applicationObject, SLOT(appResetWindow()));
    rightClickMenu.addAction(QIcon(":/contextMenu/lb_setting_normal"), tr("Setting(O)"), DownloadLeftAreaWidget::instance(), SLOT(showSettingWidget()));
    rightClickMenu.addSeparator();

    QMenu aboutInfo(tr("About"), &rightClickMenu);
    aboutInfo.addAction(tr("Update"), m_applicationObject, SLOT(appVersionUpdate()));
    aboutInfo.addAction(QIcon(":/image/lb_player_logo"), tr("Version") + QString(DOWNLOAD_VERSION_STR) + QString(DOWNLOAD_VER_TIME_STR),
                        m_applicationObject, SLOT(appAboutUs()));
    rightClickMenu.addMenu(&aboutInfo);
    rightClickMenu.addSeparator();
    rightClickMenu.addAction(tr("appClose(X)"), this, SLOT(quitWindowClose()));
    rightClickMenu.exec(QCursor::pos());
}

void DownloadApplication::resizeEvent(QResizeEvent *event)
{
    if(!m_quitWindowClose)
    {
        M_SETTING_PTR->setValue(DownloadSettingManager::WidgetSize, size());
        m_topAreaWidget->backgroundThemeChangedByResize();
        m_rightAreaWidget->resizeWindow();
        DownloadAbstractMoveResizeWidget::resizeEvent(event);
    }
    else
    {
        setMinimumSize(0, 0); ///remove fixed size
        m_ui->background->stop();
        event->ignore();
    }
}
void DownloadApplication::closeEvent(QCloseEvent *event)
{
    DownloadAbstractMoveResizeWidget::closeEvent(event);
    event->ignore();
    if(!m_bottomAreaWidget->getSystemCloseConfig() &&
        m_bottomAreaWidget->systemTrayIsVisible() )
    {
        hide();
        m_bottomAreaWidget->showMessage(tr("Prompt"),
                                        tr("TTKDownloader will run in the background"));
    }
    else
    {
        quitWindowClose();
    }
}

void DownloadApplication::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->pos().y() <= m_ui->topWidget->height())
    {
        DownloadAbstractMoveResizeWidget::mouseDoubleClickEvent(event);
    }
    else
    {
        event->ignore();
    }
}

void DownloadApplication::readXMLConfigFromText()
{
    DownloadSysConfigManager xml;

    if(!xml.readXMLConfig())//open file
    {
        return;
    }
    xml.readSysLoadConfig();

#ifdef Q_OS_UNIX
    //Disable  window quit mode on unix
    M_SETTING_PTR->setValue(DownloadSettingManager::WindowQuitModeChoiced, false);
#endif

    //Set the current background color and alpha value
    m_topAreaWidget->setParameters(M_SETTING_PTR->value(DownloadSettingManager::BgThemeChoiced).toString(),
                                   M_SETTING_PTR->value(DownloadSettingManager::BgTransparentChoiced).toInt());

    //When the configuration is close to the direct exit
    m_bottomAreaWidget->setSystemCloseConfig(M_SETTING_PTR->value(DownloadSettingManager::CloseEventChoiced).toInt());

    //Reset geometry
    setGeometry( xml.readWindowGeometry() );

}

void DownloadApplication::writeXMLConfigToText()
{
    DownloadSysConfigManager xml;

    M_SETTING_PTR->setValue(DownloadSettingManager::WidgetPosition, pos());
    M_SETTING_PTR->setValue(DownloadSettingManager::BgThemeChoiced, m_topAreaWidget->getBackgroundPath());
    M_SETTING_PTR->setValue(DownloadSettingManager::BgTransparentChoiced, m_topAreaWidget->getBackgroundAlpha());
    xml.writeXMLConfig();
}
