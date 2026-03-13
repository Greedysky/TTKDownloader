#include "downloadthunderskinrequest.h"

static constexpr int MAX_SIZE = 30;
static constexpr const char *QUERY_URL = "K3RCVkdSMXZlSzJ3aVV2d2w4TFBZOGZMcmIzT3MxTzcrQ1lGTEhSNGZFbEJNRzRiK29YUC9ZOVZ2MnhvajlYdXlwMnhxRFpBbStnPQ==";

DownloadThunderSkinConfigManager::DownloadThunderSkinConfigManager()
    : TTKAbstractXml()
{

}

bool DownloadThunderSkinConfigManager::readBuffer(DownloadSkinRemoteGroupList &groups)
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
            groups << group;
        }
    }

    return true;
}



DownloadThunderSkinRequest::DownloadThunderSkinRequest(QObject *parent)
    : DownloadAbstractNetwork(parent)
{

}

void DownloadThunderSkinRequest::startToRequest()
{
    QNetworkRequest request;
    request.setUrl(TTK::Algorithm::mdII(QUERY_URL, false));
    TTK::setUserAgentHeader(&request);
    TTK::setSslConfiguration(&request);
    TTK::setContentTypeHeader(&request);

    m_reply = m_manager.get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downloadFinished()));
    QtNetworkErrorConnect(m_reply, this, replyError, TTK_SLOT);
}

void DownloadThunderSkinRequest::downloadFinished()
{
    TTK_INFO_STREAM(metaObject()->className() << __FUNCTION__);

    DownloadSkinRemoteGroupList groups;
    DownloadAbstractNetwork::downloadFinished();
    if(m_reply && m_reply->error() == QNetworkReply::NoError)
    {
        DownloadThunderSkinConfigManager manager;
        if(manager.fromByteArray(m_reply->readAll()))
        {
            manager.readBuffer(groups);
        }
    }

    Q_EMIT downloadDataChanged(groups);
    deleteAll();
}
