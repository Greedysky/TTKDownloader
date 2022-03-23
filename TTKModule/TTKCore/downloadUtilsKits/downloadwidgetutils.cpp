#include "downloadwidgetutils.h"
#include "downloadobject.h"

#include <QBuffer>
#include <QPainter>
#include <QFileDialog>

void DownloadUtils::Widget::setTransparent(QWidget *widget, int alpha)
{
    QPalette pal = widget->palette();
    pal.setBrush(QPalette::Base, QBrush(QColor(0xFF, 0xFF, 0xFF, alpha)));
    widget->setPalette(pal);
}

void DownloadUtils::Widget::fusionPixmap(QPixmap &bg, const QPixmap &fg, const QPoint &pt)
{
    if(fg.isNull())
    {
        return;
    }

    QPainter painter(&bg);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawPixmap(pt.x(), pt.y(), fg);
    painter.end();
}

QByteArray DownloadUtils::Widget::generatePixmapData(const QPixmap &pix)
{
    if(pix.isNull())
    {
        return QByteArray();
    }

    QByteArray data;
    QBuffer buffer(&data);
    if(buffer.open(QIODevice::WriteOnly))
    {
        pix.save(&buffer, JPG_FILE_PREFIX);
    }
    buffer.close();
    return data;
}

static int colorBurnTransform(int c, int delta)
{
    if(0 > delta || delta > 0xFF)
    {
        return c;
    }

    const int result = (c - (c * delta)/(0xFF - delta));
    if(result > 0xFF)
    {
        return 0xFF;
    }
    else if(result < 0)
    {
        return 0;
    }
    return result;
}

void DownloadUtils::Widget::reRenderImage(qint64 &avg, int delta, const QImage *input, QImage *output)
{
   if(input->isNull())
   {
       return;
   }

   QRgb r = 0, g = 0, b = 0;
   for(int w = 0; w < input->width(); ++w)
   {
       for(int h = 0; h < input->height(); ++h)
       {
           QRgb rgb = input->pixel(w, h);
           r += qRed(rgb);
           g += qGreen(rgb);
           b += qBlue(rgb);
           output->setPixel(w, h, qRgb(colorBurnTransform(qRed(rgb), delta),
                                       colorBurnTransform(qGreen(rgb), delta),
                                       colorBurnTransform(qBlue(rgb), delta)));
       }
   }

   const int size = input->width() * input->height();
   r /= size;
   g /= size;
   b /= size;
   avg = qRgb(r, g, b);
}

QString DownloadUtils::Widget::openFileDialog(QWidget *obj)
{
    return QFileDialog::getOpenFileName(obj, QObject::tr("choose a filename to open under"), QDir::currentPath(), "Images (*.png *.bmp *.jpg)");
}
