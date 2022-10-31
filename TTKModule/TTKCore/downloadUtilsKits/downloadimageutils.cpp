#include "downloadimageutils.h"

#include <QBuffer>
#include <QPainter>

void DownloadUtils::Image::fusionPixmap(QPixmap &back, const QPixmap &front, const QPoint &pt)
{
    if(front.isNull())
    {
        return;
    }

    QPainter painter(&back);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.drawPixmap(pt.x(), pt.y(), front);
}

QByteArray DownloadUtils::Image::generatePixmapData(const QPixmap &input)
{
    if(input.isNull())
    {
        return QByteArray();
    }

    QByteArray data;
    QBuffer buffer(&data);
    if(buffer.open(QIODevice::WriteOnly))
    {
        input.save(&buffer, "jpg");
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

void DownloadUtils::Image::reRenderImage(qint64 &avg, int delta, const QImage *input, QImage *output)
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
