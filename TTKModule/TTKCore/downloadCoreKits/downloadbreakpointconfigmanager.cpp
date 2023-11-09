#include "downloadbreakpointconfigmanager.h"

DownloadBreakPointConfigManager::DownloadBreakPointConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

bool DownloadBreakPointConfigManager::readBuffer(DownloadBreakPointItemList &items)
{
    QDomNodeList nodes = m_document->elementsByTagName("value");
    for(int i = 0; i < nodes.count(); ++i)
    {
        const QDomElement &element = nodes.item(i).toElement();

        DownloadBreakPointItem item;
        item.m_ready = element.attribute("ready").toLongLong();
        item.m_end = element.attribute("end").toLongLong();
        item.m_start = element.attribute("start").toLongLong();
        items << item;
    }

    nodes = m_document->elementsByTagName("url");
    for(int i = 0; i < nodes.count(); ++i)
    {
        for(DownloadBreakPointItem &item : items)
        {
            item.m_url = nodes.item(i).toElement().text();
        }
    }

    return true;
}

bool DownloadBreakPointConfigManager::writeBuffer(const DownloadBreakPointItemList &items)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot(TTK_APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "breakPoint");

    if(!items.isEmpty())
    {
        writeDomText(recordDom, "url", items.front().m_url);
    }

    for(const DownloadBreakPointItem &item : qAsConst(items))
    {
        writeDomMutilElement(recordDom, "value", {TTKXmlAttribute("start", item.m_start),
                                                  TTKXmlAttribute("end", item.m_end),
                                                  TTKXmlAttribute("ready", item.m_ready)});
    }

    save();
    return true;
}
