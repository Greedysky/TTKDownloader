#include "downloadthunderskinrequest.h"
#include "downloaddatasourcerequest.h"

static constexpr int MAX_SIZE = 30;
static constexpr const char *QUERY_URL = "K3RCVkdSMXZlSzJ3aVV2d2w4TFBZOGZMcmIzT3MxTzcrQ1lGTEhSNGZFbEJNRzRiK29YUC9ZOVZ2MnhvajlYdXlwMnhxRFpBbStnPQ==";

DownloadThunderSkinConfigManager::DownloadThunderSkinConfigManager()
    : TTKAbstractXml()
{

}

bool DownloadThunderSkinConfigManager::readBuffer(DownloadSkinRemoteGroupList &items)
{
    const QDomNodeList &nodes = m_document->elementsByTagName("group");
    for(int i = 0; i < nodes.count(); ++i)
    {
        DownloadSkinRemoteGroup group;
        QDomNode node = nodes.item(i);
        group.m_name = node.toElement().attribute("name");

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

    return true;
}



DownloadThunderSkinRequest::DownloadThunderSkinRequest(QObject *parent)
    : QObject(parent)
{

}

void DownloadThunderSkinRequest::startToRequest()
{
    DownloadDataSourceRequest *req = new DownloadDataSourceRequest(this);
    connect(req, SIGNAL(downloadRawDataChanged(QByteArray)), SLOT(downloadFinished(QByteArray)));
    req->startToRequest(TTK::Algorithm::mdII(QUERY_URL, false));
}

void DownloadThunderSkinRequest::downloadFinished(const QByteArray &bytes)
{
    DownloadSkinRemoteGroupList items;
    DownloadThunderSkinConfigManager manager;
    if(manager.fromByteArray(bytes))
    {
        manager.readBuffer(items);
    }

    Q_EMIT downloadDataChanged(items);
}
