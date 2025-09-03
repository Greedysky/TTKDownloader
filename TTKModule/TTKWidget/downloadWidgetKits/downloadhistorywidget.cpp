#include "downloadhistorywidget.h"

DownloadHistoryWidget::DownloadHistoryWidget(QWidget *parent)
    : DownloadBaseWidget(parent)
{
    m_path = HISTORY_PATH_FULL;
}

void DownloadHistoryWidget::contextMenuEvent(QContextMenuEvent *event)
{
    DownloadBaseWidget::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(TTK::UI::MenuStyle02);

    const bool enabled = selectedRows().count() > 0;
    menu.addAction(tr("Open File"), this, SLOT(openFileDir()))->setEnabled(enabled);
    menu.addSeparator();

    createMenu(&menu);
}
