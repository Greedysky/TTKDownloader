#include "downloadbackgroundskindialog.h"
#include "ui_downloadbackgroundskindialog.h"
#include "downloadbackgroundremotewidget.h"
#include "downloadbackgroundmanager.h"
#include "downloadcolordialog.h"
#include "downloadobject.h"
#include "downloadtopareawidget.h"
#include "downloadotherdefine.h"
#include "downloadfileutils.h"
#include "downloadextractmanager.h"
#include "downloaduiobject.h"
#include "downloadotherdefine.h"
#include "downloadwidgetutils.h"

#ifdef Q_CC_MSVC
#  include <functional>
#endif
static constexpr int CURRENT_ITEMS_COUNT = 58;

DownloadBackgroundSkinDialog::DownloadBackgroundSkinDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadBackgroundSkinDialog),
      m_stackThemeIndex(CURRENT_ITEMS_COUNT)
{
    m_ui->setupUi(this);
    setBackgroundLabel(m_ui->background);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(TTK::UI::ToolButtonStyle03);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    m_ui->paletteButton->setStyleSheet(TTK::UI::PushButtonStyle03);
    m_ui->customSkin->setStyleSheet(TTK::UI::PushButtonStyle03);
    m_ui->stackedWidget->setLength(m_ui->stackedWidget->width(), DownloadAnimationStackedWidget::Module::RightToLeft);
#ifdef Q_OS_UNIX
    m_ui->paletteButton->setFocusPolicy(Qt::NoFocus);
    m_ui->customSkin->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->skinAnimationSiwidget, SIGNAL(buttonClicked(int)), SLOT(backgroundListWidgetChanged(int)));

    m_cacheBackgroundList = new DownloadBackgroundListWidget(this);
    m_cacheBackgroundList->setType(DownloadBackgroundListWidget::CachedModule);
    TTK::Widget::generateVScrollAreaStyle(m_ui->recommendScrollArea, m_cacheBackgroundList);

    m_stackBackgroundList = new DownloadBackgroundListWidget(this);
    m_stackBackgroundList->setType(DownloadBackgroundListWidget::StackedModule);
    TTK::Widget::generateVScrollAreaStyle(m_ui->userScrollArea, m_stackBackgroundList);

    m_onlineBackgroundList = new DownloadBackgroundOnlineWidget(this);
    TTK::Widget::generateVScrollAreaStyle(m_ui->remoteScrollArea, m_onlineBackgroundList);

    addThemeListWidgetItem();
    backgroundListWidgetChanged(0);

    m_ui->skinTransparentButton->setStyleSheet(TTK::UI::ToolButtonStyle05);
    m_ui->skinTransparentLabel->setStyleSheet(TTK::UI::ColorStyle02);

    connect(m_ui->skinTransparentButton, SIGNAL(valueChanged(int)), DownloadTopAreaWidget::instance(), SLOT(backgroundTransparentChanged(int)));
    connect(m_ui->skinTransparentButton, SIGNAL(sliderStateChanged(bool)), DownloadTopAreaWidget::instance(), SLOT(backgroundAnimationChanged(bool)));

    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));
    connect(m_ui->paletteButton, SIGNAL(clicked()), SLOT(showPaletteDialog()));
    connect(m_ui->customSkin, SIGNAL(clicked()) ,SLOT(showCustomSkinDialog()));

    connect(m_cacheBackgroundList, SIGNAL(itemClicked(int,QString)), SLOT(classicalListWidgetItemClicked(int,QString)));
    connect(m_stackBackgroundList, SIGNAL(itemClicked(int,QString)), SLOT(classicalListWidgetItemClicked(int,QString)));
}

DownloadBackgroundSkinDialog::~DownloadBackgroundSkinDialog()
{
    delete m_ui;
    delete m_cacheBackgroundList;
    delete m_stackBackgroundList;
    delete m_onlineBackgroundList;
}

QPixmap DownloadBackgroundSkinDialog::setBackgroundUrl(QString &name)
{
    QString path = USER_THEME_DIR_FULL + name + TKM_FILE;
    DownloadBackgroundSkinDialog::isValid(name, path);
    G_BACKGROUND_PTR->setBackgroundUrl(path);

    DownloadBackgroundImage image;
    return DownloadExtractManager::outputSkin(&image, path) ? image.m_pix : QPixmap();
}

bool DownloadBackgroundSkinDialog::isValid(QString &name, QString &path)
{
    if(QFile::exists(path))
    {
        return true;
    }

    QString orPath = QString("%1%2%3").arg(THEME_DIR_FULL, name, TKM_FILE);
    if(QFile::exists(orPath))
    {
        QFile::copy(orPath, QString("%1%2%3").arg(USER_THEME_DIR_FULL, name, TKM_FILE));
    }
    else
    {
        name = "theme-1";
        orPath = QString("%1%2%3").arg(THEME_DIR_FULL, name, TKM_FILE);
        QFile::copy(orPath, QString("%1%2%3").arg(USER_THEME_DIR_FULL, name, TKM_FILE));
    }
    return false;
}

void DownloadBackgroundSkinDialog::setCurrentBackgroundTheme(const QString &theme, int background)
{
    m_cacheBackgroundList->setCurrentItemName(theme);
    m_stackBackgroundList->setCurrentItemName(theme);

    m_ui->skinTransparentButton->setValue(background);
    setSkinTransToolText(background);
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
        if(pix.save(TTK_COLOR_FILE))
        {
            showPaletteDialog(TTK_COLOR_FILE);
        }
        QFile::remove(TTK_COLOR_FILE);
    }
}

void DownloadBackgroundSkinDialog::showPaletteDialog(const QString &path)
{
    cpoyFileFromLocal(path);
    m_stackBackgroundList->updateLastItem();
}

void DownloadBackgroundSkinDialog::showCustomSkinDialog()
{
    const QString &path = TTK::File::getOpenFileName(this);
    if(path.isEmpty())
    {
        return;
    }

    if(TTK_FILE_SUFFIX(QFileInfo(path)) == TKM_FILE_SUFFIX)
    {
        const int index = cpoyFileToLocalIndex();
        if(index != -1)
        {
            m_stackThemeIndex = index;
            const QString &des = QString("%1theme-%2%3").arg(USER_THEME_DIR_FULL).arg(index + 1).arg(TKM_FILE);
            QFile::copy(path, des);
            m_stackBackgroundList->addCellItem(QString("theme-%1").arg(index + 1), des, true);
        }
    }
    else
    {
        cpoyFileFromLocal(path);
    }

    m_stackBackgroundList->updateLastItem();
}

void DownloadBackgroundSkinDialog::backgroundListWidgetChanged(int index)
{
    QWidget *toolWidget = m_onlineBackgroundList->createFunctionsWidget(index != 2, this);
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

    m_onlineBackgroundList->abort();

    if(index == 2)
    {
        m_onlineBackgroundList->initialize();
    }

    m_ui->stackedWidget->setIndex(0, 0);
    m_ui->stackedWidget->start(index);
}

void DownloadBackgroundSkinDialog::classicalListWidgetItemClicked(int type, const QString &name)
{
    if(type == DownloadBackgroundListWidget::CachedModule)
    {
        if(!m_stackBackgroundList->contains(name))
        {
            const QString &path = QString("%1%2%3").arg(USER_THEME_DIR_FULL, name, TKM_FILE);
            QFile::copy(QString("%1%2%3").arg(THEME_DIR_FULL, name, TKM_FILE), path);
            m_stackBackgroundList->addCellItem(name, path, true);
        }

        listWidgetItemClicked(m_stackBackgroundList, name);
    }
    else
    {
        listWidgetItemClicked(m_cacheBackgroundList, name);
    }
}

void DownloadBackgroundSkinDialog::remoteListWidgetItemClicked(int type, const QString &name)
{
    Q_UNUSED(type);
    DownloadBackgroundImage image;
    m_onlineBackgroundList->outputRemoteSkin(image, name);

    if(!image.isValid())
    {
        return;
    }

    m_cacheBackgroundList->clearState();
    if(!m_stackBackgroundList->contains(image))
    {
        const int index = cpoyFileToLocalIndex();
        const QString &theme = QString("theme-%1").arg(index + 1);
        const QString &des = QString("%1%2%3").arg(USER_THEME_DIR_FULL, theme, TKM_FILE);
        DownloadExtractManager::inputSkin(&image, des);

        m_stackBackgroundList->addCellItem(theme, des, true);
        listWidgetItemClicked(m_stackBackgroundList, theme);
    }
    else
    {
        const DownloadBackgroundListItem *it = m_stackBackgroundList->find(image);
        if(it)
        {
            listWidgetItemClicked(m_stackBackgroundList, it->fileName());
        }
    }
}

void DownloadBackgroundSkinDialog::listWidgetItemClicked(DownloadBackgroundListWidget *item, const QString &name)
{
    DownloadTopAreaWidget::instance()->backgroundSkinChanged(name);

    item->clearState();
    item->setCurrentItemName(name);

    QString s(name);
    QString path = USER_THEME_DIR_FULL + s + TKM_FILE;
    DownloadBackgroundSkinDialog::isValid(s, path);

    G_BACKGROUND_PTR->setBackgroundUrl(path);
}

void DownloadBackgroundSkinDialog::addThemeListWidgetItem()
{
    addThemeListWidgetItem(m_cacheBackgroundList, THEME_DIR_FULL, false);
    addThemeListWidgetItem(m_stackBackgroundList, USER_THEME_DIR_FULL, true);
}

void DownloadBackgroundSkinDialog::addThemeListWidgetItem(DownloadBackgroundListWidget *item, const QString &dir, bool state)
{
    TTKIntList items;
    findThemeListByPath(dir, items);
    std::sort(items.begin(), items.end());

    for(const int index : qAsConst(items))
    {
        const QFileInfo fin(QString("%1theme-%2%3").arg(dir).arg(index).arg(TKM_FILE));
        item->addCellItem(fin.baseName(), fin.filePath(), state);
    }
}

void DownloadBackgroundSkinDialog::cpoyFileFromLocal(const QString &path)
{
    const int index = cpoyFileToLocal(path);
    if(index != -1)
    {
        m_stackThemeIndex = index;
        const QString &des = QString("%1theme-%2%3").arg(USER_THEME_DIR_FULL).arg(m_stackThemeIndex + 1).arg(TKM_FILE);
        m_stackBackgroundList->addCellItem(QString("theme-%1").arg(m_stackThemeIndex + 1), des, true);
    }
}

void DownloadBackgroundSkinDialog::findThemeListByPath(const QString &dir, TTKIntList &items)
{
    items.clear();
    const QStringList files(QDir(dir).entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name));

    for(const QString &path : qAsConst(files))
    {
        const QFileInfo fin(path);
        if(TTK_FILE_SUFFIX(fin) != TKM_FILE_SUFFIX)
        {
            continue;
        }

        const QStringList &list = fin.baseName().split(TTK_DEFAULT_STR);
        if(list.count() < 2)
        {
            continue;
        }

        const QString &fileName = list.last();
        items << fileName.trimmed().toInt();
    }
}

int DownloadBackgroundSkinDialog::cpoyFileToLocalIndex()
{
    TTKIntList items;
    findThemeListByPath(USER_THEME_DIR_FULL, items);
    std::sort(items.begin(), items.end(), std::greater<int>());

    int index = CURRENT_ITEMS_COUNT;
    if(!items.isEmpty())
    {
        index = items.first();
        if(index < CURRENT_ITEMS_COUNT)
        {
            index = CURRENT_ITEMS_COUNT;
        }
    }

    return index;
}

int DownloadBackgroundSkinDialog::cpoyFileToLocal(const QString &path)
{
    const int index = cpoyFileToLocalIndex();

    const QString &des = QString("%1theme-%2%3").arg(USER_THEME_DIR_FULL).arg(index + 1).arg(TKM_FILE);
    DownloadBackgroundImage image;
    image.m_pix = QPixmap(path);
    return DownloadExtractManager::inputSkin(&image, des) ? index : -1;
}
