#include "downloadabstractxml.h"

DownloadAbstractXml::DownloadAbstractXml(QObject *parent)
    : QObject(parent)
{
    m_file = nullptr;
    m_document = nullptr;
}

DownloadAbstractXml::~DownloadAbstractXml()
{
    delete m_file;
    delete m_document;
}

bool DownloadAbstractXml::readConfig(const QString &name)
{
    delete m_file;
    delete m_document;
    m_file = new QFile(name);
    m_document = new QDomDocument;

    if(!m_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    if(!m_document->setContent(m_file))
    {
        m_file->close();
        delete m_file;
        m_file = nullptr;
        return false;
    }
    return true;
}

bool DownloadAbstractXml::writeConfig(const QString &name)
{
    delete m_file;
    delete m_document;
    m_file = new QFile(name);
    m_document = new QDomDocument;
    return m_file->open(QFile::WriteOnly | QFile::Text);
}

bool DownloadAbstractXml::fromString(const QString &data)
{
    delete m_file;
    delete m_document;
    m_file = nullptr;
    m_document = new QDomDocument;
    return m_document->setContent(data);
}

bool DownloadAbstractXml::fromByteArray(const QByteArray &data)
{
    delete m_file;
    delete m_document;
    m_file = nullptr;
    m_document = new QDomDocument;
    return m_document->setContent(data);
}

QString DownloadAbstractXml::toString() const
{
    return m_document ? m_document->toString() : QString();
}

QByteArray DownloadAbstractXml::toByteArray() const
{
    return m_document ? m_document->toByteArray() : QByteArray();
}

QString DownloadAbstractXml::readXmlAttributeByTagNameValue(const QString &tagName) const
{
    return readXmlAttributeByTagName(tagName, "value");
}

QString DownloadAbstractXml::readXmlAttributeByTagName(const QString &tagName, const QString &attrName) const
{
    const QDomNodeList &nodeList = m_document->elementsByTagName(tagName);
    if(nodeList.isEmpty())
    {
        return QString();
    }
    return nodeList.at(0).toElement().attribute(attrName);
}

QString DownloadAbstractXml::readXmlTextByTagName(const QString &tagName) const
{
    const QDomNodeList &nodeList = m_document->elementsByTagName(tagName);
    if(nodeList.isEmpty())
    {
        return QString();
    }
    return nodeList.at(0).toElement().text();
}

TTKVariantMap DownloadAbstractXml::readXmlAttributesByTagName(const QString &tagName) const
{
    const QDomNodeList &nodeList = m_document->elementsByTagName(tagName);
    if(nodeList.isEmpty())
    {
        return TTKVariantMap();
    }

    const QDomNamedNodeMap &nodes = nodeList.at(0).toElement().attributes();
    TTKVariantMap maps;
    for(int i=0; i<nodes.count(); ++i)
    {
        const QDomAttr &attr = nodes.item(i).toAttr();
        maps[attr.name()] = attr.value();
    }
    return maps;
}

void DownloadAbstractXml::createProcessingInstruction()
{
    const QDomNode &node = m_document->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    m_document->appendChild(node);
}

QDomElement DownloadAbstractXml::createRoot(const QString &node)
{
    const QDomElement &domElement = m_document->createElement(node);
    m_document->appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::createRoot(const QString &node, const DownloadXmlAttribute &attr)
{
    QDomElement domElement = m_document->createElement(node);
    writeAttribute(domElement, attr);
    m_document->appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::createRoot(const QString &node, const DownloadXmlAttributeList &attrs)
{
    QDomElement domElement = m_document->createElement(node);
    for(const DownloadXmlAttribute &attr : qAsConst(attrs))
    {
        writeAttribute(domElement, attr);
    }
    m_document->appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomNode(QDomElement &element, const QString &node)
{
    const QDomElement &domElement = m_document->createElement(node);
    element.appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomElement(QDomElement &element, const QString &node, const DownloadXmlAttribute &attr)
{
    QDomElement domElement = writeDomNode(element, node);
    writeAttribute(domElement, attr);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomElementMutil(QDomElement &element, const QString &node, const DownloadXmlAttributeList &attrs)
{
    if(attrs.isEmpty())
    {
        QDomElement();
    }

    QDomElement domElement = writeDomElement(element, node, attrs.front());
    for(int i=1; i<attrs.count(); ++i)
    {
        writeAttribute(domElement, attrs[i]);
    }
    return domElement;
}

void DownloadAbstractXml::writeAttribute(QDomElement &element, const DownloadXmlAttribute &attr)
{
#if TTK_QT_VERSION_CHECK(6,0,0)
    switch(attr.m_value.typeId())
#else
    switch(attr.m_value.type())
#endif
    {
        case QVariant::Int: element.setAttribute(attr.m_key, attr.m_value.toInt()); break;
        case QVariant::String: element.setAttribute(attr.m_key, attr.m_value.toString()); break;
        case QVariant::LongLong: element.setAttribute(attr.m_key, attr.m_value.toLongLong()); break;
        case QVariant::ULongLong: element.setAttribute(attr.m_key, attr.m_value.toULongLong()); break;
        case QVariant::Double: element.setAttribute(attr.m_key, attr.m_value.toDouble()); break;
        case QVariant::UInt: element.setAttribute(attr.m_key, attr.m_value.toUInt()); break;
        default: break;
    }
}

QDomElement DownloadAbstractXml::writeDomElementText(QDomElement &element, const QString &node, const DownloadXmlAttribute &attr, const QString &text)
{
    QDomElement domElement = writeDomElement(element, node, attr);
    const QDomText &domText = m_document->createTextNode(text);
    domElement.appendChild(domText);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomElementMutilText(QDomElement &element, const QString &node, const DownloadXmlAttributeList &attrs, const QString &text)
{
    if(attrs.isEmpty())
    {
        QDomElement();
    }

    QDomElement domElement = writeDomElementMutil(element, node, attrs);
    const QDomText &domText = m_document->createTextNode(text);
    domElement.appendChild(domText);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomText(QDomElement &element, const QString &node, const QString &text)
{
    QDomElement domElement = writeDomNode(element, node);
    const QDomText &domText = m_document->createTextNode(text);
    domElement.appendChild(domText);
    return domElement;
}
