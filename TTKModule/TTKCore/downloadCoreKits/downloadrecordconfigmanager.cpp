#include "downloadrecordconfigmanager.h"

DownloadRecordConfigManager::DownloadRecordConfigManager(QObject *parent)
    : TTKXmlDocument(parent)
{

}

bool DownloadRecordConfigManager::readBuffer(DownloadRecordList &items)
{
    const QDomNodeList &nodes = m_document->elementsByTagName("value");
    for(int i = 0; i < nodes.count(); ++i)
    {
        const QDomElement &element = nodes.item(i).toElement();

        DownloadRecord item;
        item.m_path = element.attribute("name");
        item.m_time = element.attribute("time");
        item.m_size = element.attribute("size");
        item.m_url = element.attribute("url");
        items << item;
    }

    return true;
}

bool DownloadRecordConfigManager::writeBuffer(const DownloadRecordList &items)
{
    createProcessingInstruction();
    QDomElement rootDom = createRoot(TTK_APP_NAME);
    QDomElement recordDom = writeDomNode(rootDom, "history");

    for(const DownloadRecord &item : qAsConst(items))
    {
        writeDomMutilElement(recordDom, "value", {TTKXmlAttribute("name", item.m_path),
                                                  TTKXmlAttribute("size", item.m_size),
                                                  TTKXmlAttribute("time", item.m_time),
                                                  TTKXmlAttribute("url", item.m_url)});
    }

    save();
    return true;
}
