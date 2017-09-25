#include "downloadsettingwidget.h"
#include "ui_downloadsettingwidget.h"
#include "downloadsettingmanager.h"

#include <QFileDialog>

DownloadFunctionTableWidget::DownloadFunctionTableWidget(QWidget *parent)
    : DownloadAbstractTableWidget(parent)
{
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 20);
    headerview->resizeSection(1, 20);
    headerview->resizeSection(2, 85);

    setRowCount(3);
    m_listIndex = 0;
}

QString DownloadFunctionTableWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadFunctionTableWidget::addFunctionItems(int index, const DownloadFunctionItems &items)
{
    m_listIndex = index;
    for(int i=0; i<items.count(); ++i)
    {
        const DownloadFunctionItem &&fItem = std::move(items[i]);
        QTableWidgetItem *item = nullptr;
        setItem(i, 0, item = new QTableWidgetItem());

                      item = new QTableWidgetItem(QIcon(fItem.m_icon), QString());
        item->setTextAlignment(Qt::AlignCenter);
        setItem(i, 1, item);

                      item = new QTableWidgetItem(fItem.m_name);
        item->setTextColor(QColor(80, 80, 80));
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        setItem(i, 2, item);
    }
}

void DownloadFunctionTableWidget::listCellClicked(int row, int column)
{
    Q_UNUSED(column);
    emit currentIndexChanged(row + m_listIndex);
    selectRow( currentRow() );
}

void DownloadFunctionTableWidget::leaveEvent(QEvent *event)
{
    QTableWidget::leaveEvent(event);
    listCellEntered(-1, -1);
}


DownloadSettingWidget::DownloadSettingWidget(QWidget *parent)
    : DownloadAbstractMoveDialog(parent),
      m_ui(new Ui::DownloadSettingWidget)
{
    m_ui->setupUi(this);

    ////////////////////////////////////////////////
    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_delete_normal"));
    m_ui->topTitleCloseButton->setStyleSheet(DownloadUIObject::MToolButtonStyle04);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    ////////////////////////////////////////////////
    DownloadFunctionItems items;
    items << DownloadFunctionItem(QString(), tr("Normal"))
          << DownloadFunctionItem(QString(), tr("Dwonload"))
          << DownloadFunctionItem(QString(), tr("Outlook"));
    m_ui->normalFunTableWidget->setRowCount(items.count());
    m_ui->normalFunTableWidget->addFunctionItems(0, items);

    m_ui->confirmButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->cancelButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->confirmButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->cancelButton->setCursor(QCursor(Qt::PointingHandCursor));
#ifdef Q_OS_UNIX
    m_ui->confirmButton->setFocusPolicy(Qt::NoFocus);
    m_ui->cancelButton->setFocusPolicy(Qt::NoFocus);
#endif
    connect(m_ui->normalFunTableWidget, SIGNAL(currentIndexChanged(int)), m_ui->stackedWidget, SLOT(setCurrentIndex(int)));
    connect(m_ui->normalFunTableWidget, SIGNAL(currentIndexChanged(int)), SLOT(clearFunctionTableSelection()));
    connect(m_ui->confirmButton, SIGNAL(clicked()), SLOT(commitTheResults()));
    connect(m_ui->cancelButton, SIGNAL(clicked()), SLOT(close()));

    ////////////////////////////////////////////////
    initNormalSettingWidget();
    ////////////////////////////////////////////////
    selectFunctionTableIndex(0, 0);

}

DownloadSettingWidget::~DownloadSettingWidget()
{
    delete m_ui;
}

QString DownloadSettingWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadSettingWidget::initControllerParameter()
{
    m_ui->downloadDirEdit->setText(M_SETTING_PTR->value(DownloadSettingManager::DownloadPathDirChoiced).toString());
}

void DownloadSettingWidget::clearFunctionTableSelection()
{
    m_ui->normalFunTableWidget->clearSelection();
}

void DownloadSettingWidget::downloadDirSelected()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setViewMode(QFileDialog::Detail);
    if(dialog.exec())
    {
        QString path = dialog.directory().absolutePath();
        if(!path.isEmpty())
        {
            m_ui->downloadDirEdit->setText(path + "/");
        }
    }
}

void DownloadSettingWidget::commitTheResults()
{
    M_SETTING_PTR->setValue(DownloadSettingManager::DownloadPathDirChoiced, m_ui->downloadDirEdit->text());

    emit parameterSettingChanged();
    close();
}

int DownloadSettingWidget::exec()
{
    setBackgroundPixmap(m_ui->background, size());
    return DownloadAbstractMoveDialog::exec();
}

void DownloadSettingWidget::selectFunctionTableIndex(int row, int col)
{
    clearFunctionTableSelection();
    switch(row)
    {
        case 0:
            m_ui->normalFunTableWidget->selectRow(col); break;
        default: break;
    }
}

void DownloadSettingWidget::initNormalSettingWidget()
{
    m_ui->downloadDirEdit->setStyleSheet(DownloadUIObject::MLineEditStyle01);
    m_ui->downloadDirButton->setStyleSheet(DownloadUIObject::MPushButtonStyle04);
    m_ui->downloadDirButton->setCursor(QCursor(Qt::PointingHandCursor));
#ifdef Q_OS_UNIX
    m_ui->downloadDirButton->setFocusPolicy(Qt::NoFocus);
#endif

    m_ui->downloadDirEdit->setText(TDDOWNLOAD_DIR_FULL);

    connect(m_ui->downloadDirButton, SIGNAL(clicked()), SLOT(downloadDirSelected()));
}
