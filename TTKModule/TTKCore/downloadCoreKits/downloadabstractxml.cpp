#include "downloadabstractxml.h"

#ifdef Q_CC_GNU
#   pragma GCC diagnostic ignored "-Wswitch"
#endif

DownloadAbstractXml::DownloadAbstractXml(QObject *parent)
    : QObject(parent)
{
    m_file = nullptr;
    m_ddom = nullptr;
}

DownloadAbstractXml::~DownloadAbstractXml()
{
    delete m_file;
    delete m_ddom;
}

bool DownloadAbstractXml::readConfig(const QString &name)
{
    delete m_file;
    delete m_ddom;
    m_file = new QFile(name);
    m_ddom = new QDomDocument;
    if(!m_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }
    if(!m_ddom->setContent(m_file))
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
    delete m_ddom;
    m_file = new QFile(name);
    m_ddom = new QDomDocument;
    if(!m_file->open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }
    return true;
}

bool DownloadAbstractXml::fromString(const QString &data)
{
    delete m_file;
    delete m_ddom;
    m_file = nullptr;
    m_ddom = new QDomDocument;
    if(!m_ddom->setContent(data))
    {
        return false;
    }
    return true;
}

bool DownloadAbstractXml::fromByteArray(const QByteArray &data)
{
    delete m_file;
    delete m_ddom;
    m_file = nullptr;
    m_ddom = new QDomDocument;
    if(!m_ddom->setContent(data))
    {
        return false;
    }
    return true;
}

QString DownloadAbstractXml::toString() const
{
    if(!m_ddom)
    {
        return QString();
    }
    return m_ddom->toString();
}

QByteArray DownloadAbstractXml::toByteArray() const
{
    if(!m_ddom)
    {
        return QByteArray();
    }
    return m_ddom->toByteArray();
}

QString DownloadAbstractXml::readXmlAttributeByTagNameValue(const QString &tagName) const
{
    return readXmlAttributeByTagName(tagName, "value");
}

QString DownloadAbstractXml::readXmlAttributeByTagName(const QString &tagName,
                                                    const QString &attrName) const
{
    QDomNodeList nodelist = m_ddom->elementsByTagName(tagName);
    if(nodelist.isEmpty())
    {
        return QString();
    }
    return nodelist.at(0).toElement().attribute(attrName);
}

QString DownloadAbstractXml::readXmlTextByTagName(const QString &tagName) const
{
    QDomNodeList nodelist = m_ddom->elementsByTagName(tagName);
    if(nodelist.isEmpty())
    {
        return QString();
    }
    return nodelist.at(0).toElement().text();
}

TTKVariantMap DownloadAbstractXml::readXmlAttributesByTagName(const QString &tagName) const
{
    QDomNodeList nodelist = m_ddom->elementsByTagName(tagName);
    if(nodelist.isEmpty())
    {
        return TTKVariantMap();
    }
    QDomNamedNodeMap nodes = nodelist.at(0).toElement().attributes();
    TTKVariantMap maps;
    for(int i=0; i<nodes.count(); ++i)
    {
        QDomAttr attr = nodes.item(i).toAttr();
        maps[attr.name()] = attr.value();
    }
    return maps;
}

void DownloadAbstractXml::createProcessingInstruction()
{
    QDomNode node = m_ddom->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    m_ddom->appendChild(node);
}

QDomElement DownloadAbstractXml::createRoot(const QString &node)
{
    QDomElement domElement = m_ddom->createElement(node);
    m_ddom->appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::createRoot(const QString &node, const DownloadXmlAttribute &attr)
{
    QDomElement domElement = m_ddom->createElement(node);
    writeAttribute(domElement, attr);
    m_ddom->appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::createRoot(const QString &node, const DownloadXmlAttributes &attrs)
{
    QDomElement domElement = m_ddom->createElement(node);
    foreach(const DownloadXmlAttribute &attr, attrs)
    {
        writeAttribute(domElement, attr);
    }
    m_ddom->appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDom(QDomElement &element, const QString &node)
{
    QDomElement domElement = m_ddom->createElement(node);
    element.appendChild(domElement);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomElement(QDomElement &element, const QString &node,
                                              const DownloadXmlAttribute &attr)
{
    QDomElement domElement = writeDom(element, node);
    writeAttribute(domElement, attr);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomElementMutil(QDomElement &element, const QString &node,
                                                   const DownloadXmlAttributes &attrs)
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
    switch(attr.m_value.type())
    {
        case QVariant::Int :
            element.setAttribute(attr.m_key, attr.m_value.toInt()); break;
        case QVariant::String :
            element.setAttribute(attr.m_key, attr.m_value.toString()); break;
        case QVariant::LongLong :
            element.setAttribute(attr.m_key, attr.m_value.toLongLong()); break;
        case QVariant::ULongLong :
            element.setAttribute(attr.m_key, attr.m_value.toULongLong()); break;
        case QVariant::Double :
            element.setAttribute(attr.m_key, attr.m_value.toDouble()); break;
        case QVariant::UInt :
            element.setAttribute(attr.m_key, attr.m_value.toUInt()); break;
    }
}

QDomElement DownloadAbstractXml::writeDomElementText(QDomElement &element, const QString &node,
                                                  const DownloadXmlAttribute &attr, const QString &text)
{
    QDomElement domElement = writeDomElement(element, node, attr);
    QDomText domText = m_ddom->createTextNode(text);
    domElement.appendChild(domText);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomElementMutilText(QDomElement &element, const QString &node,
                                                       const DownloadXmlAttributes &attrs, const QString &text)
{
    if(attrs.isEmpty())
    {
        QDomElement();
    }

    QDomElement domElement = writeDomElementMutil(element, node, attrs);
    QDomText domText = m_ddom->createTextNode(text);
    domElement.appendChild(domText);
    return domElement;
}

QDomElement DownloadAbstractXml::writeDomText(QDomElement &element, const QString &node,
                                           const QString &text)
{
    QDomElement domElement = writeDom(element, node);
    QDomText domText = m_ddom->createTextNode(text);
    domElement.appendChild(domText);
    return domElement;
}
