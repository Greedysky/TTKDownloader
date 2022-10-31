#include "downloadfileutils.h"

#include <QFileDialog>

QString DownloadUtils::File::getOpenFileName(QWidget *parent)
{
    return QFileDialog::getOpenFileName(parent, QObject::tr("choose a filename to open under"), QDir::currentPath(), "Images (*.png *.bmp *.jpg)");
}
