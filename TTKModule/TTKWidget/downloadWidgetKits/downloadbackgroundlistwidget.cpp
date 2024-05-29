#include "downloadbackgroundlistwidget.h"
#include "downloadextractwrapper.h"
#include "downloadmessagebox.h"

#include <QPainter>
#include <QMouseEvent>

static constexpr int ITEM_COUNT = 4;

DownloadBackgroundListItem::DownloadBackgroundListItem(QWidget *parent)
    : QLabel(parent),
      m_isSelected(false),
      m_printMask(false),
      m_selectedEnabled(true),
      m_closeEnabled(false)
{
    setFixedSize(100, 70);
    setCursor(Qt::PointingHandCursor);
}

void DownloadBackgroundListItem::updatePixImage()
{
    if(!m_path.isEmpty())
    {
        DownloadBackgroundImage image;
        if(DownloadExtractWrapper::outputSkin(&image, m_path))
        {
            updatePixImage(image);
        }
    }
}

void DownloadBackgroundListItem::updatePixImage(const DownloadBackgroundImage &image)
{
    m_imageInfo = image.m_item;
    setPixmap(image.m_pix.scaled(size()));
}

bool DownloadBackgroundListItem::contains(const DownloadSkinConfigItem &item) const
{
    if(item.isValid() && m_imageInfo.isValid())
    {
        return item.m_name == m_imageInfo.m_name;
    }
    return false;
}

void DownloadBackgroundListItem::setSelected(bool s)
{
    m_isSelected = s;
    update();
}

void DownloadBackgroundListItem::setSelectEnabled(bool s)
{
    m_selectedEnabled = s;
    update();
}

void DownloadBackgroundListItem::setCloseEnabled(bool s)
{
    m_closeEnabled = s;
    update();
}

void DownloadBackgroundListItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(m_closeEnabled && QRect(width() - 18 - 4, 4, 18, 18).contains(event->pos()))
    {
        Q_EMIT closeClicked(this);
    }
    else
    {
        Q_EMIT itemClicked(this);
    }
}

void DownloadBackgroundListItem::leaveEvent(QEvent *event)
{
    QLabel::leaveEvent(event);
    m_printMask = false;
    update();
}

void DownloadBackgroundListItem::enterEvent(QtEnterEvent *event)
{
    QLabel::enterEvent(event);
    m_printMask = true;
    update();
}

void DownloadBackgroundListItem::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    if(m_isSelected && m_selectedEnabled)
    {
        QPainter painter(this);
        painter.drawPixmap(width() - 17, height() - 17, 17, 17, QPixmap(":/tiny/lb_selected"));
    }

    if(m_printMask)
    {
        QPainter painter(this);
        painter.fillRect(rect(), QColor(0, 0, 0, 155));

        QFont font = painter.font();
        font.setPixelSize(13);
        painter.setFont(font);

        painter.setPen(Qt::white);
        const QFontMetrics ftm(font);
        QString v = QString::number(m_imageInfo.m_useCount);
        painter.drawText((width() - QtFontWidth(ftm, v)) / 2, 30, v);
                v = m_imageInfo.m_name;
        painter.drawText((width() - QtFontWidth(ftm, v)) / 2, 48, v);

        if(m_closeEnabled)
        {
            QPainter painter(this);
            painter.drawPixmap(width() - 18 - 4, 4, 18, 18, QPixmap(":/functions/btn_close_hover"));
        }
    }
}


DownloadBackgroundListWidget::DownloadBackgroundListWidget(QWidget *parent)
    : QWidget(parent),
      m_type(CachedModule),
      m_currentItem(nullptr)
{
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_gridLayout->setContentsMargins(7, 0, 7, 0);
    m_gridLayout->setSpacing(5);
    setLayout(m_gridLayout);
}

DownloadBackgroundListWidget::~DownloadBackgroundListWidget()
{
    clearItems();
    delete m_gridLayout;
}

void DownloadBackgroundListWidget::setCurrentItemName(const QString &name)
{
    for(DownloadBackgroundListItem *item : qAsConst(m_items))
    {
        if(item->fileName() == name)
        {
            item->setSelected(true);
            m_currentItem = item;
            break;
        }
    }
}

void DownloadBackgroundListWidget::clearState()
{
    for(DownloadBackgroundListItem *item : qAsConst(m_items))
    {
        item->setSelected(false);
    }
}

void DownloadBackgroundListWidget::clearItems()
{
    qDeleteAll(m_items);
    m_items.clear();
    m_currentItem = nullptr;
}

void DownloadBackgroundListWidget::addCellItem(const QString &icon, bool state)
{
    DownloadBackgroundListItem *item = new DownloadBackgroundListItem(this);
    item->setCloseEnabled(state);
    item->setPixmap(QPixmap(icon).scaled(item->size()));

    connect(item, SIGNAL(itemClicked(DownloadBackgroundListItem*)), SLOT(currentItemClicked(DownloadBackgroundListItem*)));
    connect(item, SIGNAL(closeClicked(DownloadBackgroundListItem*)), SLOT(itemCloseClicked(DownloadBackgroundListItem*)));
    m_gridLayout->addWidget(item, m_items.count()/ITEM_COUNT, m_items.count()%ITEM_COUNT, Qt::AlignLeft | Qt::AlignTop);
    m_items << item;
}

void DownloadBackgroundListWidget::addCellItem(const QString &name, const QString &path, bool state)
{
    DownloadBackgroundListItem *item = new DownloadBackgroundListItem(this);
    item->setCloseEnabled(state);
    item->setFileName(name);
    item->setFilePath(path);
    item->updatePixImage();

    connect(item, SIGNAL(itemClicked(DownloadBackgroundListItem*)), SLOT(currentItemClicked(DownloadBackgroundListItem*)));
    connect(item, SIGNAL(closeClicked(DownloadBackgroundListItem*)), SLOT(itemCloseClicked(DownloadBackgroundListItem*)));
    m_gridLayout->addWidget(item, m_items.count()/ITEM_COUNT, m_items.count()%ITEM_COUNT, Qt::AlignLeft | Qt::AlignTop);
    m_items << item;
}

void DownloadBackgroundListWidget::updateItem(const DownloadBackgroundImage &image, const QString &path)
{
    for(DownloadBackgroundListItem *item : qAsConst(m_items))
    {
        if(item->fileName().isEmpty())
        {
            item->setSelectEnabled(false);
            item->setFileName(path);
            item->updatePixImage(image);
            break;
        }
    }
}

bool DownloadBackgroundListWidget::contains(const QString &name) const
{
    for(DownloadBackgroundListItem *item : qAsConst(m_items))
    {
        if(item->fileName() == name)
        {
            return true;
        }
    }

    return false;
}

bool DownloadBackgroundListWidget::contains(const DownloadBackgroundImage &image) const
{
    for(DownloadBackgroundListItem *item : qAsConst(m_items))
    {
        if(item->contains(image.m_item))
        {
            return true;
        }
    }

    return false;
}

int DownloadBackgroundListWidget::find(DownloadBackgroundListItem *item) const
{
    for(int i = 0; i < m_items.count(); ++i)
    {
        if(m_items[i] == item)
        {
            return i;
        }
    }

    return -1;
}

DownloadBackgroundListItem* DownloadBackgroundListWidget::find(const QString &name) const
{
    for(DownloadBackgroundListItem *item : qAsConst(m_items))
    {
        if(item->fileName() == name)
        {
            return item;
        }
    }

    return nullptr;
}

DownloadBackgroundListItem* DownloadBackgroundListWidget::find(const DownloadBackgroundImage &image) const
{
    for(DownloadBackgroundListItem *item : qAsConst(m_items))
    {
        if(item->contains(image.m_item))
        {
            return item;
        }
    }

    return nullptr;
}

void DownloadBackgroundListWidget::updateLastItem()
{
    if(!m_items.isEmpty())
    {
        currentItemClicked(m_items.back());
    }
}

void DownloadBackgroundListWidget::itemCloseClicked(DownloadBackgroundListItem *item)
{
    if(m_items.count() == 1)
    {
        DownloadMessageBox message;
        message.setText(tr("Last One Item Can not be deleted"));
        message.exec();
        return;
    }

    m_gridLayout->removeWidget(item);
    const int index = find(item);
    const int cIndex = find(m_currentItem);
    QFile::remove(item->filePath());
    m_items.takeAt(index)->deleteLater();

    if(index == cIndex)
    {
        m_currentItem = nullptr;
        if(!m_items.isEmpty())
        {
            currentItemClicked(m_items[index == 0 ? 0 : index - 1]);
        }
    }

    for(int i = index; i < m_items.count(); ++i)
    {
        m_gridLayout->addWidget(m_items[i], i/ITEM_COUNT, i%ITEM_COUNT, Qt::AlignLeft | Qt::AlignTop);
    }
}

void DownloadBackgroundListWidget::currentItemClicked(DownloadBackgroundListItem *item)
{
    if(m_currentItem)
    {
        m_currentItem->setSelected(false);
    }

    m_currentItem = item;
    item->setSelected(true);
    Q_EMIT itemClicked(m_type, item->fileName());
}
