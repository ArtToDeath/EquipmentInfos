#ifndef EQUIPMENTUTIL_H
#define EQUIPMENTUTIL_H

#include <QObject>
#include "equipmentinfo.h"

class EquipmentUtil : public QObject
{
    Q_OBJECT
public:
    explicit EquipmentUtil(QObject *parent = nullptr);

    static QList<EquipmentInfo> getSoftwareInfos();
    static EquipmentInfo getOSInfo();

signals:

public slots:
};

#endif // EQUIPMENTUTIL_H
