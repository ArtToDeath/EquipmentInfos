#include "xmlutil.h"
#include <QFile>
bool XmlUtil::docRead()
{
    QFile file("config.xml");
    if(!file.open(QIODevice::ReadOnly))
        return false;
    if(!doc.setContent(&file)){
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool XmlUtil::docWrite()
{
    QFile file("config.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        return false;
    }
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();
    return true;
}

void XmlUtil::writeXml(const QString &departStr, const QString &classStr)
{
    if(docRead()){
        QDomElement root = doc.documentElement();

        if(!root.hasChildNodes()){//无节点
            QDomElement departEle = doc.createElement(QString("部门"));
            QDomAttr departAttr = doc.createAttribute("department");
            departAttr.setValue(departStr);
            departEle.setAttributeNode(departAttr);
            root.appendChild(departEle);
            createNodes(departEle, classStr);
        }else{//有节点
            QDomNodeList children = root.childNodes();
            bool hasDepartEle = false;
            for(int i = 0; i < children.count(); i ++){
                QDomNode node = children.at(i);
                QDomElement child;
                child = node.toElement();
                QString tempStr = child.attribute("department");
                if(tempStr == departStr){//部门存在
                    createNodes(child, classStr);
                    hasDepartEle = true;
                }
            }
            if(!hasDepartEle){
                QDomElement departEle = doc.createElement(QString("部门"));
                QDomAttr departAttr = doc.createAttribute("department");
                departAttr.setValue(departStr);
                departEle.setAttributeNode(departAttr);
                root.appendChild(departEle);
                createNodes(departEle, classStr);
            }
        }
        docWrite();
    }
}

void XmlUtil::getDepartList(QStringList &departList)
{
    if(docRead()){
        QDomElement root = doc.documentElement();
        if(root.hasChildNodes()){
            QDomNodeList children = root.childNodes();
            for (int i = 0; i < children.count(); i ++) {
                QDomNode node = children.at(i);
                QString departStr = node.toElement().attribute("department");
                departList.push_back(departStr);
            }
        }
    }
}

void XmlUtil::getClassList(const QString &departStr, QStringList &classList)
{
    if(docRead()){
        QDomElement root = doc.documentElement();
        if(root.hasChildNodes()){
            QDomNodeList children = root.childNodes();
            for (int i = 0; i < children.count(); i ++) {
                QDomNode node = children.at(i);
                QString tempStr = node.toElement().attribute("department");
                if(tempStr == departStr){
                    QDomNodeList list = node.childNodes();
                    for(int j = 0; j < list.count(); j ++){
                        QString classStr = list.at(j).toElement().text();
                        classList.push_back(classStr);
                    }
                }
            }
        }
    }
}

void XmlUtil::createNodes(QDomElement &ele, const QString &classStr)
{
    QDomNodeList children = ele.childNodes();
    for(int i = 0; i < children.count(); i ++){
        QDomNode node = children.at(i);
        QDomElement child;
        child = node.toElement();
        QString tempStr = child.text();
        if(tempStr == classStr){//课别存在
            return;
        }
    }
    QDomElement classEle = doc.createElement(QString("课别"));
    QDomText text;
    text = doc.createTextNode(classStr);
    classEle.appendChild(text);
    ele.appendChild(classEle);
}

XmlUtil::XmlUtil()
{

}
