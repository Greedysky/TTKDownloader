#include "downloadbackgroundconfigmanager.h"

DownloadSkinConfigManager::DownloadSkinConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadSkinConfigManager::writeSkinXMLConfig(const DownloadSkinConfigItem &item, const QString &path)
{
    //Open wirte file
    if(!writeConfig(path))
    {
        return;
    }
    ///////////////////////////////////////////////////////
    createProcessingInstruction();
    ///////////////////////////////////////////////////////
    QDomElement playerDom = createRoot("TTKSkin");
    //Class A
    writeDomElement(playerDom, "creator", DownloadXmlAttribute("value", APPNAME));
    writeDomElement(playerDom, "name", DownloadXmlAttribute("value", item.m_name));
    writeDomElement(playerDom, "useCount", DownloadXmlAttribute("value", item.m_useCount));

    //Write to file
    QTextStream out(m_file);
    m_ddom->save(out, 4);
}

void DownloadSkinConfigManager::readSkinXMLConfig(DownloadSkinConfigItem &item)
{
    item.m_name = readXmlAttributeByTagNameValue("name");
    item.m_useCount = readXmlAttributeByTagNameValue("useCount").toInt();
}
