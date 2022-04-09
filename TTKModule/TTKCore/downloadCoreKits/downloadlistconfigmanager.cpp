#include "downloadlistconfigmanager.h"

DownloadListConfigManager::DownloadListConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadListConfigManager::writeListConfig(const DownloadItemList &records)
{
    if(!writeConfig(LIST_PATH_FULL))
    {
        return;
    }

    createProcessingInstruction();
    QDomElement rootDom = createRoot(APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "list");

    for(const DownloadItem &record : qAsConst(records))
    {
        writeDomMutilElement(recordDom, "value", DownloadXmlAttributeList() <<
                                                 DownloadXmlAttribute("url", record.m_url) <<
                                                 DownloadXmlAttribute("name", record.m_name));
    }

    QTextStream out(m_file);
    m_document->save(out, 4);
}

void DownloadListConfigManager::readListConfig(DownloadItemList &records)
{
    const QDomNodeList &nodelist = m_document->elementsByTagName("value");
    for(int i = 0; i < nodelist.count(); ++i)
    {
        const QDomElement &element = nodelist.at(i).toElement();
        DownloadItem record;
        record.m_url = element.attribute("url");
        record.m_name = element.attribute("name");
        records << record;
    }
}
