#include "downloadbackgroundremotethread.h"
#include "downloadsourcethread.h"

#define QUERY_URL   "eC9KOTYxbVhvVDJNcGEwckhyMVZRdVRhOHhFRHQ2eFVNdWJxaURFSzA1ZWVmZm5HOFlzS1VCY2ZKOFRlYStBL2Y3SjNEK2gzY2QwPQ=="

DownloadSkinRemoteConfigManager::DownloadSkinRemoteConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadSkinRemoteConfigManager::readSkinRemoteXMLConfig(DownloadSkinRemoteGroupList &items)
{
    const QDomNodeList &nodelist = m_document->elementsByTagName("group");
    for(int i = 0; i < nodelist.count(); ++i)
    {
        DownloadSkinRemoteGroup group;
        QDomNode node = nodelist.at(i);
        group.m_group = node.toElement().attribute("name");

        const QDomNodeList &grouplist = node.childNodes();
        for(int j = 0; j < grouplist.count(); ++j)
        {
            node = grouplist.at(j);

            DownloadSkinRemoteItem item;
            const QDomNodeList &packagelist = node.childNodes();
            for(int k = 0; k < packagelist.count(); ++k)
            {
                const QDomElement &ele = packagelist.at(k).toElement();
                if(ele.nodeName() == "name")
                {
                    item.m_name = ele.text();
                }
                else if(ele.nodeName() == "popularity")
                {
                    item.m_useCount = ele.text().toInt();
                }
                else if(ele.nodeName() == "file")
                {
                    item.m_url = ele.text();
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
    download->startToDownload(DownloadUtils::Algorithm::mdII(QUERY_URL, false));
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
