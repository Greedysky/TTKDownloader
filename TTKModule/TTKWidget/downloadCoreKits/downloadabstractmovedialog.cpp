#include "downloadabstractmovedialog.h"
#include "downloadbackgroundmanager.h"

DownloadAbstractMoveDialog::DownloadAbstractMoveDialog(QWidget *parent)
    : DownloadAbstractMoveDialog(true, parent)
{

}

DownloadAbstractMoveDialog::DownloadAbstractMoveDialog(bool transparent, QWidget *parent)
    : TTKAbstractMoveDialog(transparent, parent),
      DownloadWidgetRenderer()
{
    G_BACKGROUND_PTR->addObserver(this);
}

DownloadAbstractMoveDialog::~DownloadAbstractMoveDialog()
{
    G_BACKGROUND_PTR->removeObserver(this);
}

void DownloadAbstractMoveDialog::backgroundChanged()
{
    setBackgroundPixmap(size());
}

int DownloadAbstractMoveDialog::exec()
{
    setBackgroundPixmap(size());
    return QDialog::exec();
}

void DownloadAbstractMoveDialog::show()
{
    setBackgroundPixmap(size());
    QDialog::show();
}
