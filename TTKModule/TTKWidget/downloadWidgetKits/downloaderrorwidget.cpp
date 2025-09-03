#include "downloaderrorwidget.h"

DownloadErrorWidget::DownloadErrorWidget(QWidget *parent)
    : DownloadBaseWidget(parent)
{
    m_path = ERROR_PATH_FULL;
}

void DownloadErrorWidget::contextMenuEvent(QContextMenuEvent *event)
{
    DownloadBaseWidget::contextMenuEvent(event);

    QMenu menu(this);
    menu.setStyleSheet(TTK::UI::MenuStyle02);

    createMenu(&menu);
}
