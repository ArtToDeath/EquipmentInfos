#include "excelutil.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

ExcelUtil::ExcelUtil(const QString &userStr, const QString &departStr, const QString &classStr)
{
    this->userStr = userStr;
    this->departStr = departStr;
    this->classStr = classStr;
}

void ExcelUtil::createFilePath()
{
    QString appPath = QCoreApplication::applicationDirPath();
    filePath = appPath + "\\" + departStr + "\\";
    QDir dir(filePath);//创建形如：appPath//部门//...目录
    if(!dir.exists()){
        dir.mkpath(filePath);
    }

}

void ExcelUtil::normalStyle(QXlsx::Format &style, int fontSize)
{
    style.setFontSize(fontSize);
    style.setFontName("微软雅黑");
    style.setBorderStyle(QXlsx::Format::BorderThin);
    style.setHorizontalAlignment(QXlsx::Format::AlignHCenter);
    style.setVerticalAlignment(QXlsx::Format::AlignVCenter);
}

bool ExcelUtil::toExcelFile(const QList<EquipmentInfo> &infos)
{
    createFilePath();
    QString fileName = filePath + classStr + ".xlsx";
    QXlsx::Document xlsx(fileName);
    while(xlsx.selectSheet(userStr)){//将userStr设为活动工作表
        xlsx.renameSheet(userStr, OLD_NAME);
        xlsx.deleteSheet(OLD_NAME);
    }
    if(!xlsx.addSheet(userStr)){
        return false;
    }
    xlsx.selectSheet(userStr);

    xlsx.setColumnWidth(1, 7);
    xlsx.setColumnWidth(2, 7, 12);
    xlsx.setColumnWidth(8, 24);
    //the header row
    QXlsx::Format headerStyle;
    normalStyle(headerStyle, 20);
    headerStyle.setFontBold(true);
    headerStyle.setFontUnderline(QXlsx::Format::FontUnderlineSingle);
    xlsx.setRowHeight(1, 60);
    xlsx.write("A1", QString("资讯设备履历表"));
    xlsx.mergeCells("A1:H1", headerStyle);

    QXlsx::Format entryStyle;
    normalStyle(entryStyle, 14);
    entryStyle.setFontBold(true);
    xlsx.setRowHeight(2, 3, 36);
    xlsx.write("A2", QString("序号"));
    xlsx.write("B2", QString("部门"), entryStyle);
    xlsx.write("D2", QString("课别"), entryStyle);
    xlsx.write("F2", QString("姓名"), entryStyle);
    xlsx.write("H2", QString("说明"));
    xlsx.write("B3", QString("名称"));
    xlsx.write("D3", QString("安装时间"));
    xlsx.write("F3", QString("版本"));
    xlsx.mergeCells("A2:A3", entryStyle);
    xlsx.mergeCells("H2:H3", entryStyle);
    xlsx.mergeCells("B3:C3", entryStyle);
    xlsx.mergeCells("D3:E3", entryStyle);
    xlsx.mergeCells("F3:G3", entryStyle);

    QXlsx::Format feildStyle;
    normalStyle(feildStyle, 10);
    //feildStyle.setShrinkToFit(true);
    feildStyle.setTextWarp(true);
    xlsx.write("C2", departStr, feildStyle);
    xlsx.write("E2", classStr, feildStyle);
    xlsx.write("G2", userStr,feildStyle);
    int count = 4;//行数
    for(int i = 0; i < infos.length(); i ++){
        xlsx.setRowHeight(i+4, 36);
        xlsx.write(i+4, 1, i+1, feildStyle);
        xlsx.write(i+4, 2, infos.at(i).getEquipmentName());
        xlsx.mergeCells(QXlsx::CellRange(i+4, 2, i+4, 3), feildStyle);
        xlsx.write(i+4, 4, infos.at(i).getEquipmentInstallDate());
        xlsx.mergeCells(QXlsx::CellRange(i+4, 4, i+4, 5), feildStyle);
        xlsx.write(i+4, 6, infos.at(i).getEquipmentVersion());
        xlsx.mergeCells(QXlsx::CellRange(i+4, 6, i+4, 7), feildStyle);
        xlsx.write(i+4, 8, infos.at(i).getDescrible(), feildStyle);
        count ++;
    }

    QXlsx::Format footerStyle;
    normalStyle(footerStyle, 14);
    footerStyle.setFontBold(true);
    footerStyle.setHorizontalAlignment(QXlsx::Format::AlignRight);
    footerStyle.setVerticalAlignment(QXlsx::Format::AlignBottom);
    xlsx.setRowHeight(count, 40);
    xlsx.write(count, 1, QString("签收:           "));
    xlsx.mergeCells(QXlsx::CellRange(count, 1, count, 8), footerStyle);

    if(xlsx.save()){
        foreach(QString s, xlsx.sheetNames()){
            if(s == OLD_NAME)
                qDebug()<<xlsx.deleteSheet(OLD_NAME);
        }
    }
    return xlsx.save();
}
