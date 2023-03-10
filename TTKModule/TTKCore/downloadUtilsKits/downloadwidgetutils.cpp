#include "downloadwidgetutils.h"

#include <QWidget>

void TTK::Widget::setTransparent(QWidget *widget, int alpha)
{
    QPalette plt = widget->palette();
    plt.setBrush(QPalette::Base, QBrush(QColor(0xFF, 0xFF, 0xFF, alpha)));
    widget->setPalette(plt);
}

void TTK::Widget::setTransparent(QWidget *widget, const QColor &color)
{
    QPalette plt(widget->palette());
    plt.setBrush(QPalette::Highlight, QBrush(color));
    widget->setPalette(plt);
}
