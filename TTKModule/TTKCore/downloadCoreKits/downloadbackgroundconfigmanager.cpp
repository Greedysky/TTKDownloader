#include "downloadbackgroundconfigmanager.h"

DownloadSkinConfigManager::DownloadSkinConfigManager(QObject *parent)
    : TTKAbstractXml(parent)
{

}

void DownloadSkinConfigManager::writeSkinXMLConfig(const DownloadSkinConfigItem &item, const QString &path)
{
    if(!toFile(path))
    {
        return;
    }

    createProcessingInstruction();
    QDomElement rootDom = createRoot("TTKSkin");

    writeDomElement(rootDom, "creator", TTKXmlAttribute("value", APP_NAME));
    writeDomElement(rootDom, "name", TTKXmlAttribute("value", item.m_name));
    writeDomElement(rootDom, "useCount", TTKXmlAttribute("value", item.m_useCount));

    QTextStream out(m_file);
    m_document->save(out, 4);
}

void DownloadSkinConfigManager::readSkinXMLConfig(DownloadSkinConfigItem &item)
{
    item.m_name = readXmlAttributeByTagName("name");
    item.m_useCount = readXmlAttributeByTagName("useCount").toInt();
}
