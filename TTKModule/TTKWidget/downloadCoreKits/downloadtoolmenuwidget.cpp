#include "downloadtoolmenuwidget.h"
#include "downloaduiobject.h"

#include <QWidgetAction>

DownloadToolMenu::DownloadToolMenu(QWidget *parent)
    : QMenu(parent)
{

}

void DownloadToolMenu::showEvent(QShowEvent *event)
{
    QMenu::showEvent(event);
    Q_EMIT windowStateChanged(true);
}

void DownloadToolMenu::hideEvent(QHideEvent *event)
{
    QMenu::hideEvent(event);
    Q_EMIT windowStateChanged(false);
}


DownloadToolMenuWidget::DownloadToolMenuWidget(QWidget *parent)
    : QToolButton(parent)
{
    setCursor(Qt::PointingHandCursor);

    m_menu = new DownloadToolMenu(this);
    QWidgetAction *actionWidget = new QWidgetAction(m_menu);
    m_containWidget = new QWidget(m_menu);

    actionWidget->setDefaultWidget(m_containWidget);
    m_menu->addAction(actionWidget);

    connect(this, SIGNAL(clicked()), SLOT(popupMenu()));
}

DownloadToolMenuWidget::~DownloadToolMenuWidget()
{
    delete m_containWidget;
    delete m_menu;
}

void DownloadToolMenuWidget::setTranslucentBackground()
{
    m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint);
    m_menu->setAttribute(Qt::WA_TranslucentBackground);
    m_menu->setStyleSheet(TTK::UI::MenuStyle04);
}

void DownloadToolMenuWidget::popupMenu()
{
    QPoint pos = mapToGlobal(QPoint(0, 0));
    pos.setY(pos.y() - m_containWidget->height() - 10);
    pos.setX(pos.x() - (m_containWidget->width() - width()) / 2);

    m_menu->exec(pos);
}
