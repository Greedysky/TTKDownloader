#include "downloadlistwidgets.h"
#include "downloadunits.h"
#include "downloadlistitemwidget.h"
#include "downloadobject.h"
#include "downloaduiobject.h"
#include "downloadsettingmanager.h"
#include "downloadabstracttablewidget.h"
#include "downloadlistconfigmanager.h"
#include "downloadurlutils.h"
#include "downloadmessagebox.h"
#include "downloadtopareawidget.h"

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
    for(DownloadUnits *item : qAsConst(m_itemList))
    {
        DownloadItem it;
        it.m_url = item->url();
        it.m_name = QFileInfo(item->downloadedPath()).fileName();
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

    for(const DownloadItem &it : qAsConst(list))
    {
        QString url = it.m_url.trimmed();
        if(!url.isEmpty() && !findUrl(url))
        {
            addItemToList(url, it.m_name);
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
    for(QTableWidgetItem *item : selectedItems())
    {
        int row = item->row();
        if(m_itemList.isEmpty() || row < 0)
        {
            continue;
        }

        pause(row);
    }

    topUrlToDownload();
}

void DownloadListWidgets::start()
{
    for(QTableWidgetItem *item : selectedItems())
    {
        int row = item->row();
        if(m_itemList.isEmpty() || row < 0)
        {
            return;
        }

        start(row);
    }
}

void DownloadListWidgets::addItemToList(const QString &path, const QString &name)
{
    if(path.isEmpty())
    {
        return;
    }

    const int row = rowCount();
    setRowCount(row + 1);

    DownloadUnits *unit = new DownloadUnits(path, this);
    connect(unit, SIGNAL(removeItemWidget(DownloadUnits*)), SLOT(removeItemWidget(DownloadUnits*)));
    m_itemList << unit;

    DownloadListItemWidget *widget = unit->downloadItemWidget();
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(row, 0, item);
    setRowHeight(row, widget->height());
    setCellWidget(row, 0, widget);

    start(row, name);
}

void DownloadListWidgets::addItemToList(const QStringList &path)
{
    for(const QString &pa : qAsConst(path))
    {
        QString url = pa.trimmed();
        if(!url.isEmpty() && !findUrl(url))
        {
            addItemToList(url, {});
        }
    }
}

void DownloadListWidgets::deleteItemFromList()
{
    deleteItemFromList(false);
}

void DownloadListWidgets::deleteItemFromList(bool file)
{
    for(QTableWidgetItem *item : selectedItems())
    {
        int row = item->row();
        if(m_itemList.isEmpty() || row < 0)
        {
            continue;
        }

        int state = m_itemList[row]->state();
        QString path = m_itemList[row]->downloadedPath();
        if(state == 0 || state == 1)
        {
            --m_maxDownloadCount;
        }

        removeCellWidget(row, 0);
        removeRow(row);
        delete m_itemList.takeAt(row);

        if(file)
        {
            QFile::remove(path);
            QFile::remove(path + SET_FILE);
        }
    }

    topUrlToDownload();
}

void DownloadListWidgets::deleteItemFromListWithFile()
{
    deleteItemFromList(true);
}

void DownloadListWidgets::removeItemWidget(DownloadUnits *unit)
{
    if(m_itemList.isEmpty())
    {
        return;
    }

    int row = m_itemList.indexOf(unit);
    if(row == -1)
    {
        return;
    }

    Q_EMIT downloadingFinished(unit->downloadedPath(), unit->url());

    --m_maxDownloadCount;
    removeCellWidget(row, 0);
    delete m_itemList.takeAt(row);
    removeRow(row);

    topUrlToDownload();
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
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    QString path = m_itemList[currentRow()]->downloadedPath();

    if(!TTK::Url::openUrl(QFileInfo(path).absoluteFilePath(), true))
    {
        DownloadMessageBox message;
        message.setText(tr("The origin one does not exist"));
        message.exec();
    }
}

void DownloadListWidgets::startClicked()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    start(currentRow());
}

void DownloadListWidgets::pauseClicked()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    pause(currentRow());
    topUrlToDownload();
}

void DownloadListWidgets::copyUrlClicked()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    QClipboard *clipBoard = QApplication::clipboard();
    clipBoard->setText(m_itemList[currentRow()]->url());
}

void DownloadListWidgets::updateTotalSpeedLabel()
{
    float total = 0;
    for(DownloadUnits *item : qAsConst(m_itemList))
    {
        total += item->downloadItemWidget()->percent();
    }
    DownloadTopAreaWidget::instance()->updateRemoteSpeedText(m_itemList.isEmpty() ? 0 : ceil(total / m_itemList.count()));
}

void DownloadListWidgets::contextMenuEvent(QContextMenuEvent *event)
{
    DownloadAbstractTableWidget::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(TTK::UI::MenuStyle02);

    int row = currentRow();
    menu.addAction(tr("Open File"), this, SLOT(openFileDir()))->setEnabled(row > -1);
    menu.addSeparator();

    bool downloadState = false;
    if(row > -1 && row < m_itemList.count())
    {
        int s = m_itemList[row]->state();
        downloadState = (s == 0 || s == 1);
    }
    if(downloadState)
    {
        menu.addAction(QIcon(":/contextMenu/lb_stop_normal"), tr("Pause"), this, SLOT(pauseClicked()));
    }
    else
    {
        menu.addAction(QIcon(":/contextMenu/lb_start_normal"), tr("NewDownload"), this, SLOT(startClicked()))->setEnabled(row > -1);
    }

    menu.addAction(QIcon(":/tiny/btn_close_hover"), tr("Delete"), this, SLOT(deleteItemFromList()))->setEnabled(row > -1);
    menu.addAction(QIcon(":/tiny/btn_close_normal"), tr("Delete With File"), this, SLOT(deleteItemFromListWithFile()))->setEnabled(row > -1);
    menu.addAction(tr("Sort"));
    menu.addAction(tr("Selected All"), this, SLOT(selectAll()));
    menu.addSeparator();
    menu.addAction(tr("Copy Url"), this, SLOT(copyUrlClicked()))->setEnabled(row > -1);

    menu.exec(QCursor::pos());
}

void DownloadListWidgets::clearItems()
{
    qDeleteAll(m_itemList);
    m_itemList.clear();
    removeItems();
}

void DownloadListWidgets::stateChanged(int row)
{
    int state = m_itemList[row]->state();
    Q_EMIT downloadStateChanged(state != 1 && state != 0);
}

void DownloadListWidgets::start(int row, const QString &name)
{
    if(row < 0)
    {
        return;
    }

    DownloadUnits *units = m_itemList[row];
    if(m_maxDownloadCount < 3)
    {
        ++m_maxDownloadCount;
        units->start(name);
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
    m_itemList[row]->pause();
    stateChanged(row);
}

void DownloadListWidgets::topUrlToDownload()
{
    int index = -1;
    if(!m_itemList.isEmpty() && m_maxDownloadCount < 3)
    {
        for(DownloadUnits *item : qAsConst(m_itemList))
        {
            ++index;
            if(item->state() == 3)
            {
                start(index);
                break;
            }
        }
    }
}

bool DownloadListWidgets::findUrl(const QString &path) const
{
    bool state = false;
    for(DownloadUnits *item : qAsConst(m_itemList))
    {
        if(item->url() == path)
        {
            state = true;
            break;
        }
    }

    return state;
}
