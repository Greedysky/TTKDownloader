#include "downloadtopareawidget.h"
#include "ui_downloadapplication.h"
#include "downloadtinyuiobject.h"
#include "downloadapplication.h"
#include "downloadbackgroundskindialog.h"
#include "downloadimageutils.h"
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

void DownloadTopAreaWidget::setupUi(Ui::DownloadApplication *ui)
{
    m_ui = ui;

    ui->windowSkinButton->setStyleSheet(TTK::UI::THDSkin);
    ui->windowSkinButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowSkinButton->setToolTip(tr("Skin"));
    connect(ui->windowSkinButton, SIGNAL(clicked()), SLOT(showSkinChangedWindow()));

    ui->windowSettingButton->setStyleSheet(TTK::UI::THDSetting);
    ui->windowSettingButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowSettingButton->setToolTip(tr("Setting"));
    connect(ui->windowSettingButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(createRightMenu()));

    ui->windowMinButton->setStyleSheet(TTK::UI::THDMinimum);
    ui->windowMinButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowMinButton->setToolTip(tr("Minimum"));
    connect(ui->windowMinButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(showMinimized()));

    ui->windowMaxButton->setStyleSheet(TTK::UI::THDMaximum);
    ui->windowMaxButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowMaxButton->setToolTip(tr("Maximum"));
    connect(ui->windowMaxButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(showMaximizedWindow()));

    ui->windowCloseButton->setStyleSheet(TTK::UI::THDClose);
    ui->windowCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->windowCloseButton->setToolTip(tr("Close"));
    connect(ui->windowCloseButton, SIGNAL(clicked()), DownloadApplication::instance(), SLOT(close()));

}

void DownloadTopAreaWidget::setBackgroundParameter()
{
    m_backgroundImagePath = G_SETTING_PTR->value(DownloadSettingManager::BackgroundThemeValue).toString();
    m_backgroundTransparent = G_SETTING_PTR->value(DownloadSettingManager::BackgroundTransparent).toInt();
    drawWindowBackground();
}

const QPixmap& DownloadTopAreaWidget::renderPixmap() const
{
    return m_ui->background->renderPixmap();
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

void DownloadTopAreaWidget::backgroundAnimationChanged(bool state)
{
    m_ui->background->setAnimation(!state);
}

void DownloadTopAreaWidget::showSkinChangedWindow()
{
    if(m_backgroundWidget == nullptr)
    {
        m_backgroundWidget = new DownloadBackgroundSkinDialog(this);
    }

    m_backgroundWidget->setCurrentBackgroundTheme(m_backgroundImagePath, m_backgroundTransparent);
    m_backgroundWidget->exec();
}

void DownloadTopAreaWidget::backgroundTransparentChanged()
{
    drawWindowBackground();
}

void DownloadTopAreaWidget::backgroundTransparentChanged(int index)
{
    if(m_backgroundWidget)
    {
        m_backgroundWidget->setSkinTransToolText(index);
    }

    m_backgroundTransparent = index;
    drawWindowBackgroundByImage();
}

void DownloadTopAreaWidget::backgroundTransparentChanged(const QString &fileName)
{
    drawWindowBackgroundByPath(fileName);
}

void DownloadTopAreaWidget::backgroundThemeChangedByResize()
{
    drawWindowBackgroundByImage();
}

void DownloadTopAreaWidget::backgroundSkinChanged(const QString &fileName)
{
    m_backgroundImagePath = fileName;
    backgroundTransparentChanged();
}

void DownloadTopAreaWidget::drawWindowBackground()
{
    drawWindowBackground(DownloadBackgroundSkinDialog::setBackgroundUrl(m_backgroundImagePath).toImage());
}

void DownloadTopAreaWidget::drawWindowBackground(const QImage &image)
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
    TTK::Image::reRenderImage(average, 35, &origin, &origin);
    G_BACKGROUND_PTR->setBackgroundColor(average);

    m_backgroundImage = origin;
    drawWindowBackgroundByImage();
}

void DownloadTopAreaWidget::drawWindowBackgroundByImage()
{
    float v = TTK::Image::boundValue<float>(1.0f, 0.35f, m_backgroundTransparent);
    DownloadApplication::instance()->setWindowOpacity(v);

    QSize size(G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize());
    QPixmap after(size);
    after.fill(Qt::transparent);
    QPainter paint(&after);
    paint.drawPixmap(0, 0, QPixmap::fromImage(m_backgroundImage.scaled(size, Qt::KeepAspectRatioByExpanding)));

    m_ui->background->setPixmap(after);
}

void DownloadTopAreaWidget::drawWindowBackgroundByPath(const QString &path)
{
    drawWindowBackground(QImage(path));
}
