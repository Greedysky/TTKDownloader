#include "downloadfileutils.h"

#include <QFileDialog>

QString TTK::File::getOpenFileName(QWidget *parent)
{
    return QFileDialog::getOpenFileName(parent, QObject::tr("choose a filename to open under"), QDir::currentPath(), "Image Files (*.png *.bmp *.jpg);;TKM Files (*.tkm)");
}
