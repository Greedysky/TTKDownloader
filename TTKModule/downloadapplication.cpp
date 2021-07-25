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
#include "ttkversion.h"

#include <QMenu>
#include <QResizeEvent>

DownloadApplication *DownloadApplication::m_instance = nullptr;

DownloadApplication::DownloadApplication(QWidget *parent)
    : DownloadAbstractMoveResizeWidget(parent),
      m_ui(new Ui::DownloadApplication)
{
    m_instance = this;
//#if TTK_QT_VERSION_CHECK(5,0,0)
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

    M_HOTKEY_PTR->connectParentObject(this, "Ctrl+X", SLOT(quitWindowClose()));

    /////////// Mouse tracking
    for(QObject *obj : foreachWidget(this))
    {
        QWidget *w = TTKStatic_cast(QWidget*, obj);
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

DownloadApplication *DownloadApplication::instance()
{
    return m_instance;
}

void DownloadApplication::showMaximizedWindow()
{
    isMaximized() ? showNormal() : showMaximized();
}

void DownloadApplication::getParameterSetting()
{
    //This attribute is effective immediately.
    bool config = M_SETTING_PTR->value(DownloadSettingManager::CloseEventChoiced).toBool();
    m_bottomAreaWidget->setSystemCloseConfig(config);
    config = M_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionChoiced).toBool();
    config ? m_topAreaWidget->showRemoteSpeedWidget() : m_topAreaWidget->closeRemoteSpeedWidget();
}

void DownloadApplication::quitWindowClose()
{
    //Write configuration files
    writeXMLConfigToText();
    m_applicationObject->windowCloseAnimation();
}

void DownloadApplication::appCreateRightMenu()
{
    QMenu rightClickMenu(this);
    rightClickMenu.setStyleSheet(DownloadUIObject::MMenuStyle02);

    rightClickMenu.addAction(tr("NewDownload(N)"), DownloadRightAreaWidget::instance(), SLOT(showNewFileDialog()));
    rightClickMenu.addSeparator();

    QMenu fileMenu(tr("File(F)"), &rightClickMenu);
    fileMenu.addAction(QIcon(":/contextMenu/lb_new_normal"), tr("NewDownload(N)"), DownloadRightAreaWidget::instance(), SLOT(showNewFileDialog()));
    fileMenu.addSeparator();
    fileMenu.addAction(QIcon(":/contextMenu/lb_start_normal"), tr("Start"), DownloadRightAreaWidget::instance(), SLOT(startToDownload()));
    fileMenu.addAction(QIcon(":/contextMenu/lb_stop_normal"), tr("Stop"), DownloadRightAreaWidget::instance(), SLOT(stopToDownload()));
    fileMenu.addAction(tr("Clear Bin"));
    rightClickMenu.addMenu(&fileMenu);

    QMenu editMenu(tr("Edit(E)"), &rightClickMenu);
    editMenu.addAction(tr("Select All"), DownloadRightAreaWidget::instance(), SLOT(editSelectAll()));
    editMenu.addAction(tr("Reverse Select"), DownloadRightAreaWidget::instance(), SLOT(editReverseSelect()));
    rightClickMenu.addMenu(&editMenu);

    rightClickMenu.addAction(tr("Plan"));
    rightClickMenu.addSeparator();
    rightClickMenu.addAction(tr("ResetWindow"), m_applicationObject, SLOT(appResetWindow()));
    rightClickMenu.addAction(QIcon(":/contextMenu/lb_setting_normal"), tr("Setting(O)"), DownloadLeftAreaWidget::instance(), SLOT(showSettingWidget()));
    rightClickMenu.addSeparator();

    QMenu aboutMenu(tr("About"), &rightClickMenu);
    aboutMenu.addAction(QIcon(":/image/lb_app_logo"), tr("Version") + QString(DOWNLOAD_VERSION_STR) + QString(DOWNLOAD_VER_TIME_STR),
                        m_applicationObject, SLOT(appAboutUs()));
    rightClickMenu.addMenu(&aboutMenu);
    rightClickMenu.addSeparator();
    rightClickMenu.addAction(tr("appClose(X)"), this, SLOT(quitWindowClose()));
    rightClickMenu.exec(QCursor::pos());
}

void DownloadApplication::resizeEvent(QResizeEvent *event)
{
    M_SETTING_PTR->setValue(DownloadSettingManager::WidgetSize, size());
    m_topAreaWidget->backgroundThemeChangedByResize();
    m_rightAreaWidget->resizeWindow();
    DownloadAbstractMoveResizeWidget::resizeEvent(event);
}

void DownloadApplication::closeEvent(QCloseEvent *event)
{
    DownloadAbstractMoveResizeWidget::closeEvent(event);
    event->ignore();
    if(!m_bottomAreaWidget->getSystemCloseConfig() && m_bottomAreaWidget->systemTrayIsVisible())
    {
        hide();
        m_bottomAreaWidget->showMessage(tr("Prompt"), tr("TTKDownloader will run in the background"));
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

    //Set the current background color and alpha value
    m_topAreaWidget->setParameters(M_SETTING_PTR->value(DownloadSettingManager::BgThemeChoiced).toString(),
                                   M_SETTING_PTR->value(DownloadSettingManager::BgTransparentChoiced).toInt());

    M_SETTING_PTR->setValue(DownloadSettingManager::ExpandModeChoiced, 0);

    //Set the current remote widget
    if(M_SETTING_PTR->value(DownloadSettingManager::SkinSuspensionChoiced).toBool())
    {
        m_topAreaWidget->showRemoteSpeedWidget();
    }

    //When the configuration is close to the direct exit
    m_bottomAreaWidget->setSystemCloseConfig(M_SETTING_PTR->value(DownloadSettingManager::CloseEventChoiced).toInt());

    //Reset geometry
    setGeometry(xml.readWindowGeometry());

}

void DownloadApplication::writeXMLConfigToText()
{
    DownloadSysConfigManager xml;

    M_SETTING_PTR->setValue(DownloadSettingManager::WidgetPosition, pos());
    M_SETTING_PTR->setValue(DownloadSettingManager::BgThemeChoiced, m_topAreaWidget->getBackgroundPath());
    M_SETTING_PTR->setValue(DownloadSettingManager::BgTransparentChoiced, m_topAreaWidget->getBackgroundAlpha());
    xml.writeXMLConfig();
}
