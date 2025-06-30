#include "downloadhistoryrecordwidget.h"
#include "downloaduiobject.h"
#include "downloadnumberutils.h"
#include "downloadsettingmanager.h"
#include "downloadmessagebox.h"
#include "downloadurlutils.h"

#include <QMenu>
#include <QClipboard>
#include <QApplication>
#include <QFileIconProvider>

DownloadHistoryRecordWidget::DownloadHistoryRecordWidget(QWidget *parent)
    : DownloadAbstractTableWidget(parent)
{
    setColumnCount(4);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    QHeaderView *headerView = horizontalHeader();
    headerView->resizeSection(0, 50);
    headerView->resizeSection(1, 495);
    headerView->resizeSection(2, 192);
    headerView->resizeSection(3, 50);
}

DownloadHistoryRecordWidget::~DownloadHistoryRecordWidget()
{
    clearAllItems();

    DownloadRecordConfigManager manager;
    if(!manager.load(HISTORY_PATH_FULL))
    {
        return;
    }

    manager.writeBuffer(m_records);
}

void DownloadHistoryRecordWidget::initialize()
{
    DownloadRecordConfigManager manager;
    if(!manager.fromFile(HISTORY_PATH_FULL))
    {
        return;
    }

    manager.readBuffer(m_records);

    setRowCount(m_loadRecordCount = m_records.count()); //reset row count

    for(int i = 0; i < m_records.count(); ++i)
    {
        addCellItem(i, m_records[i]);
    }
}

void DownloadHistoryRecordWidget::clearAllItems()
{
    //Remove all the original item
    DownloadAbstractTableWidget::removeItems();
    setColumnCount(4);
}

void DownloadHistoryRecordWidget::resizeWindow()
{
    int w = G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize().width();
    w += G_SETTING_PTR->value(DownloadSettingManager::ExpandMode).toInt();
    QHeaderView *headerView = horizontalHeader();
    headerView->resizeSection(1, 495 + w - WINDOW_WIDTH_MIN);
}

void DownloadHistoryRecordWidget::reverseSelect()
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

void DownloadHistoryRecordWidget::createDownloadItem(const QString &path, const QString &url)
{
    const int row = rowCount();
    setRowCount(row + 1);

    const QFileInfo fin(path);
    DownloadRecord record;
    record.m_time = fin.lastModified().toString(TTK_DATE_TIMES_FORMAT);
    record.m_path = fin.absoluteFilePath();
    record.m_size = TTK::Number::sizeByteToLabel(fin.size());
    record.m_url = url;
    m_records << record;

    addCellItem(row, record);
}

void DownloadHistoryRecordWidget::deleteItemFromList()
{
    deleteItemFromList(false);
}

void DownloadHistoryRecordWidget::deleteItemFromList(bool file)
{
    for(QTableWidgetItem *item : selectedItems())
    {
        int row = item->row();
        if(m_records.isEmpty() || row < 0)
        {
            continue;
        }

        removeCellWidget(row, 0);
        removeRow(row);
        DownloadRecord r = m_records.takeAt(row);

        if(file)
        {
            QFile::remove(r.m_path);
            QFile::remove(r.m_path + SET_FILE);
        }
    }
}

void DownloadHistoryRecordWidget::deleteItemFromListWithFile()
{
    deleteItemFromList(true);
}

void DownloadHistoryRecordWidget::openFileDir()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    QString path = m_records[ currentRow() ].m_path;
    if(!TTK::Url::openUrl(path, true))
    {
        DownloadMessageBox message;
        message.setText(tr("The origin one does not exist"));
        message.exec();
    }
}

void DownloadHistoryRecordWidget::copyUrlClicked()
{
    if(rowCount() == 0 || currentRow() < 0)
    {
        return;
    }

    QClipboard *clipBoard = QApplication::clipboard();
    clipBoard->setText(m_records[ currentRow() ].m_path);
}

void DownloadHistoryRecordWidget::contextMenuEvent(QContextMenuEvent *event)
{
    DownloadAbstractTableWidget::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(TTK::UI::MenuStyle02);

    int row = currentRow();
    menu.addAction(tr("Open File"), this, SLOT(openFileDir()))->setEnabled(row > -1);
    menu.addSeparator();

    menu.addAction(QIcon(":/tiny/btn_close_hover"), tr("Delete"), this, SLOT(deleteItemFromList()))->setEnabled(row > -1);
    menu.addAction(QIcon(":/tiny/btn_close_normal"), tr("Delete With File"), this, SLOT(deleteItemFromListWithFile()))->setEnabled(row > -1);
    menu.addAction(tr("Sort"));
    menu.addAction(tr("Selected All"), this, SLOT(selectAll()));
    menu.addSeparator();
    menu.addAction(tr("Copy Url"), this, SLOT(copyUrlClicked()))->setEnabled(row > -1);
    menu.exec(QCursor::pos());
}

void DownloadHistoryRecordWidget::addCellItem(int index, const DownloadRecord &record)
{
    setRowHeight(index, 50);
    const QFileInfo fin(record.m_path);

    QTableWidgetItem *item = new QTableWidgetItem;
    QFileIconProvider provider;
    QPixmap pix(provider.icon(QFileInfo(fin.fileName())).pixmap(40, 40));
    if(pix.isNull())
    {
        pix.load(":/image/lb_blankImage");
    }
    item->setIcon(QIcon(pix.scaled(40, 40)));
    setIconSize(pix.size());
    setItem(index, 0, item);

                      item = new QTableWidgetItem;
    item->setText(fin.fileName());
    item->setForeground(QColor(50, 50, 50));
    QtItemSetTextAlignment(item, Qt::AlignLeft | Qt::AlignVCenter);
    item->setToolTip(fin.fileName());
    setItem(index, 1, item);

                      item = new QTableWidgetItem;
    item->setText(record.m_time);
    item->setForeground(QColor(50, 50, 50));
    QtItemSetTextAlignment(item, Qt::AlignLeft | Qt::AlignVCenter);
    item->setToolTip(record.m_time);
    setItem(index, 2, item);

                      item = new QTableWidgetItem;
    item->setText(record.m_size);
    item->setForeground(QColor(50, 50, 50));
    QtItemSetTextAlignment(item, Qt::AlignLeft | Qt::AlignVCenter);
    item->setToolTip(record.m_size);
    setItem(index, 3, item);
}
