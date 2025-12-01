#include "downloadbreakpointconfigmanager.h"

DownloadBreakPointConfigManager::DownloadBreakPointConfigManager()
    : TTKAbstractXml()
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
    QDomElement recordDom = writeDomElement(rootDom, "breakPoint");

    if(!items.isEmpty())
    {
        writeDomElement(recordDom, "url", items.first().m_url);
    }

    for(const DownloadBreakPointItem &item : qAsConst(items))
    {
        writeDomMultiElement(recordDom, "value", {{"start", item.m_start},
                                                  {"end", item.m_end},
                                                  {"ready", item.m_ready}});
    }

    save();
    return true;
}
