#include "downloadtopareawidget.h"
#include "ui_downloadapplication.h"
#include "downloadtinyuiobject.h"
#include "downloadapplication.h"
#include "downloadbackgroundskindialog.h"
#include "downloadwidgetutils.h"
#include "downloadsettingmanager.h"
#include "downloadbackgroundmanager.h"
#include "downloadremotewidget.h"

#include <QPainter>

DownloadTopAreaWidget *DownloadTopAreaWidget::m_instance = nullptr;

DownloadTopAreaWidget::DownloadTopAreaWidget(QWidget *parent)
    : QWidget(parent),
      m_remoteWidget(nullptr),
      m_backgroundWidget(nullptr)
{
    m_instance = this;
}

DownloadTopAreaWidget::~DownloadTopAreaWidget()
{
    delete m_remoteWidget;
    delete m_backgroundWidget;
}

DownloadTopAreaWidget *DownloadTopAreaWidget::instance()
{
    return m_instance;
}

void DownloadTopAreaWidget::setupUi(Ui::DownloadApplication* ui)
{
    m_ui = ui;

    ui->windowSkinButton->setStyleSheet(DownloadUIObject::MTHDSkin);
    ui->windowSkinButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowSkinButton->setToolTip(tr("Skin"));
    connect(ui->windowSkinButton, SIGNAL(clicked()), SLOT(showSkinChangedWindow()));

    ui->windowSettingButton->setStyleSheet(DownloadUIObject::MTHDSetting);
    ui->windowSettingButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowSettingButton->setToolTip(tr("Setting"));
    connect(ui->windowSettingButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(appCreateRightMenu()));

    ui->windowMinButton->setStyleSheet(DownloadUIObject::MTHDMinimum);
    ui->windowMinButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowMinButton->setToolTip(tr("Minimum"));
    connect(ui->windowMinButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(showMinimized()));

    ui->windowMaxButton->setStyleSheet(DownloadUIObject::MTHDMaximum);
    ui->windowMaxButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowMaxButton->setToolTip(tr("Maximum"));
    connect(ui->windowMaxButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(showMaximizedWindow()));

    ui->windowCloseButton->setStyleSheet(DownloadUIObject::MTHDClose);
    ui->windowCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowCloseButton->setToolTip(tr("Close"));
    connect(ui->windowCloseButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(close()));

}

void DownloadTopAreaWidget::setParameters(const QString &skin, int alpha)
{
    m_backgroundImagePath = skin;
    m_backgroundAlpha = alpha;
    drawWindowBackgroundRect();
}

QPixmap DownloadTopAreaWidget::rendererPixmap() const
{
    return m_ui->background->rendererPixmap();
}

void DownloadTopAreaWidget::showRemoteSpeedWidget()
{
    if(m_remoteWidget)
    {
        return;
    }

    m_remoteWidget = new DownloadRemoteWidget;
    m_remoteWidget->show();
}

void DownloadTopAreaWidget::closeRemoteSpeedWidget()
{
    if(m_remoteWidget)
    {
        m_remoteWidget->deleteLater();
        m_remoteWidget = nullptr;
    }
}

void DownloadTopAreaWidget::updateRemoteSpeedText(int value)
{
    if(m_remoteWidget)
    {
        m_remoteWidget->setValue(value);
    }
}

void DownloadTopAreaWidget::backgroundSliderStateChanged(bool state)
{
    m_ui->background->setNoAnimation(state);
}

void DownloadTopAreaWidget::showSkinChangedWindow()
{
    if(m_backgroundWidget == nullptr)
    {
        m_backgroundWidget = new DownloadBackgroundSkinDialog(this);
    }
    m_backgroundWidget->setCurrentBgTheme(m_backgroundImagePath, m_backgroundAlpha);
    m_backgroundWidget->exec();
}

void DownloadTopAreaWidget::backgroundTransparentChanged()
{
    drawWindowBackgroundRect();
}

void DownloadTopAreaWidget::backgroundTransparentChanged(int index)
{
    if(m_backgroundWidget)
    {
        m_backgroundWidget->setSkinTransToolText(index);
    }
    m_backgroundAlpha = index;
    drawWindowBackgroundRectString();
}

void DownloadTopAreaWidget::backgroundTransparentChanged(const QString &fileName)
{
    drawWindowBackgroundRectString(fileName);
}

void DownloadTopAreaWidget::backgroundThemeChangedByResize()
{
    drawWindowBackgroundRectString();
}

void DownloadTopAreaWidget::backgroundSkinChanged(const QString &fileName)
{
    m_backgroundImagePath = fileName;
    backgroundTransparentChanged();
}

void DownloadTopAreaWidget::drawWindowBackgroundRect()
{
    drawWindowBackgroundRect(DownloadBackgroundSkinDialog::setMBackground(m_backgroundImagePath).toImage());
}

void DownloadTopAreaWidget::drawWindowBackgroundRect(const QImage &image)
{
    if(image.isNull())
    {
        return;
    }

    QImage origin(image);
    if(!origin.colorTable().isEmpty())
    {
        origin = origin.convertToFormat(QImage::Format_ARGB32);
    }

    qint64 average = 0;
    DownloadUtils::Widget::reRenderImage(average, 35, &origin, &origin);
    G_BACKGROUND_PTR->setBackgroundColor(average);

    m_backgroundImage = origin;
    drawWindowBackgroundRectString();
}

void DownloadTopAreaWidget::drawWindowBackgroundRectString()
{
    float v = DownloadUtils::Widget::reRenderValue<float>(1.0f, 0.35f, m_backgroundAlpha);
    DownloadApplication::instance()->setWindowOpacity(v);

    QSize size(G_SETTING_PTR->value(DownloadSettingManager::Config::WidgetSize).toSize());
    QPixmap after(size);
    after.fill(Qt::transparent);
    QPainter paint(&after);
    paint.drawPixmap(0, 0, QPixmap::fromImage(m_backgroundImage.scaled(size, Qt::KeepAspectRatioByExpanding)));
    paint.end();

    m_ui->background->setPixmap(after);
}

void DownloadTopAreaWidget::drawWindowBackgroundRectString(const QString &path)
{
    drawWindowBackgroundRect(QImage(path));
}
