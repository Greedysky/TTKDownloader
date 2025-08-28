#include "downloadwidgetutils.h"
#include "downloaduiobject.h"
#include "ttkdesktopscreen.h"

#include <QMenu>
#include <QComboBox>
#include <QScrollBar>
#include <QScrollArea>
#include <QListWidget>
#include <QStyledItemDelegate>

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
    const QRect &rect = TTKDesktopScreen::screenGeometry();
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

void TTK::Widget::generateComboBoxStyle(QComboBox *widget, const QString &style)
{
    widget->setItemDelegate(new QStyledItemDelegate(widget));
    widget->setStyleSheet(style.isEmpty() ? TTK::UI::ComboBoxStyle01 + TTK::UI::ItemView01 : style);
    widget->view()->setStyleSheet(TTK::UI::ScrollBarStyle01);
}

void TTK::Widget::generateVScrollAreaStyle(QWidget *widget, QWidget *parent, bool background)
{
    QScrollArea *area = TTKObjectCast(QScrollArea*, widget);
    if(area)
    {
        const QString &style = background ? TTK::UI::ScrollBarStyle01 : TTK::UI::ScrollBarStyle03;
        area->setWidgetResizable(true);
        area->setFrameShape(QFrame::NoFrame);
        area->setFrameShadow(QFrame::Plain);
        area->setAlignment(Qt::AlignLeft);
        area->setWidget(parent);
        area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        area->setStyleSheet(style);
        area->verticalScrollBar()->setStyleSheet(style);
    }
}

void TTK::Widget::generateHScrollAreaStyle(QWidget *widget, QWidget *parent, bool background)
{
    QScrollArea *area = TTKObjectCast(QScrollArea*, widget);
    if(area)
    {
        const QString &style = background ? TTK::UI::ScrollBarStyle02 : TTK::UI::ScrollBarStyle04;
        area->setWidgetResizable(true);
        area->setFrameShape(QFrame::NoFrame);
        area->setFrameShadow(QFrame::Plain);
        area->setAlignment(Qt::AlignLeft);
        area->setWidget(parent);
        area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        area->setStyleSheet(style);
        area->horizontalScrollBar()->setStyleSheet(style);
    }
}
