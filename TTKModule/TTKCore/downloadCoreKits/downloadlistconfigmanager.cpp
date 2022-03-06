#include "downloadlistconfigmanager.h"

DownloadListConfigManager::DownloadListConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadListConfigManager::writeListConfig(const DownloadItems &records)
{
    if(!writeConfig(LIST_PATH_FULL))
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement player = createRoot(APP_NAME);
    QDomElement download = writeDomNode(player, "list");

    for(const DownloadItem &record : qAsConst(records))
    {
        writeDomElementMutil(download, "value", DownloadXmlAttributes() <<
                                                DownloadXmlAttribute("url", record.m_url) <<
                                                DownloadXmlAttribute("name", record.m_name));
    }

    //Write to file
    QTextStream out(m_file);
    m_document->save(out, 4);
}

void DownloadListConfigManager::readListConfig(DownloadItems &records)
{
    const QDomNodeList &nodelist = m_document->elementsByTagName("value");
    for(int i=0; i<nodelist.count(); ++i)
    {
        const QDomElement &element = nodelist.at(i).toElement();
        DownloadItem record;
        record.m_url = element.attribute("url");
        record.m_name = element.attribute("name");
        records << record;
    }
}
