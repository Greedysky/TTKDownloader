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
    if(!writeConfig(LISTPATH_FULL))
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement player = createRoot(APPNAME);
    QDomElement download = writeDom(player, "list");

    foreach(const DownloadList &record, records)
    {
        writeDomElementMutil(download, "value", DownloadXmlAttributes() << DownloadXmlAttribute("url", record.m_url)
                                             << DownloadXmlAttribute("name", record.m_name));
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
        const QDomElement element = nodelist.at(i).toElement();
        DownloadList record;
        record.m_url = element.attribute("url");
        record.m_name = element.attribute("name");
        records << record;
    }
}
