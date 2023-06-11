#include "downloadwidgetutils.h"
#include "ttkdesktopwrapper.h"

#include <QMenu>

void TTK::Widget::adjustMenuPosition(QMenu *menu)
{
#if TTK_QT_VERSION_CHECK(5,12,0)
    const QList<QAction*> actions(menu->actions());
    if(!actions.empty())
    {
        QAction* action(actions.front());
        if(action->icon().isNull())
        {
            action->setIcon(QIcon(":/tiny/lb_transparent"));
        }
    }
#else
    Q_UNUSED(menu);
#endif
}

void TTK::Widget::adjustWidgetPosition(QWidget *widget)
{
    const QRect &rect = TTKDesktopWrapper::screenGeometry();
    widget->move((rect.width() - widget->width()) / 2, (rect.height() - widget->height()) / 2);
}

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
