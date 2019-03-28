#include "equipmentinfo.h"
EquipmentInfo::EquipmentInfo(const QString &name, const QString &version, const QString &installDate)
{
    this->equipmentName = name;
    this->equipmentVersion = version;
    this->equipmentInstallDate = installDate;
}

EquipmentInfo::~EquipmentInfo()
{

}

QString EquipmentInfo::getDescrible() const
{
    return describle;
}

void EquipmentInfo::setDescrible(const QString &value)
{
    describle = value;
}

QString EquipmentInfo::toString() const
{
    return equipmentName + " | " + equipmentVersion + " | " + equipmentInstallDate + " | " + describle;
}

bool operator==(const EquipmentInfo &info1, const EquipmentInfo &info2)
{
    if(info1.equipmentName == info2.equipmentName
            && info1.equipmentVersion == info2.equipmentVersion
            && info1.equipmentInstallDate == info2.equipmentInstallDate){
        return true;
    }
    return false;
}

QString EquipmentInfo::getEquipmentInstallDate() const
{
    return equipmentInstallDate;
}

void EquipmentInfo::setEquipmentInstallDate(const QString &value)
{
    equipmentInstallDate = value;
}

QString EquipmentInfo::getEquipmentVersion() const
{
    return equipmentVersion;
}

void EquipmentInfo::setEquipmentVersion(const QString &value)
{
    equipmentVersion = value;
}

QString EquipmentInfo::getEquipmentName() const
{
    return equipmentName;
}

void EquipmentInfo::setEquipmentName(const QString &value)
{
    equipmentName = value;
}
