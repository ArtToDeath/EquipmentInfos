#ifndef CONNECTION_H
#define CONNECTION_H

#include "qdom.h"
#include <QFile>
#include <QTextStream>

static bool createXml(){
    QFile file("config.xml");
    if(file.exists()) return true;
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement(QString("清单"));
    doc.appendChild(root);
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
    return true;
}
#endif // CONNECTION_H
