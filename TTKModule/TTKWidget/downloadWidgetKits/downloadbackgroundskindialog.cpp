#include "downloadbackgroundskindialog.h"
#include "ui_downloadbackgroundskindialog.h"
#include "downloadbackgroundmanager.h"
#include "downloadcolordialog.h"
#include "downloadbackgroundremotewidget.h"
#include "downloadobject.h"
#include "downloadtopareawidget.h"
#include "downloadotherdefine.h"
#include "downloadwidgetutils.h"
#include "downloadextractwrapper.h"
#include "downloaduiobject.h"
#include "downloadotherdefine.h"

#ifdef Q_CC_MSVC
#  include <functional>
#endif
#include <QScrollBar>

DownloadBackgroundSkinDialog::DownloadBackgroundSkinDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadBackgroundSkinDialog)
{
    m_ui->setupUi(this);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(DownloadUIObject::MToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    m_ui->paletteButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->localSkinButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->localPicButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->stackedWidget->setLength(m_ui->stackedWidget->width(), DownloadAnimationStackedWidget::RightToLeft);
#ifdef Q_OS_UNIX
    m_ui->paletteButton->setFocusPolicy(Qt::NoFocus);
    m_ui->localSkinButton->setFocusPolicy(Qt::NoFocus);
    m_ui->localPicButton->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->skinAnimationSiwidget, SIGNAL(buttonClicked(int)), SLOT(backgroundListWidgetChanged(int)));

    //////////////////////////////////////////////////////
    m_backgroundList = new DownloadBackgroundListWidget(this);
    m_ui->recommandScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->recommandScrollArea->setWidgetResizable(true);
    m_ui->recommandScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->recommandScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->recommandScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->recommandScrollArea->setWidget(m_backgroundList);
    m_ui->recommandScrollArea->verticalScrollBar()->setStyleSheet(DownloadUIObject::MScrollBarStyle03);

    m_myBackgroundList = new DownloadBackgroundListWidget(this);
    m_ui->userScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->userScrollArea->setWidgetResizable(true);
    m_ui->userScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->userScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->userScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->userScrollArea->setWidget(m_myBackgroundList);
    m_ui->userScrollArea->verticalScrollBar()->setStyleSheet(DownloadUIObject::MScrollBarStyle03);

    m_remoteBackgroundList = new DownloadBackgroundRemoteWidget(this);
    m_ui->remoteScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_ui->remoteScrollArea->setWidgetResizable(true);
    m_ui->remoteScrollArea->setFrameShape(QFrame::NoFrame);
    m_ui->remoteScrollArea->setFrameShadow(QFrame::Plain);
    m_ui->remoteScrollArea->setAlignment(Qt::AlignVCenter);
    m_ui->remoteScrollArea->setWidget(m_remoteBackgroundList);
    m_ui->remoteScrollArea->verticalScrollBar()->setStyleSheet(DownloadUIObject::MScrollBarStyle03);

    m_myThemeIndex = CURRENT_ITEMS_COUNT;
    addThemeListWidgetItem();
    backgroundListWidgetChanged(0);
    //////////////////////////////////////////////////////
    m_ui->skinTransparentButton->setStyleSheet(DownloadUIObject::MToolButtonStyle06);
    m_ui->skinTransparentLabel->setStyleSheet(DownloadUIObject::MColorStyle03);

    connect(m_ui->skinTransparentButton, SIGNAL(valueChanged(int)), DownloadTopAreaWidget::instance(), SLOT(backgroundTransparentChanged(int)));
    connect(m_ui->skinTransparentButton, SIGNAL(sliderStateChanged(bool)), DownloadTopAreaWidget::instance(), SLOT(backgroundSliderStateChanged(bool)));

    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));
    connect(m_ui->paletteButton, SIGNAL(clicked()), SLOT(showPaletteDialog()));
    connect(m_ui->localPicButton, SIGNAL(clicked()) ,SLOT(showCustomSkinDialog()));
    connect(m_backgroundList, SIGNAL(itemClicked(QString)), SLOT(backgroundListWidgetItemClicked(QString)));
    connect(m_myBackgroundList, SIGNAL(itemClicked(QString)), SLOT(myBackgroundListWidgetItemClicked(QString)));

}

DownloadBackgroundSkinDialog::~DownloadBackgroundSkinDialog()
{
    delete m_ui;
    delete m_backgroundList;
    delete m_myBackgroundList;
    delete m_remoteBackgroundList;
}

QPixmap DownloadBackgroundSkinDialog::setMBackground(QString &name)
{
    QString path = USER_THEME_DIR_FULL + name + TKM_FILE;
    DownloadBackgroundSkinDialog::themeValidCheck(name, path);
    G_BACKGROUND_PTR->setBackground(path);

    DownloadBackgroundImage image;
    return DownloadExtractWrapper::outputSkin(&image, path) ? image.m_pix : QPixmap();
}

bool DownloadBackgroundSkinDialog::themeValidCheck(QString &name, QString &path)
{
    if(!QFile::exists(path))
    {
        QString orPath = QString("%1%2%3").arg(THEME_DIR_FULL).arg(name).arg(TKM_FILE);
        if(QFile::exists(orPath))
        {
            QFile::copy(orPath, QString("%1%2%3").arg(USER_THEME_DIR_FULL).arg(name).arg(TKM_FILE));
        }
        else
        {
            name = "theme-1";
            orPath = QString("%1%2%3").arg(THEME_DIR_FULL).arg(name).arg(TKM_FILE);
            QFile::copy(orPath, QString("%1%2%3").arg(USER_THEME_DIR_FULL).arg(name).arg(TKM_FILE));
        }
        return false;
    }
    return true;
}

QString DownloadBackgroundSkinDialog::cpoyArtFileToLocal(const QString &path)
{
    int index = cpoyFileToLocal(path);
    return (index != -1) ? QString("theme-%1").arg(index + 1) : QString();
}

void DownloadBackgroundSkinDialog::updateArtFileTheme(const QString &theme)
{
    QString des = QString("%1%2%3").arg(USER_THEME_DIR_FULL).arg(theme).arg(TKM_FILE);
    m_myBackgroundList->createItem(theme, des, true);
    m_myBackgroundList->updateLastedItem();
}

void DownloadBackgroundSkinDialog::setCurrentBgTheme(const QString &theme, int alpha)
{
    m_backgroundList->setCurrentItemName(theme);
    m_myBackgroundList->setCurrentItemName(theme);

    m_ui->skinTransparentButton->setValue(alpha);
    setSkinTransToolText(alpha);
}

void DownloadBackgroundSkinDialog::setSkinTransToolText(int value)
{
    m_ui->skinTransparentButton->setText(QString("%1%").arg(value));
}

void DownloadBackgroundSkinDialog::showPaletteDialog()
{
    const QColor &color = DownloadColorDialog::popup();
    if(color.isValid())
    {
        QPixmap pix(1, 1);
        pix.fill(color);
        if(pix.save(DOWNLOAD_COLOR_FILE))
        {
            showPaletteDialog(DOWNLOAD_COLOR_FILE);
        }
        QFile::remove(DOWNLOAD_COLOR_FILE);
    }
}

void DownloadBackgroundSkinDialog::showPaletteDialog(const QString &path)
{
    cpoyFileFromLocal(path);
    m_myBackgroundList->updateLastedItem();
}

void DownloadBackgroundSkinDialog::showCustomSkinDialog()
{
    QString customSkinPath = DownloadUtils::Widget::openFileDialog(this);
    if(customSkinPath.isEmpty())
    {
        return;
    }
    cpoyFileFromLocal(customSkinPath);
    m_myBackgroundList->updateLastedItem();
}

void DownloadBackgroundSkinDialog::backgroundListWidgetChanged(int index)
{
    QWidget *toolWidget = m_remoteBackgroundList->createFunctionsWidget(index != 2, this);
    if(!toolWidget->isVisible())
    {
        toolWidget->show();
        QRect rect = m_ui->stackedWidget->geometry();
        m_ui->stackedWidget->setGeometry(QRect(rect.x(), rect.y() + toolWidget->height(), rect.width(), rect.height() - toolWidget->height()));
    }

    if(m_ui->stackedWidget->currentIndex() == index)
    {
        return;
    }

    m_remoteBackgroundList->abort();
    if(index == 2)
    {
        m_remoteBackgroundList->init();
    }

    m_ui->localSkinButton->setVisible(index == 0);
    m_ui->localPicButton->setVisible(index == 0);

    m_ui->stackedWidget->setIndex(0, 0);
    m_ui->stackedWidget->start(index);
}

void DownloadBackgroundSkinDialog::backgroundListWidgetItemClicked(const QString &name)
{
    if(!m_myBackgroundList->contains(name))
    {
        QString path = QString("%1%2%3").arg(USER_THEME_DIR_FULL).arg(name).arg(TKM_FILE);
        QFile::copy(QString("%1%2%3").arg(THEME_DIR_FULL).arg(name).arg(TKM_FILE), path);
        m_myBackgroundList->createItem(name, path, true);
    }
    listWidgetItemClicked(m_myBackgroundList, name);
}

void DownloadBackgroundSkinDialog::myBackgroundListWidgetItemClicked(const QString &name)
{
    listWidgetItemClicked(m_backgroundList, name);
}

void DownloadBackgroundSkinDialog::remoteBackgroundListWidgetItemClicked(const QString &name)
{
    DownloadBackgroundImage image;
    m_remoteBackgroundList->outputRemoteSkin(image, name);
    if(!image.isValid())
    {
        return;
    }

    if(!m_myBackgroundList->contains(image))
    {
        int index = cpoyFileToLocalIndex();
        QString theme = QString("theme-%1").arg(index + 1);
        QString des = QString("%1%2%3").arg(USER_THEME_DIR_FULL).arg(theme).arg(TKM_FILE);
        DownloadExtractWrapper::inputSkin(&image, des);

        m_myBackgroundList->createItem(theme, des, true);
        listWidgetItemClicked(m_myBackgroundList, theme);
    }
    else
    {
        DownloadBackgroundListItem *it = m_myBackgroundList->find(image);
        if(it)
        {
            listWidgetItemClicked(m_myBackgroundList, it->fileName());
        }
    }
}

int DownloadBackgroundSkinDialog::exec()
{
    setBackgroundPixmap(m_ui->background, size());
    return DownloadAbstractMoveDialog::exec();
}

void DownloadBackgroundSkinDialog::listWidgetItemClicked(DownloadBackgroundListWidget *item, const QString &name)
{
    DownloadTopAreaWidget::instance()->backgroundSkinChanged(name);

    item->clearSelectState();
    item->setCurrentItemName(name);

    QString s(name);
    QString path = USER_THEME_DIR_FULL + s + TKM_FILE;
    DownloadBackgroundSkinDialog::themeValidCheck(s, path);
    G_BACKGROUND_PTR->setBackground(path);
    emit G_BACKGROUND_PTR->backgroundHasChanged();
}

void DownloadBackgroundSkinDialog::addThemeListWidgetItem()
{
    QList<QFileInfo> files(QDir(THEME_DIR_FULL).entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name));
    for(const QFileInfo &info : qAsConst(files))
    {
        m_backgroundList->createItem(info.baseName(), info.filePath(), false);
    }

    files = QDir(USER_THEME_DIR_FULL).entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    for(const QFileInfo &info : qAsConst(files))
    {
        m_myBackgroundList->createItem(info.baseName(), info.filePath(), true);
    }
}

void DownloadBackgroundSkinDialog::cpoyFileFromLocal(const QString &path)
{
    int index = cpoyFileToLocal(path);
    if(index != -1)
    {
        m_myThemeIndex = index;
        QString des = QString("%1theme-%2%3").arg(USER_THEME_DIR_FULL).arg(m_myThemeIndex + 1).arg(TKM_FILE);
        m_myBackgroundList->createItem(QString("theme-%1").arg(m_myThemeIndex + 1), des, true);
    }
}

int DownloadBackgroundSkinDialog::cpoyFileToLocalIndex()
{
    QList<QFileInfo> files(QDir(USER_THEME_DIR_FULL).entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name));
    TTKIntList data;
    for(const QFileInfo &info : qAsConst(files))
    {
        QString fileName = info.baseName();
        fileName = fileName.split(TTK_DEFAULT_STR).last();
        data << fileName.trimmed().toInt();
    }
    std::sort(data.begin(), data.end(), std::greater<int>());

    int index = CURRENT_ITEMS_COUNT;
    if(!data.isEmpty())
    {
        index = data.first();
        if(index < CURRENT_ITEMS_COUNT)
        {
            index = CURRENT_ITEMS_COUNT;
        }
    }

    return index;
}

int DownloadBackgroundSkinDialog::cpoyFileToLocal(const QString &path)
{
    int index = cpoyFileToLocalIndex();

    QString des = QString("%1theme-%2%3").arg(USER_THEME_DIR_FULL).arg(index + 1).arg(TKM_FILE);
    DownloadBackgroundImage image;
    image.m_pix = QPixmap(path);
    return DownloadExtractWrapper::inputSkin(&image, des) ? index : -1;
}
