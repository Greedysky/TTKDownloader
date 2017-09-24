#include "downloadbreakpointconfigmanager.h"

DownloadBreakPointConfigManager::DownloadBreakPointConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

QString DownloadBreakPointConfigManager::getClassName()
{
    return staticMetaObject.className();
}

void DownloadBreakPointConfigManager::writeBreakPointConfig(const DownloadBreakPointItems &records)
{
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    QDomElement player = createRoot(APPNAME);
    QDomElement download = writeDom(player, "breakPoint");

    if(!records.isEmpty())
    {
        writeDomText(download, "url", records.first().m_url);
    }

    foreach(const DownloadBreakPointItem &record, records)
    {
        writeDomElementMutil(download, "value", DownloadXmlAttributes() <<
                                                DownloadXmlAttribute("start", record.m_start) <<
                                                DownloadXmlAttribute("end", record.m_end) <<
                                                DownloadXmlAttribute("ready", record.m_ready) );
    }

    //Write to file
    QTextStream out(m_file);
    m_ddom->save(out, 4);
}

void DownloadBreakPointConfigManager::readBreakPointConfig(DownloadBreakPointItems &records)
{
    QDomNodeList nodelist = m_ddom->elementsByTagName("value");
    for(int i=0; i<nodelist.count(); ++i)
    {
        DownloadBreakPointItem record;
        QDomElement element = nodelist.at(i).toElement();
        record.m_ready = element.attribute("ready").toLongLong();
        record.m_end = element.attribute("end").toLongLong();
        record.m_start = element.attribute("start").toLongLong();
        records << record;
    }

    nodelist = m_ddom->elementsByTagName("url");
    for(int i=0; i<nodelist.count(); ++i)
    {
        for(int j=0; j<records.count(); ++j)
        {
            QDomElement element = nodelist.at(i).toElement();
            records[j].m_url = element.text();
        }
    }
}
