#include "downloadlistconfigmanager.h"

DownloadListConfigManager::DownloadListConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

void DownloadListConfigManager::writeListConfig(const DownloadItemList &records)
{
    if(!toFile(LIST_PATH_FULL))
    {
        return;
    }

    createProcessingInstruction();
    QDomElement rootDom = createRoot(APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "list");

    for(const DownloadItem &record : qAsConst(records))
    {
        writeDomMutilElement(recordDom, "value", {TTKXmlAttribute("url", record.m_url),
                                                  TTKXmlAttribute("name", record.m_name)});
    }

    QTextStream out(m_file);
    m_document->save(out, 4);
}

void DownloadListConfigManager::readListConfig(DownloadItemList &records)
{
    const QDomNodeList &nodes = m_document->elementsByTagName("value");
    for(int i = 0; i < nodes.count(); ++i)
    {
        const QDomElement &element = nodes.item(i).toElement();

        DownloadItem record;
        record.m_url = element.attribute("url");
        record.m_name = element.attribute("name");
        records << record;
    }
}
