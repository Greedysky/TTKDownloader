#include "downloadrecordconfigmanager.h"

DownloadRecordConfigManager::DownloadRecordConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

QString DownloadRecordConfigManager::getClassName()
{
    return staticMetaObject.className();
}

void DownloadRecordConfigManager::writeDownloadConfig(const DownloadRecords &records)
{
    if( !writeConfig(HISTORYPATH_FULL) )
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement player = createRoot(APPNAME);
    QDomElement download = writeDom(player, "history");

    foreach(const DownloadRecord &record, records)
    {
        writeDomElementMutil(download, "value", DownloadXmlAttributes() << DownloadXmlAttribute("name", record.m_path)
                                             << DownloadXmlAttribute("size", record.m_size)
                                             << DownloadXmlAttribute("time", record.m_time));
    }

    //Write to file
    QTextStream out(m_file);
    m_ddom->save(out, 4);
}

void DownloadRecordConfigManager::readDownloadConfig(DownloadRecords &records)
{
    QDomNodeList nodelist = m_ddom->elementsByTagName("value");
    for(int i=0; i<nodelist.count(); ++i)
    {
        DownloadRecord record;
        record.m_path = nodelist.at(i).toElement().attribute("name");
        record.m_time = nodelist.at(i).toElement().attribute("time");
        record.m_size = nodelist.at(i).toElement().attribute("size");
        records << record;
    }
}
