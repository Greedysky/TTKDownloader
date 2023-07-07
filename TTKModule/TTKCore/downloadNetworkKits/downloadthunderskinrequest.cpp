#include "downloadthunderskinrequest.h"
#include "downloaddatasourcerequest.h"

#define MAX_SIZE    30
#define QUERY_URL   "eC9KOTYxbVhvVDJNcGEwckhyMVZRdVRhOHhFRHQ2eFVNdWJxaURFSzA1ZWVmZm5HOFlzS1VCY2ZKOFRlYStBL2Y3SjNEK2gzY2QwPQ=="

DownloadThunderSkinConfigManager::DownloadThunderSkinConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

void DownloadThunderSkinConfigManager::readBuffer(DownloadSkinRemoteGroupList &items)
{
    const QDomNodeList &nodes = m_document->elementsByTagName("group");
    for(int i = 0; i < nodes.count(); ++i)
    {
        DownloadSkinRemoteGroup group;
        QDomNode node = nodes.item(i);
        group.m_group = node.toElement().attribute("name");

        const QDomNodeList &groupNodes = node.childNodes();
        for(int j = 0; j < groupNodes.count(); ++j)
        {
            if(j > MAX_SIZE)
            {
                break;
            }

            node = groupNodes.item(j);
            const QDomNodeList &packageNodes = node.childNodes();

            DownloadSkinRemoteItem item;
            for(int k = 0; k < packageNodes.count(); ++k)
            {
                const QDomElement &element = packageNodes.item(k).toElement();
                if(element.nodeName() == "name")
                {
                    item.m_name = element.text();
                }
                else if(element.nodeName() == "popularity")
                {
                    item.m_useCount = element.text().toInt();
                }
                else if(element.nodeName() == "file")
                {
                    item.m_url = element.text();
                }
            }

            if(item.isValid())
            {
                group.m_items << item;
            }
        }

        if(group.isValid())
        {
            items << group;
        }
    }
}



DownloadThunderSkinRequest::DownloadThunderSkinRequest(QObject *parent)
    : QObject(parent)
{

}

void DownloadThunderSkinRequest::startRequest()
{
    DownloadDataSourceRequest *download = new DownloadDataSourceRequest(this);
    connect(download, SIGNAL(downLoadRawDataChanged(QByteArray)), SLOT(downLoadFinished(QByteArray)));
    download->startRequest(TTK::Algorithm::mdII(QUERY_URL, false));
}

void DownloadThunderSkinRequest::downLoadFinished(const QByteArray &bytes)
{
    DownloadSkinRemoteGroupList items;
    DownloadThunderSkinConfigManager manager;
    if(manager.fromByteArray(bytes))
    {
        manager.readBuffer(items);
    }

    Q_EMIT downLoadDataChanged(items);
}
