#include "downloadfunctionlistwidget.h"

#include <QPainter>
#include <QBoxLayout>

DownloadFunctionItemWidget::DownloadFunctionItemWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(205, 35);
    m_enterIn = false;
    m_selectedOn = false;
    m_resizeMode = false;
}

QString DownloadFunctionItemWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadFunctionItemWidget::setLabelText(const QString &text)
{
    m_text = text;
}

void DownloadFunctionItemWidget::setLabelIcon(const QString &iconf, const QString &iconb)
{
    m_iconf = iconf;
    m_iconb = iconb;
}

void DownloadFunctionItemWidget::setSelectedMode(bool select)
{
    m_selectedOn = select;
    update();
}

void DownloadFunctionItemWidget::resizeMode(bool mode)
{
    m_resizeMode = mode;
    setFixedWidth(mode ? 75 : 205);
    update();
}

void DownloadFunctionItemWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    m_selectedOn = true;
    emit selectedChanged(this);
    update();
}

void DownloadFunctionItemWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    m_enterIn = (m_selectedOn ? false : true);
    update();
}

void DownloadFunctionItemWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    m_enterIn = false;
    update();
}

void DownloadFunctionItemWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    if(m_selectedOn)
    {
        painter.fillRect(rect(), QColor(0, 0, 0, 100));

        QPolygon py;
        py.append(QPoint(width(), height()/2 - 7));
        py.append(QPoint(width() - 7, height()/2));
        py.append(QPoint(width(), height()/2 + 7));
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);
        painter.drawPolygon(py);
    }
    else
    {
        painter.fillRect(rect(), m_enterIn ? QColor(0, 0, 0, 50) : QColor(0, 0, 0, 0));
    }

    if(!m_resizeMode)
    {
        painter.drawPixmap(45, 8, QPixmap(m_enterIn ? m_iconf : m_iconb));
        painter.setPen(m_enterIn ? QColor(255, 255, 255) : QColor(222, 222, 222));
        painter.drawText(QRect(70, 0, 130, height()), Qt::AlignLeft | Qt::AlignVCenter, m_text);
    }
    else
    {
        QPixmap pix(m_enterIn ? m_iconf : m_iconb);
        painter.drawPixmap((width() - pix.width())/2, 8, pix);
    }
}



DownloadFunctionListWidget::DownloadFunctionListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 18, 0, 0);
    layout->setSpacing(0);

    DownloadFunctionItemWidget *item = new DownloadFunctionItemWidget(this);
    item->setLabelText(tr("Download"));
    item->setLabelIcon(":/appTools/item_download_hover", ":/appTools/item_download_normal");
    item->setSelectedMode(true);
    connect(item, SIGNAL(selectedChanged(DownloadFunctionItemWidget*)), SLOT(selectedChanged(DownloadFunctionItemWidget*)));
    layout->addWidget(item);
    m_items << item;

    item = new DownloadFunctionItemWidget(this);
    item->setLabelText(tr("Finished"));
    item->setLabelIcon(":/appTools/item_finished_hover", ":/appTools/item_finished_normal");
    connect(item, SIGNAL(selectedChanged(DownloadFunctionItemWidget*)), SLOT(selectedChanged(DownloadFunctionItemWidget*)));
    layout->addWidget(item);
    m_items << item;

    item = new DownloadFunctionItemWidget(this);
    item->setLabelText(tr("Delete"));
    item->setLabelIcon(":/appTools/item_delete_hover", ":/appTools/item_delete_normal");
    connect(item, SIGNAL(selectedChanged(DownloadFunctionItemWidget*)), SLOT(selectedChanged(DownloadFunctionItemWidget*)));
    layout->addWidget(item);
    m_items << item;

    layout->addStretch(1);
    setLayout(layout);
}

DownloadFunctionListWidget::~DownloadFunctionListWidget()
{
    qDeleteAll(m_items);
}

QString DownloadFunctionListWidget::getClassName()
{
    return staticMetaObject.className();
}

void DownloadFunctionListWidget::resizeMode(bool mode)
{
    foreach(DownloadFunctionItemWidget *it, m_items)
    {
        it->resizeMode(mode);
    }
}

void DownloadFunctionListWidget::selectedChanged(DownloadFunctionItemWidget *item)
{
    int index = m_items.indexOf(item);
    if(index == -1)
    {
        return;
    }

    emit currentIndexChanged(index);

    foreach(DownloadFunctionItemWidget *it, m_items)
    {
        it->setSelectedMode(false);
    }
    m_items[index]->setSelectedMode(true);
}

void DownloadFunctionListWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
