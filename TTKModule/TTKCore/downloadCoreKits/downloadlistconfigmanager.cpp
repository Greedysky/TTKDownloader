#include "downloadlistconfigmanager.h"

DownloadListConfigManager::DownloadListConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

bool DownloadListConfigManager::readBuffer(DownloadItemList &items)
{
    const QDomNodeList &nodes = m_document->elementsByTagName("value");
    for(int i = 0; i < nodes.count(); ++i)
    {
        const QDomElement &element = nodes.item(i).toElement();

        DownloadItem item;
        item.m_url = element.attribute("url");
        item.m_name = element.attribute("name");
        items << item;
    }

    return true;
}

bool DownloadListConfigManager::writeBuffer(const DownloadItemList &items)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot(TTK_APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "list");

    for(const DownloadItem &item : qAsConst(items))
    {
        writeDomMutilElement(recordDom, "value", {TTKXmlAttribute("url", item.m_url),
                                                  TTKXmlAttribute("name", item.m_name)});
    }

    save();
    return true;
}
