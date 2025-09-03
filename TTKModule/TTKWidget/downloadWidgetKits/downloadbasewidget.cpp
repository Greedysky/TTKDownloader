#include "downloadbasewidget.h"
#include "downloaduiobject.h"
#include "downloadnumberutils.h"
#include "downloadsettingmanager.h"
#include "downloadmessagebox.h"
#include "downloadurlutils.h"

#include <QClipboard>
#include <QApplication>
#include <QFileIconProvider>

DownloadBaseWidget::DownloadBaseWidget(QWidget *parent)
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

DownloadBaseWidget::~DownloadBaseWidget()
{
    DownloadRecordConfigManager manager;
    if(!manager.load(m_path))
    {
        return;
    }

    manager.writeBuffer(m_records);
}

void DownloadBaseWidget::initialize()
{
    DownloadRecordConfigManager manager;
    if(!manager.fromFile(m_path))
    {
        return;
    }

    manager.readBuffer(m_records);

    setRowCount(m_records.count()); //reset row count

    for(int i = 0; i < m_records.count(); ++i)
    {
        addCellItem(i, m_records[i]);
    }
}

void DownloadBaseWidget::resizeWindow()
{
    int w = G_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize().width();
        w += G_SETTING_PTR->value(DownloadSettingManager::ExpandMode).toInt();
    QHeaderView *headerView = horizontalHeader();
    headerView->resizeSection(1, 495 + w - WINDOW_WIDTH_MIN);
}

void DownloadBaseWidget::removeItems()
{
    DownloadAbstractTableWidget::removeItems();
    setColumnCount(4);
}

void DownloadBaseWidget::unselectAll()
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

void DownloadBaseWidget::createResultItem(const QString &path, const QString &url)
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

void DownloadBaseWidget::deleteItemFromList()
{
    deleteItemFromList(false);
}

void DownloadBaseWidget::deleteItemFromList(bool file)
{
    for(const int row : selectedRows())
    {
        if(m_records.isEmpty() || row < 0)
        {
            continue;
        }

        removeCellWidget(row, 0);
        removeRow(row);

        const DownloadRecord &r = m_records.takeAt(row);
        if(file)
        {
            QFile::remove(r.m_path);
            QFile::remove(r.m_path + STK_FILE);
        }
        else
        {
            Q_EMIT deleteFinished(r.m_path, r.m_url);
        }
    }
}

void DownloadBaseWidget::deleteItemFromListWithFile()
{
    DownloadMessageBox message;
    message.setText(tr("Are you sure to delete?"));
    if(!message.exec())
    {
        return;
    }

    deleteItemFromList(true);
}

void DownloadBaseWidget::openFileDir()
{
    if(!isValid())
    {
        return;
    }

    if(!TTK::Url::openUrl(m_records[currentRow()].m_path, true))
    {
        DownloadMessageBox message;
        message.setText(tr("The origin one does not exist"));
        message.exec();
    }
}

void DownloadBaseWidget::copyUrlClicked()
{
    if(!isValid())
    {
        return;
    }

    QClipboard *clipBoard = QApplication::clipboard();
    clipBoard->setText(m_records[currentRow()].m_path);
}

void DownloadBaseWidget::createMenu(QMenu *menu)
{
    const bool enabled = selectedRows().count() > 0;
    menu->addAction(QIcon(":/tiny/btn_close_hover"), tr("Delete"), this, SLOT(deleteItemFromList()))->setEnabled(enabled);
    menu->addAction(QIcon(":/tiny/btn_close_normal"), tr("Delete With File"), this, SLOT(deleteItemFromListWithFile()))->setEnabled(enabled);
    menu->addAction(tr("Restart"))->setEnabled(enabled);
    menu->addSeparator();
    menu->addAction(tr("Selected All"), this, SLOT(selectAll()));
    menu->addAction(tr("Copy Url"), this, SLOT(copyUrlClicked()))->setEnabled(enabled);
    menu->exec(QCursor::pos());
}

void DownloadBaseWidget::addCellItem(int index, const DownloadRecord &record)
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
