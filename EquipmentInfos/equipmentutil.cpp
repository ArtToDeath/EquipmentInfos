#include "equipmentutil.h"

#include <QSettings>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>

EquipmentUtil::EquipmentUtil(QObject *parent) : QObject(parent)
{

}

QList<EquipmentInfo> EquipmentUtil::getSoftwareInfos()
{
    QList<EquipmentInfo>  list;
    int softWareCount=0;
    QStringList subKeyNameList{
        "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall"};
    foreach(QString subKeyName, subKeyNameList){
        QSettings reg(subKeyName, QSettings::NativeFormat);
        QStringList groupsList = reg.childGroups();
        foreach(QString group, groupsList){
            reg.beginGroup(group);

            int windowsInstaller = reg.value("WindowsInstaller").toInt();
            int systemComponent = reg.value("SystemComponent").toInt();
            if(windowsInstaller == 1 || systemComponent == 1){
                reg.endGroup();
                continue;
            }
            QString softWareName = reg.value("DisplayName").toString();
            QString softWareVersion = reg.value("DisplayVersion").toString();

            if(!softWareName.isEmpty() && !softWareVersion.isEmpty()){

                if (!softWareName.toLower().contains("driver")
                        && !softWareName.toLower().contains("update")
                        && !softWareName.toLower().contains("redistributable")
                        && !softWareName.toLower().contains("flash")
                        && !softWareName.toLower().contains(".net framework")){
                    //日期查询
                    QString installDate = reg.value("InstallDate").toDateTime().toString("yyyy-MM-dd");
                    if(installDate.isEmpty()){
                        QString installLocation = reg.value("InstallLocation").toString();
                        QFileInfo info(installLocation);
                        if(info.exists()){
                            installDate = info.birthTime().toString("yyyy-MM-dd");
                        }else{
                            QString displayIcon = reg.value("DisplayIcon").toString();
                            if(displayIcon.contains(",")){
                                displayIcon = displayIcon.left(displayIcon.length() - 2);
                            }

                            info.setFile(displayIcon);
                            if(info.exists()){
                                info.setFile(info.absolutePath());//文件路径的创建时间更准确
                                if(info.exists()){
                                    installDate = info.birthTime().toString("yyyy-MM-dd");
                                }
                            }
                        }
                    }

                    EquipmentInfo info(softWareName, softWareVersion, installDate);
                    if(softWareName.toLower().contains("solidworks")){
                        QSettings regSW("HKEY_LOCAL_MACHINE\\SOFTWARE\\SolidWorks\\Security", QSettings::NativeFormat);\
                        QString description = regSW.value("Serial Number").toString();
                        info.setDescrible("序列号: " + description);
                        regSW.clear();
                    }
                    if(!list.contains(info)){
                        list.push_back(info);
                        softWareCount++;
                    }
                }
            }
            reg.endGroup();
        }
        reg.clear();
    }
    return list;
}

EquipmentInfo EquipmentUtil::getOSInfo()
{
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", QSettings::NativeFormat);

    uint seconds = reg.value("InstallDate").toUInt();
    QString installDate = QDateTime::fromTime_t(seconds).toString("yyyy-MM-dd");
    QString OSName = reg.value("ProductName").toString();
    QString OSVersion = reg.value("CurrentVersion").toString();
    QString productId = reg.value("ProductId").toString();
    EquipmentInfo info(OSName, OSVersion, installDate);
    info.setDescrible("产品ID: " + productId);
    reg.clear();
    return info;
}
