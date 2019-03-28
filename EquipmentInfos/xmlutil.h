#ifndef XMLUTIL_H
#define XMLUTIL_H

#include "connection.h"
#include <QStringList>
#include <QTextStream>

class XmlUtil
{
private:
    QDomDocument doc;
    bool docRead();
    bool docWrite();
    void createNodes(QDomElement &ele, const QString &classStr);

public:
    XmlUtil();

    void writeXml(const QString &departStr, const QString &classStr);
    void getDepartList(QStringList &departList);
    void getClassList(const QString &departStr, QStringList &classList);

};

#endif // XMLUTIL_H
