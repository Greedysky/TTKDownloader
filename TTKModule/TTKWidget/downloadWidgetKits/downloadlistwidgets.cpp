#include "downloadlistwidgets.h"
#include "downloadunits.h"
#include "downloadlistitemwidget.h"
#include "downloadobject.h"
#include "downloaduiobject.h"
#include "downloadsettingmanager.h"
#include "downloadabstracttablewidget.h"
#include "downloadwidgetutils.h"

#include <QHeaderView>

DownloadListWidgets::DownloadListWidgets(QWidget *parent)
    : DownloadAbstractTableWidget(parent)
{
    setColumnCount(1);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    DownloadUtils::Widget::setTransparent(this, 0);
    m_maxDownloadCount = 0;
}

DownloadListWidgets::~DownloadListWidgets()
{
    clearItems();
}

QString DownloadListWidgets::getClassName()
{
    return staticMetaObject.className();
}

void DownloadListWidgets::resizeWindow()
{
    int w = M_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize().width();
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 795 + w - WINDOW_WIDTH_MIN);
}

void DownloadListWidgets::pause()
{
    foreach(QTableWidgetItem *item, selectedItems())
    {
        int row = item->row();
        if(m_itemList.isEmpty() || row < 0)
        {
            continue;
        }

        --m_maxDownloadCount;
        m_maxDownloadCount = qMax(m_maxDownloadCount, 0);
        m_itemList[row]->pause();
        stateChanged(row);
    }

    getTopUrlToDownload();
}

void DownloadListWidgets::start()
{
    foreach(QTableWidgetItem *item, selectedItems())
    {
        int row = item->row();
        if(m_itemList.isEmpty() || row < 0)
        {
            return;
        }

        start(row);
    }
}

void DownloadListWidgets::addItemToList(const QString &path)
{
    if(path.isEmpty())
    {
        return;
    }

    int row = rowCount();
    setRowCount(row + 1);
    DownloadUnits *unit = new DownloadUnits(path, this);
    connect(unit, SIGNAL(removeItemWidget(DownloadUnits*)), SLOT(removeItemWidget(DownloadUnits*)));
    m_itemList << unit;

    DownloadListItemWidget *widget = unit->getDownloadItemWidget();
    QTableWidgetItem *item = new QTableWidgetItem;
    setItem(row, 0, item);
    setRowHeight(row, widget->height());
    setCellWidget(row, 0, widget);

    start(row);
}

void DownloadListWidgets::addItemToList(const QStringList &path)
{
    foreach(const QString &pa, path)
    {
        QString url = pa.trimmed();
        if( !url.isEmpty() && !findUrl(url) )
        {
            addItemToList(url);
        }
    }
}

void DownloadListWidgets::deleteItemFromList()
{
    foreach(QTableWidgetItem *item, selectedItems())
    {
        int row = item->row();
        if(m_itemList.isEmpty() || row < 0)
        {
            continue;
        }

        int state = m_itemList[row]->getState();
        if(state == 0 || state == 1)
        {
            --m_maxDownloadCount;
        }

        removeCellWidget(row, 0);
        removeRow(row);
        delete m_itemList.takeAt(row);

    }

    getTopUrlToDownload();
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

    --m_maxDownloadCount;
    removeCellWidget(row, 0);
    delete m_itemList.takeAt(row);
    removeRow(row);

    getTopUrlToDownload();
}

void DownloadListWidgets::listCellClicked(int row, int column)
{
    Q_UNUSED(column);
    if(row < 0)
    {
        return;
    }

    stateChanged(row);
}

void DownloadListWidgets::clearItems()
{
    while(!m_itemList.isEmpty())
    {
        delete m_itemList.takeLast();
    }
    clear();
}

void DownloadListWidgets::stateChanged(int row)
{
    int state = m_itemList[row]->getState();
    emit downloadStateChanged(state != 1 && state != 0);
}

void DownloadListWidgets::start(int row)
{
    if(row < 0)
    {
        return;
    }

    DownloadUnits *units = m_itemList[row];
    if(m_maxDownloadCount < 3)
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

void DownloadListWidgets::getTopUrlToDownload()
{
    int index = -1;
    if( !m_itemList.isEmpty() && m_maxDownloadCount < 3 )
    {
        foreach(DownloadUnits *item, m_itemList)
        {
            ++index;
            if(item->getState() == 3)
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
    foreach(DownloadUnits *item, m_itemList)
    {
        if(item->getUrl() == path)
        {
            state = true;
            break;
        }
    }

    return state;
}
