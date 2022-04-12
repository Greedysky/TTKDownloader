#ifndef DOWNLOADABSTRACTXML_H
#define DOWNLOADABSTRACTXML_H

/***************************************************************************
 * This file is part of the TTK Downloader project
 * Copyright (C) 2015 - 2022 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>

#include "ttkglobaldefine.h"
#include "downloadobject.h"

/*! @brief The class of the xml attribute.
 * @author Greedysky <greedysky@163.com>
 */
struct TTK_MODULE_EXPORT DownloadXmlAttribute
{
    QString m_key;
    QVariant m_value;

    DownloadXmlAttribute(const QString &key, const QVariant &value)
    {
        m_key = key;
        m_value = value;
    }
};
TTK_DECLARE_LIST(DownloadXmlAttribute);

/*! @brief The class of the base class of xml interface.
 * @author Greedysky <greedysky@163.com>
 */
class TTK_MODULE_EXPORT DownloadAbstractXml : public QObject
{
    Q_OBJECT
    TTK_DECLARE_MODULE(DownloadAbstractXml)
public:
    /*!
     * Object contsructor.
     */
    explicit DownloadAbstractXml(QObject *parent = nullptr);
    ~DownloadAbstractXml();

    /*!
     * Read datas from xml file by given name.
     */
    bool readConfig(const QString &name);
    /*!
     * Write datas into xml file by given name.
     */
    bool writeConfig(const QString &name);

    /*!
     * Xml stream data from string.
     */
    bool fromString(const QString &data);
    /*!
     * Xml stream data from byteArray.
     */
    bool fromByteArray(const QByteArray &data);

    /*!
     * Xml stream data to string.
     */
    QString toString() const;
    /*!
     * Xml stream data to byteArray.
     */
    QByteArray toByteArray() const;

    /*!
     * Read xml attribute by tagName and default name "value".
     */
    QString readXmlAttributeByTagNameValue(const QString &tagName) const;
    /*!
     * Read xml attribute by tagName and attribute name.
     */
    QString readXmlAttributeByTagName(const QString &tagName, const QString &attrName) const;
    /*!
     * Read xml attribute's text by tagName.
     */
    QString readXmlTextByTagName(const QString &tagName) const;
    /*!
     * Read xml attributes by tagName and default name "value".
     */
    TTKVariantMap readXmlAttributesByTagName(const QString &tagName) const;
    /*!
     * Create processing instruction in header.
     */
    void createProcessingInstruction();
    /*!
     * Create xml node nodes by node name.
     */
    QDomElement createRoot(const QString &node);
    /*!
     * Create xml node nodes by node atrr.
     */
    QDomElement createRoot(const QString &node, const DownloadXmlAttribute &attr);
    /*!
     * Create xml node nodes by node atrrs.
     */
    QDomElement createRoot(const QString &node, const DownloadXmlAttributeList &attrs);
    /*!
     * Append xml element nodes by node name.
     */
    QDomElement writeDomNode(QDomElement &element, const QString &node);
    /*!
     * Append xml element nodes by node name\ key name and value.
     */
    QDomElement writeDomElement(QDomElement &element, const QString &node, const DownloadXmlAttribute &attr);
    /*!
     * Append xml elements nodes by node name\ keys name and values.
     */
    QDomElement writeDomMutilElement(QDomElement &element, const QString &node, const DownloadXmlAttributeList &attrs);
    /*!
     * Append xml element nodes by node name\ key name \ value and attribute's text.
     */
    QDomElement writeDomElementText(QDomElement &element, const QString &node, const DownloadXmlAttribute &attr, const QString &text);
    /*!
     * Append xml elements nodes by node name\ keys name \ values and attribute's text.
     */
    QDomElement writeDomMutilElementText(QDomElement &element, const QString &node, const DownloadXmlAttributeList &attrs, const QString &text);
    /*!
     * Append xml element nodes by node name and attribute's text.
     */
    QDomElement writeDomText(QDomElement &element, const QString &node, const QString &text);
    /*!
     * Append xml element nodes key name and value.
     */
    void writeAttribute(QDomElement &element, const DownloadXmlAttribute &attr);

protected:
    QFile *m_file;
    QDomDocument *m_document;

};

#endif // DOWNLOADABSTRACTXML_H
