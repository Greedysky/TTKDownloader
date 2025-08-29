#include "downloadtoastlabel.h"
#include "downloadapplication.h"
#include "ttktoastlabel.h"

void DownloadToastLabel::popup(const QString &text)
{
    TTKToastLabel *label = new TTKToastLabel(DownloadApplication::instance());
    label->setText(text);
    label->popup();
}
