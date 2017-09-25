#include "downloadhistoryrecordwidget.h"
#include "downloaduiobject.h"
#include "downloadnumberutils.h"
#include "downloadsettingmanager.h"

#include <QFileIconProvider>

DownloadHistoryRecordWidget::DownloadHistoryRecordWidget(QWidget *parent)
    : DownloadAbstractTableWidget(parent)
{
    setColumnCount(4);

    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 40);
    headerview->resizeSection(1, 505);
    headerview->resizeSection(2, 200);
    headerview->resizeSection(3, 50);
}

DownloadHistoryRecordWidget::~DownloadHistoryRecordWidget()
{
    clearAllItems();

    DownloadRecordConfigManager xml;
    xml.writeDownloadConfig(m_records);
}

QString DownloadHistoryRecordWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadHistoryRecordWidget::init()
{
    DownloadRecordConfigManager xml;
    if(!xml.readDownloadXMLConfig())
    {
        return;
    }

    xml.readDownloadConfig(m_records);

    setRowCount(m_loadRecordCount = m_records.count()); //reset row count

    for(int i=0; i<m_records.count(); i++)
    {
        createItem(i, m_records[i]);
    }
}

void DownloadHistoryRecordWidget::clearAllItems()
{
    //Remove all the original item
    DownloadAbstractTableWidget::clear();
    setColumnCount(4);
}

void DownloadHistoryRecordWidget::resizeWindow()
{
    int width = M_SETTING_PTR->value(DownloadSettingManager::WidgetSize).toSize().width();
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(1, 505 + width - WINDOW_WIDTH_MIN);
}

void DownloadHistoryRecordWidget::setDeleteItemAt()
{

}

void DownloadHistoryRecordWidget::listCellClicked(int row, int column)
{

}

void DownloadHistoryRecordWidget::createDownloadItem(const QString &path)
{
    int row = rowCount();
    setRowCount(row + 1);

    QFileInfo info(path);
    DownloadRecord record;
    record.m_time = info.lastModified().toString("yyyy-MM-dd HH:mm:ss");
    record.m_path = info.absoluteFilePath();
    record.m_size = DownloadUtils::Number::size2Label(info.size());
    m_records << record;

    createItem(row, record);
}

void DownloadHistoryRecordWidget::contextMenuEvent(QContextMenuEvent *event)
{

}

void DownloadHistoryRecordWidget::createItem(int index, const DownloadRecord &record)
{
    setRowHeight(index, 50);
    QFileInfo info(record.m_path);

    QTableWidgetItem *item = new QTableWidgetItem;
    QFileIconProvider provider;
    QPixmap pix(provider.icon(QFileInfo(info.fileName())).pixmap(40, 40));
    if(pix.isNull())
    {
        pix.load(":/image/lb_blankImage");
    }
    item->setIcon(QIcon(pix.scaled(40, 40)));
    item->setSizeHint(pix.size());
    setItem(index, 0, item);

                      item = new QTableWidgetItem;
    item->setText(info.fileName());
    item->setTextColor(QColor(DownloadUIObject::MColorStyle12_S));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    item->setToolTip(info.fileName());
    setItem(index, 1, item);

                      item = new QTableWidgetItem;
    item->setText(record.m_time);
    item->setTextColor(QColor(DownloadUIObject::MColorStyle12_S));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    item->setToolTip(record.m_time);
    setItem(index, 2, item);

                      item = new QTableWidgetItem;
    item->setText(record.m_size);
    item->setTextColor(QColor(DownloadUIObject::MColorStyle12_S));
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    item->setToolTip(record.m_size);
    setItem(index, 3, item);
}
