#include "downloadlistwidget.h"
#include "downloadunits.h"
#include "downloadlistitemwidget.h"
#include "downloaduiobject.h"
#include "downloadsettingmanager.h"
#include "downloadabstracttablewidget.h"
#include "downloadlistconfigmanager.h"
#include "downloadurlutils.h"
#include "downloadmessagebox.h"
#include "downloadtopareawidget.h"
#include "downloadstringutils.h"
#include "downloadbreakpointconfigmanager.h"
#include "downloadtoastlabel.h"

#include <cmath>
#include <QClipboard>
#include <QHeaderView>
#include <QApplication>

DownloadListWidget::DownloadListWidget(QWidget *parent)
    : DownloadAbstractTableWidget(parent),
      m_maxDownloadCount(0)
{
    setColumnCount(1);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    m_speedTimer.setInterval(TTK_DN_S2MS / 4);
    connect(&m_speedTimer, SIGNAL(timeout()), SLOT(updateTotalSpeedLabel()));
    m_speedTimer.start();
}

DownloadListWidget::~DownloadListWidget()
{
    m_speedTimer.stop();
    DownloadItemList list;
    for(DownloadUnits *item : qAsConst(m_items))
    {
        DownloadItem it;
        it.m_url = item->url();
        it.m_name = item->name();
        list << it;
    }

    DownloadListConfigManager manager;
    if(!manager.load(LIST_PATH_FULL))
    {
        return;
    }

    manager.writeBuffer(list);
    clearItems();
}

void DownloadListWidget::initialize()
{
    DownloadListConfigManager manager;
    if(!manager.fromFile(LIST_PATH_FULL))
    {
        return;
    }

    DownloadItemList list;
    manager.readBuffer(list);

    const bool startupMode = G_SETTING_PTR->value(DownloadSettingManager::StartUpRunMode).toBool();
    for(const DownloadItem &it : qAsConst(list))
    {
        if(findUrl(it.m_url))
        {
            continue;
        }

        if(startupMode)
        {
            addItemToStartList(it.m_url);
        }
        else
        {
            addItemToCacheList(it.m_url, it.m_name);
        }
    }
}

void DownloadListWidget::resizeWindow()
{
    int w = G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize().width();
        w += G_SETTING_PTR->value(DownloadSettingManager::ExpandMode).toInt();
    QHeaderView *headerView = horizontalHeader();
    headerView->resizeSection(0, 787 + w - WINDOW_WIDTH_MIN);
}

void DownloadListWidget::unselectAll()
{
    const TTKIntList &rows = selectedRows();
    setSelectionMode(QAbstractItemView::MultiSelection);

    clearSelection();
    for(int i = 0; i < rowCount(); ++i)
    {
        if(!rows.contains(i))
        {
            selectRow(i);
        }
    }

    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void DownloadListWidget::pause()
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(const int row : selectedRows())
    {
        pause(row);
    }

    nextUrlToDownload();
}

void DownloadListWidget::start()
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(const int row : selectedRows())
    {
        start(row);
    }
}

void DownloadListWidget::addItemToList(const QStringList &urls)
{
    for(const QString &url : qAsConst(urls))
    {
        const QString &v = url.trimmed();
        if(findUrl(v))
        {
            DownloadToastLabel::popup(tr("Download url is already exist"));
            continue;
        }

        addItemToStartList(v);
    }
}

void DownloadListWidget::deleteItemFromList()
{
    deleteItemFromList(false);
}

void DownloadListWidget::deleteItemFromList(bool file)
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(const int row : selectedRows())
    {
        if(row < 0)
        {
            continue;
        }

        DownloadUnits *unit = m_items[row];
        if(unit->isRunning())
        {
            --m_maxDownloadCount;
        }

        const QString &url = unit->url();
        const QString &name = unit->name();
        const QString &path = unit->path();

        removeCellWidget(row, 0);
        removeRow(row);
        delete m_items.takeAt(row);

        if(file)
        {
            QFile::remove(path);
            QFile::remove(path + STK_FILE);
        }
        else
        {
            Q_EMIT deleteFinished(TTK::String::downloadPrefix() + name, url);
        }
    }

    nextUrlToDownload();
}

void DownloadListWidget::deleteItemFromListWithFile()
{
    DownloadMessageBox message;
    message.setText(tr("Are you sure to delete?"));
    if(!message.exec())
    {
        return;
    }

    deleteItemFromList(true);
}

void DownloadListWidget::removeItemWidget(DownloadUnits *unit)
{
    if(!unit)
    {
        TTK_INFO_STREAM("Current file is error occurred, to do next");
        --m_maxDownloadCount;
        nextUrlToDownload();
        return;
    }

    if(m_items.isEmpty())
    {
        return;
    }

    const int row = m_items.indexOf(unit);
    if(row < 0)
    {
        return;
    }

    Q_EMIT downloadFinished(unit->path(), unit->url());

    --m_maxDownloadCount;
    removeCellWidget(row, 0);
    delete m_items.takeAt(row);
    removeRow(row);

    nextUrlToDownload();
}

void DownloadListWidget::itemCellClicked(int row, int column)
{
    Q_UNUSED(column);
    if(row < 0)
    {
        return;
    }

    setDownloadState(row);
}

void DownloadListWidget::openFileDir()
{
    if(!isValid())
    {
        return;
    }

    if(!TTK::Url::openUrl(m_items[currentRow()]->path(), true))
    {
        DownloadMessageBox message;
        message.setText(tr("The origin one does not exist"));
        message.exec();
    }
}

void DownloadListWidget::startClicked()
{
    if(!isValid())
    {
        return;
    }

    start(currentRow());
}

void DownloadListWidget::pauseClicked()
{
    if(!isValid())
    {
        return;
    }

    pause(currentRow());
    nextUrlToDownload();
}

void DownloadListWidget::copyUrlClicked()
{
    if(!isValid())
    {
        return;
    }

    QClipboard *clipBoard = QApplication::clipboard();
    clipBoard->setText(m_items[currentRow()]->url());
}

void DownloadListWidget::updateTotalSpeedLabel()
{
    float total = 0;
    for(DownloadUnits *item : qAsConst(m_items))
    {
        total += item->widget()->percent();
    }
    DownloadTopAreaWidget::instance()->updateRemoteSpeedText(m_items.isEmpty() ? 0 : std::ceil(total / m_items.count()));
}

void DownloadListWidget::itemLeftDoublePressed()
{
    if(!isValid())
    {
        return;
    }

    const int row = currentRow();
    if(m_items[row]->isRunning())
    {
        pause(row);
        nextUrlToDownload();
    }
    else
    {
        start(row);
    }
}

void DownloadListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    DownloadAbstractTableWidget::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(TTK::UI::MenuStyle02);

    const int row = currentRow();
    const bool enabled = row > -1;
    const bool single = selectedRows().count() == 1;

    menu.addAction(tr("Open File"), this, SLOT(openFileDir()))->setEnabled(enabled && single);
    menu.addSeparator();

    bool downloadState = false;
    if(enabled && row < m_items.count())
    {
        downloadState = m_items[row]->isRunning();
    }

    if(downloadState)
    {
        menu.addAction(QIcon(":/contextMenu/lb_stop_normal"), tr("Pause"), this, SLOT(pauseClicked()));
    }
    else
    {
        menu.addAction(QIcon(":/contextMenu/lb_start_normal"), tr("NewDownload"), this, SLOT(startClicked()))->setEnabled(enabled);
    }

    menu.addAction(QIcon(":/tiny/btn_close_hover"), tr("Delete"), this, SLOT(deleteItemFromList()))->setEnabled(enabled);
    menu.addAction(QIcon(":/tiny/btn_close_normal"), tr("Delete With File"), this, SLOT(deleteItemFromListWithFile()))->setEnabled(enabled);
    menu.addAction(tr("Restart"));
    menu.addSeparator();
    menu.addAction(tr("Sort"))->setEnabled(false);
    menu.addAction(tr("Selected All"), this, SLOT(selectAll()));
    menu.addAction(tr("Copy Url"), this, SLOT(copyUrlClicked()))->setEnabled(enabled && single);
    menu.exec(QCursor::pos());
}

void DownloadListWidget::addItemToCacheList(const QString &url, const QString &name)
{
    if(url.isEmpty())
    {
        return;
    }

    const int row = rowCount();
    setRowCount(row + 1);

    DownloadUnits *unit = new DownloadUnits(url, name, this);
    connect(unit, SIGNAL(removeItemWidget(DownloadUnits*)), SLOT(removeItemWidget(DownloadUnits*)));
    m_items << unit;

    DownloadListItemWidget *widget = unit->widget();
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(row, 0, item);
    setRowHeight(row, widget->height());
    setCellWidget(row, 0, widget);

    DownloadBreakPointConfigManager manager;
    DownloadBreakPointItemList records;
    if(manager.fromFile(TTK::String::downloadPrefix() + name + STK_FILE))
    {
        manager.readBuffer(records);
    }

    if(!records.isEmpty())
    {
        DownloadBreakPointItem item = records.first();
        widget->updateFileInfoChanged(name, item.m_end);
        widget->progressChanged(item.m_ready, item.m_end);
        widget->stateChanged(tr("StatePause"));
    }
}

void DownloadListWidget::addItemToStartList(const QString &url)
{
    if(url.isEmpty())
    {
        return;
    }

    const int row = rowCount();
    setRowCount(row + 1);

    DownloadUnits *unit = new DownloadUnits(url, this);
    connect(unit, SIGNAL(removeItemWidget(DownloadUnits*)), SLOT(removeItemWidget(DownloadUnits*)));
    m_items << unit;

    DownloadListItemWidget *widget = unit->widget();
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(row, 0, item);
    setRowHeight(row, widget->height());
    setCellWidget(row, 0, widget);

    start(row);
}

void DownloadListWidget::clearItems()
{
    qDeleteAll(m_items);
    m_items.clear();
    removeItems();
}

void DownloadListWidget::setDownloadState(int row)
{
    Q_EMIT downloadStateChanged(!m_items[row]->isRunning());
}

void DownloadListWidget::start(int row)
{
    if(row < 0)
    {
        return;
    }

    DownloadUnits *units = m_items[row];
    if(m_maxDownloadCount < G_SETTING_PTR->value(DownloadSettingManager::DownloadMaxCount).toInt() + 1)
    {
        ++m_maxDownloadCount;
        units->start();
        setDownloadState(row);
    }
    else
    {
        units->queue();
    }
}

void DownloadListWidget::pause(int row)
{
    if(row < 0)
    {
        return;
    }

    --m_maxDownloadCount;
    m_maxDownloadCount = qMax(m_maxDownloadCount, 0);
    m_items[row]->pause();
    setDownloadState(row);
}

void DownloadListWidget::nextUrlToDownload()
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(int i = 0; i < m_items.count(); ++i)
    {
        if(m_items[i]->state() == TTK::DownloadState::Queue)
        {
            start(i);
        }
    }
}

bool DownloadListWidget::findUrl(const QString &url) const
{
    bool state = false;
    for(DownloadUnits *item : qAsConst(m_items))
    {
        if(item->url() == url)
        {
            state = true;
            break;
        }
    }

    return state;
}
