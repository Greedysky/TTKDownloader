#include "downloadrecordconfigmanager.h"

DownloadRecordConfigManager::DownloadRecordConfigManager()
    : TTKAbstractXml()
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
    QDomElement recordDom = writeDomElement(rootDom, "record");

    for(const DownloadRecord &item : qAsConst(items))
    {
        writeDomMultiElement(recordDom, "value", {{"name", item.m_path},
                                                  {"size", item.m_size},
                                                  {"time", item.m_time},
                                                  {"url", item.m_url}});
    }

    save();
    return true;
}
