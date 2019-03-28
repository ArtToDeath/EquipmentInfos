#ifndef EXCELUTIL_H
#define EXCELUTIL_H

#include "equipmentinfo.h"

#include <QList>
#include <QString>
#include <QtXlsx>

class ExcelUtil
{
public:
    ExcelUtil(const QString &userStr, const QString &departStr, const QString &classStr);
private:
    const QString OLD_NAME = "OLD_NAME";
    QString userStr;
    QString departStr;
    QString classStr;

    QString filePath;

    void createFilePath();

    void normalStyle(QXlsx::Format &style, int fontSize);

public:

    bool toExcelFile(const QList<EquipmentInfo> &infos);
};

#endif // EXCELUTIL_H
