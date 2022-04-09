#include "downloadbackgroundconfigmanager.h"

DownloadSkinConfigManager::DownloadSkinConfigManager(QObject *parent)
    : DownloadAbstractXml(parent)
{

}

void DownloadSkinConfigManager::writeSkinXMLConfig(const DownloadSkinConfigItem &item, const QString &path)
{
    if(!writeConfig(path))
    {
        return;
    }

    createProcessingInstruction();
    QDomElement rootDom = createRoot("TTKSkin");

    writeDomElement(rootDom, "creator", DownloadXmlAttribute("value", APP_NAME));
    writeDomElement(rootDom, "name", DownloadXmlAttribute("value", item.m_name));
    writeDomElement(rootDom, "useCount", DownloadXmlAttribute("value", item.m_useCount));

    QTextStream out(m_file);
    m_document->save(out, 4);
}

void DownloadSkinConfigManager::readSkinXMLConfig(DownloadSkinConfigItem &item)
{
    item.m_name = readXmlAttributeByTagNameValue("name");
    item.m_useCount = readXmlAttributeByTagNameValue("useCount").toInt();
}
