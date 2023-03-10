#include "downloadbackgroundremotethread.h"
#include "downloadsourcethread.h"

#define QUERY_URL   "eC9KOTYxbVhvVDJNcGEwckhyMVZRdVRhOHhFRHQ2eFVNdWJxaURFSzA1ZWVmZm5HOFlzS1VCY2ZKOFRlYStBL2Y3SjNEK2gzY2QwPQ=="

DownloadSkinRemoteConfigManager::DownloadSkinRemoteConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

void DownloadSkinRemoteConfigManager::readSkinRemoteXMLConfig(DownloadSkinRemoteGroupList &items)
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



DownloadBackgroundRemoteThread::DownloadBackgroundRemoteThread(QObject *parent)
    : QObject(parent)
{

}

void DownloadBackgroundRemoteThread::startToDownload()
{
    DownloadSourceThread *download = new DownloadSourceThread(this);
    connect(download, SIGNAL(downLoadByteDataChanged(QByteArray)), SLOT(downLoadDataFinished(QByteArray)));
    download->startToDownload(TTK::Algorithm::mdII(QUERY_URL, false));
}

void DownloadBackgroundRemoteThread::downLoadDataFinished(const QByteArray &bytes)
{
    DownloadSkinRemoteGroupList items;
    DownloadSkinRemoteConfigManager manager;
    if(manager.fromByteArray(bytes))
    {
        manager.readSkinRemoteXMLConfig(items);
    }

    Q_EMIT downLoadDataChanged(items);
}
