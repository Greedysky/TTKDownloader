#include "downloadbackgroundremotewidget.h"
#include "downloadextractmanager.h"
#include "downloadqueuerequest.h"

#include <QDir>
#include <QPushButton>
#include <QButtonGroup>

DownloadBackgroundOnlineWidget::DownloadBackgroundOnlineWidget(QWidget *parent)
    : QWidget(parent),
      m_currentIndex(-1),
      m_functionsWidget(nullptr),
      m_networkRequest(nullptr),
      m_downloadRequest(nullptr)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(0);

    m_backgroundList = new DownloadBackgroundListWidget(this);
    hbox->addWidget(m_backgroundList);
    setLayout(hbox);

    m_networkRequest = new DownloadQueueRequest(this);
    connect(m_networkRequest, SIGNAL(downLoadDataChanged(QString)), SLOT(downLoadDataChanged(QString)));
    connect(m_backgroundList, SIGNAL(itemClicked(int,QString)), parent, SLOT(remoteListWidgetItemClicked(int,QString)));
}

DownloadBackgroundOnlineWidget::~DownloadBackgroundOnlineWidget()
{
    abort();
    delete m_backgroundList;
    delete m_functionsWidget;
    delete m_networkRequest;
    delete m_downloadRequest;
}

void DownloadBackgroundOnlineWidget::initialize()
{
    if(!m_downloadRequest)
    {
        m_downloadRequest = new DownloadThunderSkinRequest(this);
        connect(m_downloadRequest, SIGNAL(downLoadDataChanged(DownloadSkinRemoteGroupList)), SLOT(downLoadDataChanged(DownloadSkinRemoteGroupList)));
        m_downloadRequest->startToRequest();
    }
}

void DownloadBackgroundOnlineWidget::abort()
{
    m_networkRequest->abort();
}

QWidget* DownloadBackgroundOnlineWidget::createFunctionsWidget(bool revert, QWidget *object)
{
    if(!m_functionsWidget)
    {
        m_functionsWidget = new QWidget(object);
        m_functionsWidget->setGeometry(15, 45, 428, 20);
        m_functionsWidget->hide();

        QHBoxLayout *hbox = new QHBoxLayout(m_functionsWidget);
        hbox->setContentsMargins(9, 0, 0, 9);

        QButtonGroup *buttonGroup = new QButtonGroup(m_functionsWidget);
        QtButtonGroupConnect(buttonGroup, this, buttonClicked, TTK_SLOT);

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
        createButton({});

        m_functionsWidget->setLayout(hbox);
    }

    QHBoxLayout *ly = TTKObjectCast(QHBoxLayout*, m_functionsWidget->layout());
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

void DownloadBackgroundOnlineWidget::outputRemoteSkin(DownloadBackgroundImage &image, const QString &data)
{
    const int index = QFileInfo(data).baseName().toInt();
    DownloadSkinRemoteItemList &items = m_groups[m_currentIndex].m_items;
    if(index >= 0 || index < items.count())
    {
        DownloadSkinRemoteItem &item = items[index];
        image.m_item.m_name = item.m_name;
        image.m_item.m_useCount = item.m_useCount;
        DownloadExtractManager::outputThunderSkin(image.m_pix, data);
    }
}

void DownloadBackgroundOnlineWidget::buttonClicked(int index)
{
    if(index < 0 || index >= m_groups.count())
    {
        return;
    }

    if(m_currentIndex != index)
    {
        m_networkRequest->abort();
    }

    m_currentIndex = index;
    buttonStyleChanged();

    const QDir dir(TTK_DOT);
    dir.mkpath(QString("%1%2").arg(APPCACHE_DIR_FULL).arg(index));

    m_backgroundList->clearItems();
    DownloadQueueDataList datas;
    DownloadSkinRemoteItemList &items = m_groups[index].m_items;
    for(int i = 0; i < items.count(); ++i)
    {
        m_backgroundList->addCellItem(":/image/lb_noneImage", false);
        DownloadQueueData data;
        data.m_url = items[i].m_url;
        data.m_path = QString("%1%2/%3%4").arg(APPCACHE_DIR_FULL).arg(index).arg(i).arg(TKM_FILE);
        datas << data;
    }

    m_networkRequest->addQueue(datas);
    m_networkRequest->startToRequest();
}

void DownloadBackgroundOnlineWidget::downLoadDataChanged(const QString &bytes)
{
    DownloadBackgroundImage image;
    outputRemoteSkin(image, bytes);
    if(!image.isValid())
    {
        image.m_pix = QPixmap(":/image/lb_noneImage");
    }

    m_backgroundList->updateItem(image, bytes);
}

void DownloadBackgroundOnlineWidget::downLoadDataChanged(const DownloadSkinRemoteGroupList &bytes)
{
    m_groups = bytes;
    for(int i = 0; i < m_groups.count(); ++i)
    {
        m_functionsItems[i]->setText(m_groups[i].m_group);
    }

    //Hide left items if the number just not enough
    for(int i = m_groups.count(); i < m_functionsItems.count(); ++i)
    {
        m_functionsItems[i]->hide();
    }
}

QPushButton* DownloadBackgroundOnlineWidget::createButton(const QString &name)
{
    QPushButton *btn = new QPushButton(name, m_functionsWidget);
    btn->setStyleSheet(TTK::UI::PushButtonStyle02);
    btn->setCursor(QCursor(Qt::PointingHandCursor));
    btn->setFixedSize(35, 20);
    btn->hide();
#ifdef Q_OS_UNIX
    btn->setFocusPolicy(Qt::NoFocus);
#endif
    m_functionsItems << btn;
    return btn;
}

void DownloadBackgroundOnlineWidget::buttonStyleChanged()
{
    for(int i = 0; i < m_functionsItems.count() - 1; ++i)
    {
        m_functionsItems[i]->setStyleSheet(TTK::UI::PushButtonStyle02);
    }
    m_functionsItems[m_currentIndex]->setStyleSheet(TTK::UI::PushButtonStyle02 + QString("QPushButton{ %1 }").arg(TTK::UI::ColorStyle03));
}
