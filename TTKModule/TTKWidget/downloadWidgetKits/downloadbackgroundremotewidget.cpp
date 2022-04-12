#include "downloadbackgroundremotewidget.h"
#include "downloadqueuecache.h"
#include "downloadextractwrapper.h"

#include <QDir>
#include <QPushButton>
#include <QButtonGroup>
#include <QBoxLayout>

DownloadBackgroundRemoteWidget::DownloadBackgroundRemoteWidget(QWidget *parent)
    : QWidget(parent), m_downloadQueue(nullptr)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(0);

    m_listWidget = new DownloadBackgroundListWidget(this);
    hbox->addWidget(m_listWidget);
    setLayout(hbox);

    m_currentIndex = -1;
    m_functionsWidget = nullptr;
    m_queryThread = nullptr;

    m_downloadQueue = new DownloadQueueCache(this);
    connect(m_downloadQueue, SIGNAL(downLoadDataChanged(QString)), SLOT(downLoadDataChanged(QString)));
    connect(m_listWidget, SIGNAL(itemClicked(QString)), parent, SLOT(remoteBackgroundListWidgetItemClicked(QString)));
}

DownloadBackgroundRemoteWidget::~DownloadBackgroundRemoteWidget()
{
    abort();
    delete m_listWidget;
    delete m_functionsWidget;
    delete m_downloadQueue;
    delete m_queryThread;
}

void DownloadBackgroundRemoteWidget::initialize()
{
    if(!m_queryThread)
    {
        m_queryThread = new DownloadBackgroundRemoteThread(this);
        connect(m_queryThread, SIGNAL(downLoadDataChanged(DownloadSkinRemoteGroupList)), SLOT(downLoadDataChanged(DownloadSkinRemoteGroupList)));
        m_queryThread->startToDownload();
    }
}

void DownloadBackgroundRemoteWidget::abort()
{
    m_downloadQueue->abort();
}

QWidget* DownloadBackgroundRemoteWidget::createFunctionsWidget(bool revert, QWidget *object)
{
    if(!m_functionsWidget)
    {
        m_functionsWidget = new QWidget(object);
        m_functionsWidget->setGeometry(15, 45, 428, 20);
        m_functionsWidget->hide();

        QHBoxLayout *hbox = new QHBoxLayout(m_functionsWidget);
        hbox->setContentsMargins(9, 0, 0, 9);

        QButtonGroup *buttonGroup = new QButtonGroup(m_functionsWidget);
#if TTK_QT_VERSION_CHECK(5,15,0)
        connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(buttonClicked(int)));
#else
        connect(buttonGroup, SIGNAL(buttonClicked(int)), SLOT(buttonClicked(int)));
#endif
        QStringList names;
        for(int i = 1; i <= 9; ++i)
        {
            names << QString::number(i);
        }

        for(int i = 0; i < names.count(); ++i)
        {
            buttonGroup->addButton(createButton(names[i]), i);
        }

        hbox->addStretch(1);
        QPushButton *p = createButton(tr("ALL"));
        p->setStyleSheet(p->styleSheet() + QString("QPushButton{%1}").arg(DownloadUIObject::MColorStyle08));

        m_functionsWidget->setLayout(hbox);
    }

    QHBoxLayout *ly = TTKStatic_cast(QHBoxLayout*, m_functionsWidget->layout());
    int count = ly->count();
    if(revert)
    {
        while(count > 0)
        {
            --count;
            ly->removeWidget(m_functionsItems[count]);
            ly->removeItem(ly->itemAt(count));
            m_functionsItems[count]->hide();
        }
        ly->addStretch(1);

        m_functionsItems[m_functionsItems.count() - 1]->show();
        ly->addWidget(m_functionsItems[m_functionsItems.count() - 1]);
    }
    else
    {
        while(count > 0)
        {
            --count;
            ly->removeItem(ly->itemAt(count));
        }
        m_functionsItems[m_functionsItems.count() - 1]->hide();

        for(int i = 0; i < m_functionsItems.count() - 1; ++i)
        {
            m_functionsItems[i]->show();
            ly->addWidget(m_functionsItems[i]);
        }
        ly->addStretch(1);
    }

    return m_functionsWidget;
}

void DownloadBackgroundRemoteWidget::outputRemoteSkin(DownloadBackgroundImage &image, const QString &data)
{
    int index = QFileInfo(data).baseName().toInt();
    DownloadSkinRemoteItemList *items = &m_groups[m_currentIndex].m_items;
    if(index >= 0 || index < items->count())
    {
        DownloadSkinRemoteItem *item = &(*items)[index];
        image.m_item.m_name = item->m_name;
        image.m_item.m_useCount = item->m_useCount;
        DownloadExtractWrapper::outputThunderSkin(image.m_pix, data);
    }
}

void DownloadBackgroundRemoteWidget::buttonClicked(int index)
{
    if(index < 0 || index >= m_groups.count())
    {
        return;
    }

    if(m_currentIndex != index)
    {
        m_downloadQueue->abort();
    }

    m_currentIndex = index;
    buttonStyleChanged();

    QDir dir(TTK_DOT);
    dir.mkpath(QString("%1%2").arg(APPCACHE_DIR_FULL).arg(index));

    m_listWidget->clearAllItems();
    DownloadQueueDataList datas;
    DownloadSkinRemoteItemList *items = &m_groups[index].m_items;
    for(int i = 0; i < items->count(); ++i)
    {
        m_listWidget->createItem(":/image/lb_noneImage", false);
        DownloadQueueData data;
        data.m_url = (*items)[i].m_url;
        data.m_savePath = QString("%1%2/%3%4").arg(APPCACHE_DIR_FULL).arg(index).arg(i).arg(TKM_FILE);
        datas << data;
    }

    m_downloadQueue->addImageQueue(datas);
    m_downloadQueue->startToDownload();
}

void DownloadBackgroundRemoteWidget::downLoadDataChanged(const QString &data)
{
    DownloadBackgroundImage image;
    outputRemoteSkin(image, data);
    if(image.isValid())
    {
        m_listWidget->updateItem(image, data);
    }
}

void DownloadBackgroundRemoteWidget::downLoadDataChanged(const DownloadSkinRemoteGroupList &data)
{
    m_groups = data;
    for(int i = 0; i < m_groups.count(); ++i)
    {
        DownloadSkinRemoteGroup *item = &m_groups[i];
        m_functionsItems[i]->setText(item->m_group);
    }

    //Hide left items if the number just not enough
    for(int i = m_groups.count(); i < m_functionsItems.count(); ++i)
    {
        m_functionsItems[i]->hide();
    }
}

QPushButton* DownloadBackgroundRemoteWidget::createButton(const QString &name)
{
    QPushButton *btn = new QPushButton(name, m_functionsWidget);
    btn->setStyleSheet(DownloadUIObject::MPushButtonStyle02);
    btn->setCursor(QCursor(Qt::PointingHandCursor));
    btn->setFixedSize(35, 20);
    btn->hide();
#ifdef Q_OS_UNIX
    btn->setFocusPolicy(Qt::NoFocus);
#endif
    m_functionsItems << btn;

    return btn;
}

void DownloadBackgroundRemoteWidget::buttonStyleChanged()
{
    for(int i = 0; i < m_functionsItems.count() - 1; ++i)
    {
        m_functionsItems[i]->setStyleSheet(DownloadUIObject::MPushButtonStyle02);
    }
    m_functionsItems[m_currentIndex]->setStyleSheet(DownloadUIObject::MPushButtonStyle02 +
                                                    QString("QPushButton{%1}").arg(DownloadUIObject::MColorStyle08));
}
