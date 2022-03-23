#include "downloadrecordconfigmanager.h"

DownloadRecordConfigManager::DownloadRecordConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadRecordConfigManager::writeDownloadConfig(const DownloadRecordList &records)
{
    if(!writeConfig(HISTORY_PATH_FULL))
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement player = createRoot(APP_NAME);
    QDomElement download = writeDomNode(player, "history");

    for(const DownloadRecord &record : qAsConst(records))
    {
        writeDomElementMutil(download, "value", DownloadXmlAttributeList() <<
                                                DownloadXmlAttribute("name", record.m_path) <<
                                                DownloadXmlAttribute("size", record.m_size) <<
                                                DownloadXmlAttribute("time", record.m_time) <<
                                                DownloadXmlAttribute("url", record.m_url));
    }

    //Write to file
    QTextStream out(m_file);
    m_document->save(out, 4);
}

void DownloadRecordConfigManager::readDownloadConfig(DownloadRecordList &records)
{
    const QDomNodeList &nodelist = m_document->elementsByTagName("value");
    for(int i = 0; i < nodelist.count(); ++i)
    {
        const QDomElement &element = nodelist.at(i).toElement();
        DownloadRecord record;
        record.m_path = element.attribute("name");
        record.m_time = element.attribute("time");
        record.m_size = element.attribute("size");
        record.m_url = element.attribute("url");
        records << record;
    }
}
