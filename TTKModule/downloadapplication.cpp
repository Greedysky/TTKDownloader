#include "downloadapplication.h"
#include "ui_downloadapplication.h"
#include "downloadbottomareawidget.h"
#include "downloadtopareawidget.h"
#include "downloadrightareawidget.h"
#include "downloadleftareawidget.h"
#include "downloadapplicationmodule.h"
#include "downloadsettingmanager.h"
#include "downloadconfigmanager.h"
#include "downloadhotkeymanager.h"
#include "downloadabstractnetwork.h"
#include "downloaduiobject.h"
#include "downloadwidgetutils.h"
#include "ttkversion.h"
#include "ttklogoutput.h"

#include <QMenu>
#include <QResizeEvent>

DownloadApplication *DownloadApplication::m_instance = nullptr;

DownloadApplication::DownloadApplication(QWidget *parent)
    : TTKAbstractMoveResizeWidget(false, parent),
      m_ui(new Ui::DownloadApplication)
{
    m_instance = this;

    m_applicationModule = new DownloadApplicationModule(this);
    m_topAreaWidget = new DownloadTopAreaWidget(this);
    m_rightAreaWidget = new DownloadRightAreaWidget(this);
    m_leftAreaWidget = new DownloadLeftAreaWidget(this);
    m_bottomAreaWidget = new DownloadBottomAreaWidget(this);

    m_ui->setupUi(this);
    const QSize &size = G_SETTING_PTR->value(DownloadSettingManager::ScreenSize).toSize();
    setMinimumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    setMaximumSize(size.width(), size.height());

    m_bottomAreaWidget->setupUi(m_ui);
    m_topAreaWidget->setupUi(m_ui);
    m_rightAreaWidget->setupUi(m_ui);
    m_leftAreaWidget->setupUi(m_ui);
    m_topAreaWidget->backgroundAnimationChanged(false);

    G_HOTKEY_PTR->addHotKey(this, SLOT(quitWindow()));

    // Objects Mouse tracking
    setObjectsTracking({m_ui->background});

    readSystemConfigFromFile();
    //
    m_rightAreaWidget->initialize();

#ifndef QT_NO_SSL
    // ssl support check
    TTK_INFO_STREAM("Application network support ssl:" << (QSslSocket::supportsSsl() ? "true" : "false"));
#  if TTK_QT_VERSION_CHECK(5,0,0)
#    if TTK_QT_VERSION_CHECK(5,4,0)
    TTK_INFO_STREAM("Application network ssl build version:" << QSslSocket::sslLibraryBuildVersionString());
#    endif
    TTK_INFO_STREAM("Application network ssl runtime version:" << QSslSocket::sslLibraryVersionString());
#  endif
#endif
}

DownloadApplication::~DownloadApplication()
{
    delete m_bottomAreaWidget;
    delete m_topAreaWidget;
    delete m_rightAreaWidget;
    delete m_leftAreaWidget;
    delete m_applicationModule;
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

void DownloadApplication::applyParameter()
{
    //This attribute is effective immediately.
    bool config = G_SETTING_PTR->value(DownloadSettingManager::CloseEventMode).toBool();
    m_bottomAreaWidget->setSystemCloseConfig(config);

    config = G_SETTING_PTR->value(DownloadSettingManager::SkinSuspension).toBool();
    config ? m_topAreaWidget->showRemoteSpeedWidget() : m_topAreaWidget->closeRemoteSpeedWidget();

    config = G_SETTING_PTR->value(DownloadSettingManager::LogTrackEnable).toBool();
    config ? TTK::installLogHandler() : TTK::removeLogHandler();
}

void DownloadApplication::quitWindow()
{
    //Write configuration files
    writeSystemConfigToFile();
    m_applicationModule->windowCloseAnimation();
}

void DownloadApplication::createRightMenu()
{
    QMenu menu(this);
    menu.setStyleSheet(TTK::UI::MenuStyle02);
    menu.addAction(tr("NewDownload(N)"), DownloadRightAreaWidget::instance(), SLOT(showNewFileDialog()));
    menu.addSeparator();

    QMenu *fileMenu = menu.addMenu(tr("File(F)"));
    fileMenu->addAction(QIcon(":/contextMenu/lb_new_normal"), tr("NewDownload(N)"), DownloadRightAreaWidget::instance(), SLOT(showNewFileDialog()));
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon(":/contextMenu/lb_start_normal"), tr("Start"), DownloadRightAreaWidget::instance(), SLOT(startToDownload()));
    fileMenu->addAction(QIcon(":/contextMenu/lb_stop_normal"), tr("Stop"), DownloadRightAreaWidget::instance(), SLOT(stopToDownload()));
    fileMenu->addAction(tr("Clear Bin"));

    QMenu *editMenu = menu.addMenu(tr("Edit(E)"));
    editMenu->addAction(tr("Select All"), DownloadRightAreaWidget::instance(), SLOT(editSelectAll()));
    editMenu->addAction(tr("Unselect All"), DownloadRightAreaWidget::instance(), SLOT(editUnselectAll()));
    TTK::Widget::adjustMenuPosition(editMenu);

    menu.addAction(tr("Plan"));
    menu.addSeparator();
    menu.addAction(tr("ResetWindow"), m_applicationModule, SLOT(resetWindowGeometry()));
    menu.addAction(QIcon(":/contextMenu/lb_setting_normal"), tr("Setting(O)"), DownloadLeftAreaWidget::instance(), SLOT(showSettingWidget()));
    menu.addSeparator();

    QMenu *aboutMenu = menu.addMenu(tr("About"));
    aboutMenu->addAction(QIcon(":/image/lb_app_logo"), tr("Version") + QString(TTK_VERSION_STR) + QString(TTK_VERSION_TIME_STR), m_applicationModule, SLOT(showAboutWidget()));

    menu.addSeparator();
    menu.addAction(tr("appClose(X)"), this, SLOT(quitWindow()));
    menu.exec(QCursor::pos());
}

void DownloadApplication::resizeEvent(QResizeEvent *event)
{
    G_SETTING_PTR->setValue(DownloadSettingManager::WidgetSize, size());
    m_topAreaWidget->backgroundThemeChangedByResize();
    m_rightAreaWidget->resizeWidgetGeometry();
    TTKAbstractMoveResizeWidget::resizeEvent(event);
}

void DownloadApplication::closeEvent(QCloseEvent *event)
{
    TTKAbstractMoveResizeWidget::closeEvent(event);
    event->ignore();
    if(!m_bottomAreaWidget->systemCloseConfig() && m_bottomAreaWidget->systemTrayIsVisible())
    {
        hide();
        m_bottomAreaWidget->showMessage(tr("Prompt"), tr("TTKDownloader will run in the background"));
    }
    else
    {
        quitWindow();
    }
}

void DownloadApplication::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(QtPositionY(event) <= m_ui->topWidget->height())
    {
        TTKAbstractMoveResizeWidget::mouseDoubleClickEvent(event);
        if(event->buttons() == Qt::LeftButton)
        {
            isMaximized() ? showNormal() : showMaximized();
        }
    }
    else
    {
        event->ignore();
    }
}

void DownloadApplication::readSystemConfigFromFile()
{
    DownloadConfigManager manager;
    if(!manager.fromFile(COFIG_PATH_FULL))
    {
        return;
    }

    manager.readBuffer();

    //global hotkey
    if(G_SETTING_PTR->value(DownloadSettingManager::HotkeyEnable).toBool())
    {
        QStringList hotkeys = G_SETTING_PTR->value(DownloadSettingManager::HotkeyValue).toString().split(TTK_SPLITER);
        if(hotkeys.count() != G_HOTKEY_PTR->count())
        {
            hotkeys = G_HOTKEY_PTR->defaultKeys();
        }

        for(int i = 0; i < hotkeys.count(); ++i)
        {
            G_HOTKEY_PTR->setHotKey(i, hotkeys[i]);
        }
        //
        G_HOTKEY_PTR->setEnabled(true);
    }

    //Set the current background color and alpha value
    m_topAreaWidget->setBackgroundParameter();

    G_SETTING_PTR->setValue(DownloadSettingManager::ExpandMode, 0);

    //Set the current remote widget
    if(G_SETTING_PTR->value(DownloadSettingManager::SkinSuspension).toBool())
    {
        m_topAreaWidget->showRemoteSpeedWidget();
    }

    //When the configuration is close to the direct exit
    m_bottomAreaWidget->setSystemCloseConfig(G_SETTING_PTR->value(DownloadSettingManager::CloseEventMode).toBool());

    //Reset geometry
    setGeometry(manager.readWindowGeometry());
}

void DownloadApplication::writeSystemConfigToFile()
{
    G_SETTING_PTR->setValue(DownloadSettingManager::WidgetPosition, pos());
    G_SETTING_PTR->setValue(DownloadSettingManager::BackgroundThemeValue, m_topAreaWidget->backgroundPath());
    G_SETTING_PTR->setValue(DownloadSettingManager::BackgroundTransparent, m_topAreaWidget->backgroundTransparent());

    DownloadConfigManager manager;
    if(!manager.load(COFIG_PATH_FULL))
    {
        return;
    }

    manager.writeBuffer();
}
