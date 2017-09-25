#include "downloadlistconfigmanager.h"

DownloadListConfigManager::DownloadListConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

QString DownloadListConfigManager::getClassName()
{
    return staticMetaObject.className();
}

void DownloadListConfigManager::writeListConfig(const DownloadLists &records)
{
    if( !writeConfig(LISTPATH_FULL) )
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement player = createRoot(APPNAME);
    QDomElement download = writeDom(player, "list");

    foreach(const DownloadList &record, records)
    {
        writeDomElement(download, "value", DownloadXmlAttribute("url", record.m_url));
    }

    //Write to file
    QTextStream out(m_file);
    m_ddom->save(out, 4);
}

void DownloadListConfigManager::readListConfig(DownloadLists &records)
{
    QDomNodeList nodelist = m_ddom->elementsByTagName("value");
    for(int i=0; i<nodelist.count(); ++i)
    {
        DownloadList record;
        record.m_url = nodelist.at(i).toElement().attribute("url");
        records << record;
    }
}
