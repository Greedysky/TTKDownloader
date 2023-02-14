#include "downloadbreakpointconfigmanager.h"

DownloadBreakPointConfigManager::DownloadBreakPointConfigManager(QObject *parent)
    : TTKAbstractXml(parent)
{

}

void DownloadBreakPointConfigManager::writeBreakPointConfig(const DownloadBreakPointItemList &records)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot(APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "breakPoint");

    if(!records.isEmpty())
    {
        writeDomText(recordDom, "url", records.front().m_url);
    }

    for(const DownloadBreakPointItem &record : qAsConst(records))
    {
        writeDomMutilElement(recordDom, "value", TTKXmlAttributeList() <<
                                                 TTKXmlAttribute("start", record.m_start) <<
                                                 TTKXmlAttribute("end", record.m_end) <<
                                                 TTKXmlAttribute("ready", record.m_ready));
    }

    QTextStream out(m_file);
    m_document->save(out, 4);
}

void DownloadBreakPointConfigManager::readBreakPointConfig(DownloadBreakPointItemList &records)
{
    QDomNodeList nodes = m_document->elementsByTagName("value");
    for(int i = 0; i < nodes.count(); ++i)
    {
        DownloadBreakPointItem record;
        const QDomElement &element = nodes.item(i).toElement();
        record.m_ready = element.attribute("ready").toLongLong();
        record.m_end = element.attribute("end").toLongLong();
        record.m_start = element.attribute("start").toLongLong();
        records << record;
    }

    nodes = m_document->elementsByTagName("url");
    for(int i = 0; i < nodes.count(); ++i)
    {
        for(int j = 0; j < records.count(); ++j)
        {
            records[j].m_url = nodes.item(i).toElement().text();
        }
    }
}
