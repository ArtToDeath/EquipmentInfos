#ifndef EQUIPMENTINFO_H
#define EQUIPMENTINFO_H
#include <QObject>
class EquipmentInfo
{
public:
    EquipmentInfo(const QString &name, const QString &version, const QString &installDate);
    virtual ~EquipmentInfo();
private:
    QString equipmentName;
    QString equipmentVersion;
    QString equipmentInstallDate;
    QString describle;

public:

    QString getEquipmentName() const;
    void setEquipmentName(const QString &value);

    QString getEquipmentVersion() const;
    void setEquipmentVersion(const QString &value);

    QString getEquipmentInstallDate() const;
    void setEquipmentInstallDate(const QString &value);

    QString getDescrible() const;
    void setDescrible(const QString &value);

    QString toString() const;

    friend bool operator==(const EquipmentInfo &info1, const EquipmentInfo &info2);

signals:

public slots:
};

#endif // EQUIPMENTINFO_H
