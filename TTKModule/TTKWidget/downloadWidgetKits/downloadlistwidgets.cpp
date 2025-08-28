#include "downloadlistwidgets.h"
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

#include <qmath.h>

#include <QMenu>
#include <QClipboard>
#include <QHeaderView>
#include <QApplication>

DownloadListWidgets::DownloadListWidgets(QWidget *parent)
    : DownloadAbstractTableWidget(parent),
      m_maxDownloadCount(0)
{
    setColumnCount(1);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    m_speedTimer.setInterval(TTK_DN_S2MS / 4);
    connect(&m_speedTimer, SIGNAL(timeout()), SLOT(updateTotalSpeedLabel()));
    m_speedTimer.start();
}

DownloadListWidgets::~DownloadListWidgets()
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

void DownloadListWidgets::initialize()
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

void DownloadListWidgets::resizeWindow()
{
    int w = G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize().width();
    w += G_SETTING_PTR->value(DownloadSettingManager::ExpandMode).toInt();
    QHeaderView *headerView = horizontalHeader();
    headerView->resizeSection(0, 787 + w - WINDOW_WIDTH_MIN);
}

void DownloadListWidgets::reverseSelect()
{
    TTKIntSet rows;
    for(QTableWidgetItem *item : selectedItems())
    {
        rows.insert(item->row());
    }

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

void DownloadListWidgets::pause()
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(QTableWidgetItem *item : selectedItems())
    {
        pause(item->row());
    }

    nextUrlToDownload();
}

void DownloadListWidgets::start()
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(QTableWidgetItem *item : selectedItems())
    {
        start(item->row());
    }
}

void DownloadListWidgets::addItemToList(const QStringList &urls)
{
    for(const QString &url : qAsConst(urls))
    {
        const QString &v = url.trimmed();
        if(!findUrl(v))
        {
            addItemToStartList(v);
        }
    }
}

void DownloadListWidgets::deleteItemFromList()
{
    deleteItemFromList(false);
}

void DownloadListWidgets::deleteItemFromList(bool file)
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(QTableWidgetItem *item : selectedItems())
    {
        const int row = item->row();
        if(row < 0)
        {
            continue;
        }

        const TTK::DownloadState state = m_items[row]->state();
        const QString &path = m_items[row]->path();
        if(state == TTK::DownloadState::Waiting || state == TTK::DownloadState::Download)
        {
            --m_maxDownloadCount;
        }

        removeCellWidget(row, 0);
        removeRow(row);
        delete m_items.takeAt(row);

        if(file)
        {
            QFile::remove(path);
            QFile::remove(path + STK_FILE);
        }
    }

    nextUrlToDownload();
}

void DownloadListWidgets::deleteItemFromListWithFile()
{
    deleteItemFromList(true);
}

void DownloadListWidgets::removeItemWidget(DownloadUnits *unit)
{
    if(m_items.isEmpty())
    {
        return;
    }

    const int row = m_items.indexOf(unit);
    if(row < 0)
    {
        return;
    }

    Q_EMIT downloadingFinished(unit->path(), unit->url());

    --m_maxDownloadCount;
    removeCellWidget(row, 0);
    delete m_items.takeAt(row);
    removeRow(row);

    nextUrlToDownload();
}

void DownloadListWidgets::itemCellClicked(int row, int column)
{
    Q_UNUSED(column);
    if(row < 0)
    {
        return;
    }

    stateChanged(row);
}

void DownloadListWidgets::openFileDir()
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

void DownloadListWidgets::startClicked()
{
    if(!isValid())
    {
        return;
    }

    start(currentRow());
}

void DownloadListWidgets::pauseClicked()
{
    if(!isValid())
    {
        return;
    }

    pause(currentRow());
    nextUrlToDownload();
}

void DownloadListWidgets::copyUrlClicked()
{
    if(!isValid())
    {
        return;
    }

    QClipboard *clipBoard = QApplication::clipboard();
    clipBoard->setText(m_items[currentRow()]->url());
}

void DownloadListWidgets::updateTotalSpeedLabel()
{
    float total = 0;
    for(DownloadUnits *item : qAsConst(m_items))
    {
        total += item->downloadItemWidget()->percent();
    }
    DownloadTopAreaWidget::instance()->updateRemoteSpeedText(m_items.isEmpty() ? 0 : ceil(total / m_items.count()));
}

void DownloadListWidgets::contextMenuEvent(QContextMenuEvent *event)
{
    DownloadAbstractTableWidget::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(TTK::UI::MenuStyle02);

    const int row = currentRow();
    const bool enabled = row > -1;

    menu.addAction(tr("Open File"), this, SLOT(openFileDir()))->setEnabled(enabled);
    menu.addSeparator();

    bool downloadState = false;
    if(enabled && row < m_items.count())
    {
        TTK::DownloadState s = m_items[row]->state();
        downloadState = (s == TTK::DownloadState::Waiting || s == TTK::DownloadState::Download);
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
    menu.addAction(tr("Sort"));
    menu.addAction(tr("Selected All"), this, SLOT(selectAll()));
    menu.addSeparator();
    menu.addAction(tr("Copy Url"), this, SLOT(copyUrlClicked()))->setEnabled(enabled);
    menu.exec(QCursor::pos());
}

void DownloadListWidgets::addItemToCacheList(const QString &url, const QString &name)
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

    DownloadListItemWidget *widget = unit->downloadItemWidget();
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
        DownloadBreakPointItem item = records.front();
        widget->updateFileInfoChanged(name, item.m_end);
        widget->progressChanged(item.m_ready, item.m_end);
        widget->stateChanged(tr("Pause"));
    }
}

void DownloadListWidgets::addItemToStartList(const QString &url)
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

    DownloadListItemWidget *widget = unit->downloadItemWidget();
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(row, 0, item);
    setRowHeight(row, widget->height());
    setCellWidget(row, 0, widget);

    start(row);
}

void DownloadListWidgets::clearItems()
{
    qDeleteAll(m_items);
    m_items.clear();
    removeItems();
}

void DownloadListWidgets::stateChanged(int row)
{
    const TTK::DownloadState state = m_items[row]->state();
    Q_EMIT downloadStateChanged(state != TTK::DownloadState::Waiting && state != TTK::DownloadState::Download);
}

void DownloadListWidgets::start(int row)
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
        stateChanged(row);
    }
    else
    {
        units->setStateChanged(tr("D_Queue"));
    }
}

void DownloadListWidgets::pause(int row)
{
    if(row < 0)
    {
        return;
    }

    --m_maxDownloadCount;
    m_maxDownloadCount = qMax(m_maxDownloadCount, 0);
    m_items[row]->pause();
    stateChanged(row);
}

void DownloadListWidgets::nextUrlToDownload()
{
    if(m_items.isEmpty())
    {
        return;
    }

    for(int i = 0; i < m_items.count(); ++i)
    {
        if(m_items[i]->state() == TTK::DownloadState::Stop)
        {
            start(i);
        }
    }
}

bool DownloadListWidgets::findUrl(const QString &url) const
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
