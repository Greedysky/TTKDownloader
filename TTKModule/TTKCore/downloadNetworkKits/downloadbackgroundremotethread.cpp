#include "downloadbackgroundremotethread.h"
#include "downloadsourcethread.h"

#define D_URL   "ZGlhbXFHSDhQemdMb3QyN1dVZlQ4elhzSnZsOWozT2hpSVFORXNDOWhOc2ZtWXZWZ3BYRU5USHg5ZytMQUFRS3FZbnc0Q2ZHMk40PQ=="

DownloadSkinRemoteConfigManager::DownloadSkinRemoteConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadSkinRemoteConfigManager::readSkinRemoteXMLConfig(DownloadSkinRemoteGroups &items)
{
    QDomNodeList nodelist = m_ddom->elementsByTagName("group");
    for(int i=0; i<nodelist.count(); ++i)
    {
        DownloadSkinRemoteGroup group;
        QDomNode node = nodelist.at(i);
        group.m_group = node.toElement().attribute("name");

        QDomNodeList grouplist = node.childNodes();
        for(int j=0; j<grouplist.count(); ++j)
        {
            node = grouplist.at(j);

            DownloadSkinRemoteItem item;
            QDomNodeList packagelist = node.childNodes();
            for(int k=0; k<packagelist.count(); ++k)
            {
                QDomElement ele = packagelist.at(k).toElement();
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
    download->startToDownload(DownloadUtils::Algorithm::mdII(D_URL, false));
}

void DownloadBackgroundRemoteThread::downLoadDataFinished(const QByteArray &bytes)
{
    DownloadSkinRemoteGroups items;

    DownloadSkinRemoteConfigManager manager;
    if(manager.fromByteArray(bytes))
    {
        manager.readSkinRemoteXMLConfig(items);
    }

    emit downLoadDataChanged(items);
}
