#include "downloadabstractmovewidget.h"
#include "downloadbackgroundmanager.h"

DownloadAbstractMoveWidget::DownloadAbstractMoveWidget(QWidget *parent)
    : DownloadAbstractMoveWidget(true, parent)
{

}

DownloadAbstractMoveWidget::DownloadAbstractMoveWidget(bool transparent, QWidget *parent)
    : TTKAbstractMoveWidget(transparent, parent),
      DownloadWidgetRenderer()
{
    G_BACKGROUND_PTR->addObserver(this);
}

DownloadAbstractMoveWidget::~DownloadAbstractMoveWidget()
{
    G_BACKGROUND_PTR->removeObserver(this);
}

void DownloadAbstractMoveWidget::backgroundChanged()
{
    setBackgroundPixmap(size());
}

void DownloadAbstractMoveWidget::show()
{
    setBackgroundPixmap(size());
    QWidget::show();
}
